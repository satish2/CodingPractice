/**
 * imggif.c - interface for libgif input routines
 *
 * Copyright (c) 1998
 *      Transvirtual Technologies, Inc.  All rights reserved.
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */

#if NO_NEED

#include "toolkit.h"
#include <stdio.h>

#if defined(HAVE_GIF_LIB_H) && (defined(HAVE_LIBGIF) || defined(HAVE_LIBUNGIF))
#define INCLUDE_GIF 1
#endif

#if defined(INCLUDE_GIF)
#include "gif_lib.h"
#endif


/**************************************************************************************
 * internal functions
 */

#if defined(INCLUDE_GIF)

static int iOffset[] = { 0, 4, 2, 1 };
static int iJumps[] = { 8, 8, 4, 2 };

void
writeRow ( Image* img, GifPixelType* rowBuf, GifColorType* cm, int row )
{
  int             idx, col;
  jint            rgb;
  unsigned long   pix;

  for ( col=0; col < img->width; col++ ) {
	idx = rowBuf[col];
	if ( img->xMask && (idx == img->trans) ) {
	  pix = 0;
	  XPutPixel( img->xMask, col, row, 0);
	}
	else {
	  rgb = (cm[idx].Red << 16) | (cm[idx].Green << 8) | (cm[idx].Blue);
	  pix = pixelValue( X, rgb);
	}
	XPutPixel( img->xImg, col, row, pix);
  }
}


#define CHECK(gifOp) \
  if ( gifOp == GIF_ERROR ) { \
    if ( img )    Java_java_awt_Toolkit_imgFreeImage( 0, 0, img); \
    if ( rowBuf ) AWT_FREE( rowBuf); \
    return 0; \
  }


Image*
readGif ( GifFileType *gf )
{
  Image           *firstImg = 0, *img;
  int             i, extCode, width, height, row, cmapSize, nFrames = 0;
  GifRecordType   rec;
  GifByteType     *ext;
  ColorMapObject  *cmap;
  GifColorType    *clrs;
  GifPixelType    *rowBuf = (GifPixelType*) AWT_MALLOC( gf->SWidth * sizeof( GifPixelType) );

  img = createImage( gf->SWidth, gf->SHeight);

  do {
	CHECK( DGifGetRecordType( gf, &rec));

	switch ( rec ) {
	case IMAGE_DESC_RECORD_TYPE:
	  CHECK( DGifGetImageDesc( gf));

	  width    = gf->Image.Width;
	  height   = gf->Image.Height;

      cmap     = (gf->Image.ColorMap) ? gf->Image.ColorMap : gf->SColorMap;
	  clrs     = cmap->Colors;
      cmapSize = cmap->ColorCount;

	  /*
	   * create our image objects and keep track of frames 
	   */
	  if ( !firstImg ) {     /* this is the first (maybe only) frame */
		firstImg = img;
	  }
	  else {                 /* this is a subsequent gif-movie frame, link it in */
		img->next = createImage( gf->SWidth, gf->SHeight);
		if ( !img->latency )
		  img->latency = 100;  /* default */
		img = img->next;
	  }
	  nFrames++;
	  createXImage( X, img);

	  /*
	   * start reading in the image data
	   */
	  if ( gf->Image.Interlace ) {
		/* Need to perform 4 passes on the images: */
		for ( i = 0; i < 4; i++ ) {
		  for (row = iOffset[i]; row < height; row += iJumps[i]) {
			memset( rowBuf, gf->SBackGroundColor, width);
			CHECK( DGifGetLine( gf, rowBuf, width));

			writeRow( img, rowBuf, clrs, row);
		  }
		}
	  }
	  else {
		for ( row = 0; row < height; row++) {
		  memset( rowBuf, gf->SBackGroundColor, width);
		  CHECK( DGifGetLine(gf, rowBuf, width));

		  writeRow( img, rowBuf, clrs, row);
		}
	  }
	  break;

	case EXTENSION_RECORD_TYPE:
	  CHECK( DGifGetExtension( gf, &extCode, &ext));

	  if ( extCode == 0xf9 ) {   /* graphics extension */
		if ( ext[1] & 1 ) {      /* transparent index following */
		  img->trans = ext[4];
		  createXMaskImage( X, img);
		}
	  }

	  while ( ext != NULL ) {
		CHECK( DGifGetExtensionNext( gf, &ext));
	  }
	  break;

	case TERMINATE_RECORD_TYPE:
	  break;

	default:                /* Should be traps by DGifGetRecordType. */
	  break;
	}
  } while ( rec != TERMINATE_RECORD_TYPE );

  if ( firstImg && (img != firstImg) ){
	img->next = firstImg;   /* link it together (as a ring) */
  }

  return firstImg;
}

/**************************************************************************************
 * memory buffer IO
 */

typedef struct {
  unsigned char *buf;
  unsigned char *p;
  long          remain;
} BufferSource;

int
readGifBuffer ( GifFileType *gf, GifByteType* buf, int length )
{
  BufferSource *psource = (BufferSource*)gf->UserData;

  if ( psource && (psource->remain >= length) ) {
	memcpy( buf, psource->p, length);
	psource->p += length;
	psource->remain -= length;

	return length;
  }
  else {
	return 0;
  }
}

#endif /* INCLUDE_GIF */

/**************************************************************************************
 * these are the "exported" production interface functions
 */

Image*
readGifFile ( FILE* infile )
{
  Image          *img = 0;

#if defined(INCLUDE_GIF)
  GifFileType    *gf;

  if ( !(gf = DGifOpenFileHandle( fileno( infile))) )
	return 0;

  img = readGif( gf);

  DGifCloseFile( gf);
#endif

  return img;
}


Image*
readGifData ( unsigned char* buf, long len )
{
  Image          *img = 0;
#if defined(INCLUDE_GIF)
  BufferSource   bufSrc;
  GifFileType    *gf;

  bufSrc.buf = bufSrc.p = buf;
  bufSrc.remain = len;

  if ( !(gf = DGifOpen( &bufSrc, readGifBuffer)) )
	return 0;

  img = readGif( gf);

  DGifCloseFile( gf);
  
#endif /* INCLUDE_GIF */

  return img;
}

#endif /* NO_NEED */