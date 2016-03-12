/**
 * img.c - 
 *
 * Copyright (c) 1998
 *      Transvirtual Technologies, Inc.  All rights reserved.
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */

#include <StorageKit.h>
#include <TranslationKit.h>

#include "toolkit.h"

#if TODO

/* interfaces of image conversion functions */
Image* readGifFile ( FILE* );
Image* readGifData ( unsigned char*, long len );
Image* readJpegFile ( FILE* );
Image* readJpegData ( unsigned char*, long len );
Image* readPngFile ( FILE* );
Image* readPngData ( unsigned char*, long len );

#endif

/************************************************************************************
 * own auxiliary funcs
 */


Image*
createImage ( int width, int height )
{
  Image * img = (Image *) AWT_CALLOC( 1, sizeof( Image));

  img->trans  = -1;     /* default to no alpha */

  img->width = width;   /* we need to (temp) store them for subsequent X image creation */
  img->height = height;

  return img;
}

#if TODO  /* FOLLOWING FUNCTIONS DISABLED */

int
createShmXImage ( Toolkit* X, Image* img, int depth, int isMask )
{
  Visual  *vis = DefaultVisual( X->dsp, DefaultScreen( X->dsp));
  XShmSegmentInfo* shmi = (XShmSegmentInfo*) AWT_MALLOC( sizeof(XShmSegmentInfo));
  XImage *xim;
  unsigned int    nBytes;

  if ( isMask ) {
	xim = XShmCreateImage( X->dsp, vis, depth, XYBitmap, 0, shmi, img->width, img->height);
  }
  else {
    xim = XShmCreateImage( X->dsp, vis, depth, ZPixmap, 0, shmi, img->width, img->height);
  }

  nBytes = xim->bytes_per_line * img->height;
  shmi->shmid = shmget( IPC_PRIVATE, nBytes, (IPC_CREAT | 0777));

  /*
   * It is essential to check if shmget failed, because shared memory is usually
   * a scarce resource
   */
  if ( shmi->shmid == -1 ) {
	XShmDetach( X->dsp, shmi);
	xim->data = 0;
	XDestroyImage( xim);
	AWT_FREE( shmi);

	X->shm = SUSPEND_SHM;
	return 0;
  }

  xim->data = shmi->shmaddr = shmat( shmi->shmid, 0, 0);
  shmi->readOnly = False;
  XShmAttach( X->dsp, shmi);
  /*
   * make sure it will be freed automatically once the attachment count comes
   * down to 0 (either by explicit imgFreeImage or by process termination)
   */
  shmctl( shmi->shmid, IPC_RMID, 0);

  if ( isMask ) {
	memset( xim->data, 0xff, nBytes);
	img->shmiMask = shmi;
	img->xMask = xim;
  }
  else {
	img->shmiImg = shmi;
	img->xImg = xim;
  }

  return 1;
}


void
destroyShmXImage ( Toolkit* X, Image* img, int isMask )
{
  XShmSegmentInfo *shmi;
  XImage          *xim;

  if ( isMask ) {
	shmi = img->shmiMask;
	xim  = img->xMask;
	img->shmiMask = 0;
  }
  else {
	shmi = img->shmiImg;
	xim  = img->xImg;
	img->shmiImg = 0;
  }

  XShmDetach( X->dsp, shmi);
  xim->data = 0;
  XDestroyImage( xim);
  /* we created it as 'deleted', so we just have to detach here */
  shmdt( shmi->shmaddr);
  AWT_FREE( shmi);

  /* if we have suspended shm, give it a try again */
  if ( X->shm == SUSPEND_SHM )
	X->shm = USE_SHM;
}


void
createXImage ( Toolkit* Tlk, Image* img )
{
UNIMPLEMENTED((
  int bitmap_pad;
  int bytes_per_line;
  int bytes_per_pix;
  unsigned int nPix;
  char *data;
  Visual *vis  = DefaultVisual( X->dsp, DefaultScreen( X->dsp));
  int    depth = DefaultDepth(  X->dsp, DefaultScreen( X->dsp));
	
  if ( depth <= 8)	      bytes_per_pix = 1;
  else if ( depth <= 16)  bytes_per_pix = 2;
  else			          bytes_per_pix = 4;

  bytes_per_line = bytes_per_pix * img->width;
  bitmap_pad = bytes_per_pix * 8;
  nPix = img->width * img->height;

  if ( (X->shm == USE_SHM) && (nPix > X->shmThreshold) && (img->alpha == 0) ) {
	if ( createShmXImage( X, img, depth, False) ){
	  DBG( AWT_IMG, printf( "alloc Shm: %x %x %x (%dx%d) \n", img, img->xImg, img->shmiImg,
					  img->width, img->height));
	  return;
	}
  }

  data = AWT_CALLOC( nPix, bytes_per_pix);
  img->xImg = XCreateImage( X->dsp, vis, depth, ZPixmap, 0,
							data, img->width, img->height, bitmap_pad, bytes_per_line);
  DBG( AWT_IMG, printf( "alloc: %x %x (%dx%d)\n", img, img->xImg, img->width, img->height));
));
}

void
createXMaskImage ( Toolkit* X, Image* img )
{
  int     bytes_per_line;
  unsigned int nBytes, nPix;
  char    *data;
  Visual  *vis = DefaultVisual( X->dsp, DefaultScreen( X->dsp));

  bytes_per_line = (img->width + 7) / 8;
  nPix   = img->width * img->height;
  nBytes = bytes_per_line * img->height;

  if ( (X->shm == USE_SHM) && (nPix > X->shmThreshold) ) {
	if ( createShmXImage( X, img, 1, True) ){
	  DBG( AWT_IMG, printf( "alloc Shm mask: %x %x %x (%dx%d) \n", img, img->xMask, img->shmiMask,
					  img->width, img->height));
	  return;
	}
  }

  data = AWT_MALLOC( nBytes);
  memset( data, 0xff, nBytes);

  img->xMask = XCreateImage( X->dsp, vis, 1, XYBitmap, 0,
							 data, img->width, img->height, 8, bytes_per_line );
  DBG( AWT_IMG, printf( "alloc mask: %x %x (%dx%d)\n", img, img->xMask, img->width, img->height));
}


void
createAlphaImage ( Toolkit* Tlk, Image *img )
{
  int nBytes = img->width * img->height;

  img->alpha = AWT_MALLOC( sizeof( AlphaImage));

  img->alpha->width  = img->width;
  img->alpha->height = img->height;
  img->alpha->buf = AWT_MALLOC( nBytes);
  memset( img->alpha->buf, 0xff, nBytes);
}

/*
 * For images with a full alpha channel, check if we really need an alpha byte for
 * each pel, or if a mask bitmap (alpha 0x00 / 0xff) will be sufficient
 */
int
needsFullAlpha ( Toolkit* Tlk, Image *img, double threshold )
{
  int i, j, a;
  int n = 0, max;

  if ( !img->alpha ) return 0;

  max = (img->width * img->height) * threshold;

  for ( i=0; i<img->height; i++ ) {
	for ( j=0; j<img->width; j++ ) {
	  a = GetAlpha( img->alpha, j, i);
	  if ( (a != 0) && (a != 0xff) ) {
		if ( ++n > max )
		  return 1;
	  }
	}
  }

  return 0;
}

void
countAlphas ( Image *img, int* noAlpha, int* partAlpha, int* fullAlpha )
{
  int i, j, a;

  if ( !img->alpha ) return;

  for ( i=0; i<img->height; i++ ) {
	for ( j=0; j<img->width; j++ ) {
	  a = GetAlpha( img->alpha, j, i);
	  if ( a == 0 ) {
		(*noAlpha)++;
	  }
	  else if ( a == 0xff ) {
		(*fullAlpha)++;
	  }
	  else {
		(*partAlpha)++;
	  }
	}
  }
}

/*
 * A full alpha image channel is way slower than using a mask bitmap (= 0 / 0xff alpha).
 * This function provides a simple alpha-to-mask translation
 */
void
reduceAlpha ( Toolkit* Tlk, Image* img, int threshold )
{
  int i, j, a;

  if ( !img->alpha )
	return;

  createXMaskImage( Tlk, img);

  for ( i=0; i<img->height; i++ ) {
	for ( j=0; j<img->width; j++ ) {
	  a = GetAlpha( img->alpha, j, i);
	  if ( a < threshold ) {
		XPutPixel( img->xImg, j, i, 0);
		XPutPixel( img->xMask, j, i, 0);
	  }
	}
  }

  AWT_FREE( img->alpha->buf);
  AWT_FREE( img->alpha);
  img->alpha = 0;
}


__inline__ int
interpolate ( int ul, int ur, int ll, int lr, double dx, double dy )
{
  double u = ul + (double)(ur - ul) * dx;
  double l = ll + (double)(lr - ll) * dx;

  return (int) (u + (l - u) * dy  + 0.5);
}

unsigned int
getScaledAlpha ( Toolkit* Tlk, Image* img, int x, int y, double dx, double dy )
{
  int   ul, ur, ll, lr, a;
  int   xi = (dx) ? x+1 : x;
  int   yi = (dy) ? y+1 : y;

  if ( img->alpha ) {
	ul = GetAlpha( img->alpha, x, y);
	ur = GetAlpha( img->alpha, xi, y);
	ll = GetAlpha( img->alpha, x, yi);
	lr = GetAlpha( img->alpha, xi,yi);
	a = (unsigned int) interpolate( ul, ur, ll, lr, dx, dy);
	return a;
  }

  return 0xff;
}

long
getScaledPixel ( Toolkit* Tlk, Image* img, int x, int y, double dx, double dy )
{
  unsigned long  ul, ur, ll, lr;
  int            ulR, urR, llR, lrR, ulG, urG, llG, lrG, ulB, urB, llB, lrB, r, g, b;
  int            xi = (dx) ? x+1 : x;
  int            yi = (dy) ? y+1 : y;

  if ( img->xMask ) {
	ul = XGetPixel( img->xMask, x, y);
	ur = XGetPixel( img->xMask, xi, y);
	ll = XGetPixel( img->xMask, x, yi);
	lr = XGetPixel( img->xMask, xi,yi);
	
	if ( !interpolate( ul, ur, ll, lr, dx, dy) )
	  return -1;
  }

  ul = XGetPixel( img->xImg, x, y);
  ur = XGetPixel( img->xImg, xi, y);
  ll = XGetPixel( img->xImg, x, yi);
  lr = XGetPixel( img->xImg, xi,yi);


  if ( (ul == ur) && (ll == ul) && (lr == ll) ) {
	rgbValues( Tlk, ul, &r, &g, &b);
  }
  else {
	rgbValues( Tlk, ul, &ulR, &ulG, &ulB);
	rgbValues( Tlk, ur, &urR, &urG, &urB);
	rgbValues( Tlk, ll, &llR, &llG, &llB);
	rgbValues( Tlk, lr, &lrR, &lrG, &lrB);

	r = interpolate( ulR, urR, llR, lrR, dx, dy);
	g = interpolate( ulG, urG, llG, lrG, dx, dy);
	b = interpolate( ulB, urB, llB, lrB, dx, dy);
  }

  return pixelValue( Tlk, (r << 16) | (g << 8) | b);
}



void
initScaledImage ( Toolkit* Tlk, Image *tgt, Image *src,
				  int dx0, int dy0, int dx1, int dy1,
				  int sx0, int sy0, int sx1, int sy1 )
{
  double         xScale, yScale, sX, sY, sxDelta, syDelta;
  int            dx, dy, dxInc, dyInc, sx, sy;
  long           c;

  dxInc = (dx1 > dx0) ? 1 : -1;
  dyInc = (dy1 > dy0) ? 1 : -1;

  dx1 += dxInc;
  dy1 += dyInc;

  xScale = (double) (dx1 - dx0) / (double) (sx1 - sx0 +1);
  yScale = (double) (dy1 - dy0) / (double) (sy1 - sy0 +1);

  for ( dy=dy0; dy != dy1; dy += dyInc ) {
	sY = sy0 + (dy - dy0) / yScale;
	sy = (int) sY;
	syDelta = (sy < sy1) ? sY - sy : 0;

	for ( dx=dx0; dx != dx1; dx += dxInc ) {
	  sX = sx0 + (dx - dx0) / xScale;
	  sx = (int) sX;
	  sxDelta = (sx < sx1) ? sX - sx : 0;

	  if ( (c = getScaledPixel( Tlk, src, sx, sy, sxDelta, syDelta)) != -1 ){
  		XPutPixel( tgt->xImg, dx, dy, c);
		if ( src->alpha )
		  PutAlpha( tgt->alpha, dx, dy, getScaledAlpha( Tlk, src, sx, sy, sxDelta, syDelta));
	  }
	  else {
		XPutPixel( tgt->xMask, dx, dy, 0);
		XPutPixel( tgt->xImg, dx, dy, 0);
	  }
	}
  }
}
#endif /* TODO */


/************************************************************************************
 * exported native methods
 */


AWT_EXPORT
void*
Java_java_awt_Toolkit_imgCreateImage ( JNIEnv* env, jclass clazz, jint width, jint height )
{
  Image *img = createImage( width, height);
/**
  createXImage( X, img);
**/
  // !!! default to a 32 bit bitmap with an attached BView
  BBitmap * bmap = new BBitmap(BRect(0,0,width,height), B_RGB_32_BIT, true);   
  BView   * tmp  = new BView(BRect(0,0,width,height), "_bkgnd_view_", B_FOLLOW_ALL_SIDES, 0);
  if (bmap != NULL && bmap->Lock())
  {
    bmap->AddChild(tmp);
    tmp->StrokeRect(BRect(2,2,width-4,height-4));
    tmp->Sync();
    bmap->Unlock();
  }
  img->bitmap = bmap; 

DBG(AWT_IMG, printf("imgCreateImage: %p (%p)\n", img, img->bitmap));

  return img;
}


AWT_EXPORT
void*
Java_java_awt_Toolkit_imgCreateScreenImage ( JNIEnv* env, jclass clazz, jint width, jint height )
{
  Image  *img = createImage( width, height);

UNIMPLEMENTED((
  int    depth = DefaultDepth(  X->dsp, DefaultScreen( X->dsp));

  img->pix  = XCreatePixmap( X->dsp, X->root, width, height, depth);
));

  // !!! default to a 32 bit bitmap with an attached BView
  BBitmap * bmap = new BBitmap(BRect(0,0,width,height), B_RGB_32_BIT, true);   
  BView   * tmp  = new BView(BRect(0,0,width,height), "_bkgnd_view_", B_FOLLOW_ALL_SIDES, 0);
	if (bmap != NULL && bmap->Lock())
	{
		bmap->AddChild(tmp);
		tmp->StrokeRect(BRect(2,2,width-4,height-4));  
		tmp->Sync();
		bmap->Unlock();
	}
	img->bitmap = bmap; 

	DBG(AWT_IMG, printf("imgCreateScreenImage: %d,%d -> %p (%p) \n", width, height, img, img->bitmap ));
	return img;
}


/* generic (ImageProducer) based image construction */

typedef struct { uint8 alpha; uint8 red; uint8 green; uint8 blue; } pix32_little;
union  pix32   { pix32_little color; uint32 value; }; 

AWT_EXPORT
void
Java_java_awt_Toolkit_imgSetIdxPels ( JNIEnv* env, jclass clazz, Image * img,
									  jint x, jint y, jint w, jint h,
									  jarray clrMap, jarray idxPels, jint trans,
									  jint off, jint scan)
{
UNIMPLEMENTED((
  register int    row, col;
  unsigned long   pix;
  jint            rgb;
  jboolean        isCopy;
  jint            *clr = (*env)->GetIntArrayElements( env, clrMap, &isCopy);
  jbyte           *pel = (*env)->GetByteArrayElements( env, idxPels, &isCopy);
  unsigned char   *idx = (unsigned char*)(pel + off);
  int             maxCol = x + w;
  int             maxRow = y + h;
  unsigned char   curPel;

  if ( (trans >= 0) && !img->xMask )
	createXMaskImage( X, img);

  for ( row = y; row < maxRow; row++) {
    for ( col = x; col < maxCol; col++) {
      curPel = idx[col + row * scan];
      rgb = clr[curPel];
      pix = pixelValue( X, rgb);
      if ( trans >= 0 ) {
		if ( curPel == trans ){
		  pix = 0;
		  XPutPixel( img->xMask, col, row, 0);
		}
      }
      XPutPixel( img->xImg, col, row, pix);
    }
  }

  (*env)->ReleaseIntArrayElements( env, clrMap, clr, JNI_ABORT);
  (*env)->ReleaseByteArrayElements( env, idxPels, pel, JNI_ABORT);
));

DBG(AWT_IMG, printf("imgSetIdxPels\n"));
  register int    row, col;
//  unsigned long   pix;
/*  jint            rgb; */
  pix32           rgb;
  jboolean        isCopy;
  jint            *clr = (*env)->GetIntArrayElements( env, clrMap, &isCopy);
  jbyte           *pel = (*env)->GetByteArrayElements( env, idxPels, &isCopy);
  unsigned char   *idx = (unsigned char*)(pel + off);
  int             maxCol = x + w;  
  int             maxRow = y + h;  
  unsigned char   curPel;

/*
  if ( (trans >= 0) && !img->xMask )
	createXMaskImage( X, img);
*/
  if (img==NULL) return;
  
  rgb_color ctrans = B_TRANSPARENT_32_BIT;
  pix32 ptrans;
  
  if (trans >= 0) {
  	/* !!! transparency, WE COULD USE MASKS */
  	ptrans.color.red  = ctrans.red;
  	ptrans.color.green= ctrans.green;
  	ptrans.color.blue = ctrans.blue;
  	ptrans.color.alpha= 0; 
  	img->trans = 0;  /* enable alpha */
  }
  
  pix32 * data = (pix32*)img->bitmap->Bits();
  
  for ( row = y; row < maxRow; row++) {
    for ( col = x; col < maxCol; col++) {
      curPel = idx[col + row * scan];
      if (trans >= 0 && curPel == trans)
      	rgb = ptrans; 
      else
      {
      	rgb.value = clr[curPel];	
      }      
      data[col + row * scan + row] = rgb;    // !!! why our scanline is one pixel shorter ?
/*
      pix = pixelValue( X, rgb);
      if ( trans >= 0 ) {
		if ( curPel == trans ){
		  pix = 0;
		  XPutPixel( img->xMask, col, row, 0);
		}
      }
      XPutPixel( img->xImg, col, row, pix);
*/
	  	  
    }
  }
  
  (*env)->ReleaseIntArrayElements( env, clrMap, clr, JNI_ABORT);
  (*env)->ReleaseByteArrayElements( env, idxPels, pel, JNI_ABORT);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_imgSetRGBPels ( JNIEnv* env, jclass clazz, Image * img,
									  jint x, jint y, jint w, jint h,
									  jarray rgbPels, jint off, jint scan)
{

  register int    row, col;
  unsigned long   pix = 0;
  jboolean        isCopy;
  jint            *rgbs = (*env)->GetIntArrayElements( env, rgbPels, &isCopy);
  jint            *rgb = rgbs + off;
  int             maxCol = x + w;
  int             maxRow = y + h;
  jint		  val;

  pix32 * data = (pix32*)img->bitmap->Bits();

  for ( row = y; row < maxRow; row++) {
    for ( col = x; col < maxCol; col++) {
	  val = rgb[col + row * scan];
	  if ( (val & 0xff000000) == 0xff000000 ) {
		pix = pixelValue( Tlk, val);
		data[col + row * scan + row].value = pix;    // !!! why our scanline is one pixel shorter ?		
	  }
	  else {
        img->trans=0;	/* enable alpha */
		pix = pixelValue( Tlk, val);
		data[col + row * scan + row].value = val;    // !!! why our scanline is one pixel shorter ?		
        
#if 0  // !!! TODO, SUPPORT ALPHA
		debugger("Alpha unsupported\n");
		/*
		 * No way to tell for now if this will be a reduced (on/off) or a
		 * full alpha channel. We have to be prepared for the "worst", and reduce
		 * later
		 */
		if ( !img->alpha )
		  createAlphaImage( Tlk, img);
		PutAlpha( img->alpha, col, row, (val >> 24));
		XPutPixel( img->xImg, col, row, pix);

		/*
		if ( !img->xMask )
		  createXMaskImage( Tlk, img);
		XPutPixel( img->xMask, col, row, 0);
		XPutPixel( img->xImg, col, row, 0);
		*/
#endif
	  }
    }
  }

DBG(AWT_IMG, printf("imgSetRGBPels %p (%d,%d - %d,%d) %s\n", img, x, y, maxCol, maxRow, (img->trans>=0 ? "alpha" : "no alpha")));

  (*env)->ReleaseIntArrayElements( env, rgbPels, rgbs, JNI_ABORT);
}

AWT_EXPORT
void
Java_java_awt_Toolkit_imgComplete( JNIEnv* env, jclass clazz, Image * img, jint status )
{
UNIMPLEMENTED((
  /*
   * Check for alpha channel reduction. Note that full alpha images aren't created
   * with Shm (by policy), so you might loose the Shm speed factor. This method is just
   * called for external (generic) production, since our own prod facilities usually
   * know better if and how to do alpha support
   */
  if ( img->alpha &&  !needsFullAlpha( Tlk, img, 0.0) )
	reduceAlpha( Tlk, img, 128);
));
DBG(AWT_IMG, printf("imgComplete\n"));
}

AWT_EXPORT
void
Java_java_awt_Toolkit_imgFreeImage( JNIEnv* env, jclass clazz, Image * img)
{
DBG(AWT_IMG, printf("imgFreeImage\n"));
UNIMPLEMENTED((
  Image *next, *first = img;

  /* we have to be aware of image rings (GIF movies), iterate */
  do {
	if ( img->pix ){
	  XFreePixmap( X->dsp, img->pix);
	  img->pix = 0;
	}

	/*
	 * note that XDestroyImage automatically frees any non-NULL data pointer
	 * (since we explicitly allocated the data, we better free it explicitly, too)
	 * malloc, free might be resolved
	 */

	if ( img->xImg ){
	  if ( img->shmiImg ) {
		DBG( AWT_IMG, printf( "free Shm: %x %x %x (%dx%d)\n", img, img->xImg, img->shmiImg,
						img->width, img->height));
		destroyShmXImage( X, img, False);
	  }
	  else {
		DBG( AWT_IMG, printf( "free: %x %x (%dx%d)\n", img, img->xImg, img->width, img->height));
		AWT_FREE( img->xImg->data);
		img->xImg->data = 0;
		XDestroyImage( img->xImg);
	  }
	  img->xImg = 0;
	}

	if ( img->xMask ){
	  if ( img->shmiMask ) {
		DBG( AWT_IMG, printf( "free Shm mask: %x %x %x (%dx%d)\n", img, img->xMask, img->shmiMask,
						img->width, img->height));
		destroyShmXImage( X, img, True);
	  }
	  else {
		DBG( AWT_IMG, printf( "free mask: %x %x (%dx%d)\n", img, img->xMask,
						img->width, img->height));
		AWT_FREE( img->xMask->data);
		img->xMask->data = 0;
		XDestroyImage( img->xMask);
	  }
	  img->xMask = 0;
	}

	if ( img->alpha ) {
	  AWT_FREE( img->alpha->buf);
	  AWT_FREE( img->alpha);
	  img->alpha = 0;
	}

	next = img->next;
	AWT_FREE( img);
	img = next;
  } while ( (img != 0) && (img != first) );
));
}


AWT_EXPORT
void*
Java_java_awt_Toolkit_imgCreateScaledImage ( JNIEnv* env, jclass clazz,
											 Image* img, int width, int height )
{
UNIMPLEMENTED((
  int depth;

  Image *scaledImg = createImage( width, height);

  if ( img->xImg ) {
	createXImage( X, scaledImg);
	if ( img->xMask )
	  createXMaskImage( X, scaledImg);

	initScaledImage ( X, scaledImg, img,
					  0, 0, width-1, height-1,
					  0, 0, img->width-1, img->height-1);
  }
  else if ( img->pix ) {
	depth = DefaultDepth(  X->dsp, DefaultScreen( X->dsp));
	scaledImg->pix  = XCreatePixmap( X->dsp, X->root, width, height, depth);
  }

  return scaledImg;
));
  
  Image *scaledImg = createImage( width, height);

  // !!! default to a 32 bit bitmap with an attached BView
  BBitmap * bmap = new BBitmap(BRect(0,0,width,height), B_RGB_32_BIT, true);   
  BView   * tmp  = new BView(BRect(0,0,width,height), "_bkgnd_view_", B_FOLLOW_ALL_SIDES, 0);
  if (bmap != NULL && bmap->Lock())
  {
    bmap->AddChild(tmp);
    if (img!=NULL)
    	tmp->DrawBitmap(img->bitmap, BRect(0,0,width,height));
    tmp->Sync();
    bmap->Unlock();
  }
  img->bitmap = bmap; 

DBG(AWT_IMG, printf("imgCreateScaledImage %p (%d,%d) -> %p (%d,%d)\n", 
	img, img->height, img->width, scaledImg, height, width));
  return scaledImg;
}


AWT_EXPORT
void
Java_java_awt_Toolkit_imgProduceImage ( JNIEnv* env, jclass clazz, jobject producer, Image* img )
{
DBG(AWT_IMG, printf("imgProduceImage\n"));
	
  int       i, j;
//  int       r, g, b;
//  unsigned long pix;
  jclass    prodClazz, modelClazz;
  jmethodID modelCtor,setDim,setCM,setHints,setPix,imgCompl;
  jobject   model;
  jarray	pelArray;
  jint		*pels;
  jboolean  isCopy;
  
  prodClazz  = (*env)->GetObjectClass( env, producer);
//  jclass    modelClazz = (*env)->FindClass( env, "java/awt/image/ColorModel");
  modelClazz = (*env)->FindClass( env, "kaffe/awt/JavaColorModel");
  
//  jmethodID modelCtor = (*env)->GetStaticMethodID( env, modelClazz, "getRGBdefault", "()Ljava/awt/image/ColorModel;");
  modelCtor = (*env)->GetStaticMethodID( env, modelClazz, "getSingleton", "()Lkaffe/awt/JavaColorModel;");
  setDim    = (*env)->GetMethodID( env, prodClazz, "setDimensions", "(II)V");
  setCM     = (*env)->GetMethodID( env, prodClazz, "setColorModel", "(Ljava/awt/image/ColorModel;)V");
  setHints  = (*env)->GetMethodID( env, prodClazz, "setHints", "(I)V");
  setPix    = (*env)->GetMethodID( env, prodClazz, "setPixels", "(IIIILjava/awt/image/ColorModel;[III)V");
  imgCompl  = (*env)->GetMethodID( env, prodClazz, "imageComplete", "(I)V");

  model     = (*env)->CallStaticObjectMethod( env, modelClazz, modelCtor);

  /* for JDK compat, the pixel buffer has to be large enough to hold the *complete* image */
  pelArray  = (*env)->NewIntArray( env, img->width * img->height);
  pels = (*env)->GetIntArrayElements( env, pelArray, &isCopy);

  (*env)->CallVoidMethod( env, producer, setDim, img->width, img->height);
  (*env)->CallVoidMethod( env, producer, setCM, model);
  (*env)->CallVoidMethod( env, producer, setHints, 6); /* TOPDOWNLEFTRIGHT | COMPLETESCANLINES */

  for ( j=0; j<img->height; j++ ) {
	for ( i=0; i<img->width; i++ ) {
#if 0	// !!! TODO, MANAGE MASKS FOR REDUCED ALPHA IMAGES
	  if ( (img->xMask == 0) || XGetPixel( img->xMask, i, j) ) {
		pix = XGetPixel( img->xImg, i, j);
		rgbValues( X, pix, &r, &g, &b);
		pels[j*img->width+i] = (0xff000000 | (r << 16) | (g << 8) | b);
	  }
	  else
#endif
	  {
		pels[j*img->width+i] = 0;
	  }

	}
  }
  if ( isCopy ) {
    (*env)->ReleaseIntArrayElements( env, pelArray, pels, JNI_COMMIT);
  }

  (*env)->CallVoidMethod( env, producer, setPix, 0, 0, img->width, img->height, model, pelArray, 0, img->width);
  (*env)->CallVoidMethod( env, producer, imgCompl, 3); /* 3 = STATICIMAGEDONE */
}



/************************************************************************************
 * native format production dispatcher routines (GIF, jpeg, png, ..)
 */

#define SIG_LENGTH 4
#define SIG_GIF    1
#define SIG_JPEG   2
#define SIG_PNG    3

Image *unknownImage = 0;  /* fill in some default image here */

int imageFormat ( unsigned char* sig ) {
  if ( (sig[0] == 'G') && (sig[1] == 'I') && (sig[2] == 'F') )
	return SIG_GIF;

  if ( (sig[0] == 0xff) && (sig[1] == 0xd8) && (sig[2] == 0xff) && (sig[3] == 0xe0) )
	return SIG_JPEG;

  if ( (sig[0] == 0x89) && (sig[1] == 'P') && (sig[2] == 'N') && (sig[3] == 'G') )
	return SIG_PNG;

  return 0;
}

AWT_EXPORT
void*
Java_java_awt_Toolkit_imgCreateFromFile ( JNIEnv* env, jclass clazz, jstring fileName )
{
UNIMPLEMENTED((
  Image *img = 0;
  FILE  *infile;
  char  *fn = java2CString( env, X, fileName);
  unsigned char  sig[SIG_LENGTH];

  if ((infile = AWT_OPEN( fn, "rb")) != NULL) {
	if ( AWT_READ( sig, 1, sizeof(sig), infile) == sizeof(sig) ) {
	  AWT_REWIND( infile);  /* some native converters can't skip the signature read */

	  switch ( imageFormat( sig) ) {
	  case SIG_GIF:
		img = readGifFile( infile);
		break;
	  case SIG_JPEG:
		img = readJpegFile( infile);
		break;
	  case SIG_PNG:
		img = readPngFile( infile);
		break;
	  default:
		img = unknownImage;
	  }
	}
	AWT_CLOSE( infile);
  }

  return img;
));

  Image *img = 0;
/*  FILE  *infile; */
  char  *fn = java2CString( env, Tlk, fileName);

 	BFile file(fn, B_READ_ONLY); 
 	BTranslatorRoster *roster = BTranslatorRoster::Default(); 
 	BBitmapStream stream; 

 	
 	BBitmap *bmap = NULL;
 	if (roster->Translate(&file, NULL, NULL, &stream, B_TRANSLATOR_BITMAP) >= B_OK) 
	{
    	stream.DetachBitmap(&bmap);
		if (bmap) 
		{	
			BRect r = bmap->Bounds();
			img = createImage( (int) r.Width(), (int) r.Height());
			img->bitmap = bmap;
		}
	}

 	DBG(AWT_IMG, printf("imgCreateFromFile %s -> %p (%p)\n", fn, img, bmap));
	return img;		
}

AWT_EXPORT
void*
Java_java_awt_Toolkit_imgSetFrame ( JNIEnv* env, jclass clazz, Image* img, int frameNo )
{
	Image *imgCur = img;

 	DBG(AWT_IMG, printf("imgSetFrame %p %d\n", img, frameNo));

	if ( !img->next )
		return img;

	while ( img->frame != frameNo ) {
		img = img->next;
		if ( img == imgCur ) {
			break;
		}
	}
	return img;
}

AWT_EXPORT
void*
Java_java_awt_Toolkit_imgCreateFromData ( JNIEnv* env, jclass clazz,
										  jarray jbuffer, jint off, jint len )
{
UNIMPLEMENTED((
  Image *img = 0;
  jboolean isCopy;
  jint   length = (*env)->GetArrayLength( env, jbuffer);
  jbyte  *jb = (*env)->GetByteArrayElements( env, jbuffer, &isCopy);
  unsigned char *buf = (unsigned char*) jb + off;

  /* in case of a buffer overrun, we probably have a JPEG read error, anyway */
  if ( (off + len) <= length ) {
	switch ( imageFormat( buf) ) {
	case SIG_GIF:
	  img = readGifData( buf, len);
	  break;
	case SIG_JPEG:
	  img = readJpegData( buf, len);
	  break;
	case SIG_PNG:
	  img = readPngData( buf, len);
	  break;
	default:
	  img = unknownImage;
	}
  }

  (*env)->ReleaseByteArrayElements( env, jbuffer, jb, JNI_ABORT);
  return img;  
));

  Image *img = 0;
  jboolean isCopy;
  jint   length = (*env)->GetArrayLength( env, jbuffer);
  jbyte  *jb = (*env)->GetByteArrayElements( env, jbuffer, &isCopy);
/*  unsigned char *buf = (unsigned char*) jb + off; */

  /* in case of a buffer overrun, we probably have a JPEG read error, anyway */
/**
  if ( (off + len) <= length ) {
	switch ( imageFormat( buf) ) {
	case SIG_GIF:
	  img = readGifData( buf, len);
	  break;
	case SIG_JPEG:
	  img = readJpegData( buf, len);
	  break;
	case SIG_PNG:
	  img = readPngData( buf, len);
	  break;
	default:
	  img = unknownImage;
	}
  }
*/

  BBitmap *bmap = NULL;
  
  if ( (off+len) <= length)
  {
  	BMemoryIO buff(jb + off, len); 
  	BTranslatorRoster *roster = BTranslatorRoster::Default(); 
  	BBitmapStream stream; 
   
   
  	if (roster->Translate(&buff, NULL, NULL, &stream, B_TRANSLATOR_BITMAP) >= B_OK)
  	{
    	stream.DetachBitmap(&bmap);
    	if (bmap) 
    	{
       	BRect r = bmap->Bounds();
       	img = createImage( (int) r.Width(), (int) r.Height());
       	img->bitmap = bmap;
    	}
  	}
  }
  
  (*env)->ReleaseByteArrayElements( env, jbuffer, jb, JNI_ABORT);

  DBG(AWT_IMG, printf("imgCreateFromData %p %d %d -> %p (%p)\n", jb, off, len, img, bmap));

  return img;  

}


/************************************************************************************
 * field access
 */

AWT_EXPORT
jint
Java_java_awt_Toolkit_imgGetWidth ( JNIEnv* env, jclass clazz, Image* img)
{
  return img->width;
}

AWT_EXPORT
jint
Java_java_awt_Toolkit_imgGetHeight ( JNIEnv* env, jclass clazz, Image* img)
{
  return img->height;
}

AWT_EXPORT
jboolean
Java_java_awt_Toolkit_imgIsMultiFrame ( JNIEnv* env, jclass clazz, Image* img)
{
UNIMPLEMENTED((
  return (img->next != 0);
));
  return false; // !!!
}

AWT_EXPORT
jint
Java_java_awt_Toolkit_imgGetLatency ( JNIEnv* env, jclass clazz, Image* img)
{
UNIMPLEMENTED((
  return img->latency;
));
  return 0; // !!!
}

AWT_EXPORT
void*
Java_java_awt_Toolkit_imgGetNextFrame ( JNIEnv* env, jclass clazz, Image* img )
{
UNIMPLEMENTED((
  return img->next;   /* next in the ring */
));
  return NULL; // !!!
}
