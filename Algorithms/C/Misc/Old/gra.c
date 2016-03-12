/**
 * gra.c - 
 *
 * Copyright (c) 1998
 *      Transvirtual Technologies, Inc.  All rights reserved.
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */

#include <ByteOrder.h>

#include "toolkit.h"

#include "jview.h"
#include "jwindow.h"

#include "graphics.h"


// be sure to sync these with java.awt.NativeGraphics
#define  TGT_TYPE_WINDOW   0
#define  TGT_TYPE_IMAGE    1
#define  TGT_TYPE_GRAPHICS 2

#define FLUSH(graphics)	 ((graphics)->drw->Flush())

/*******************************************************************************
 *
 */

AWT_EXPORT
void*
Java_java_awt_Toolkit_graInitGraphics ( JNIEnv* env, jclass clazz,
				Graphics* gr, jobject tgt, jint tgtType,
				jint xOff, jint yOff,
				jint xClip, jint yClip, jint wClip, jint hClip,
				jobject fnt, jint fg, jint bg, jboolean blank )
{
	jView *       drw;

	DBG( AWT_GRA, printf("initGraphics: %p (%p, %d) %d,%d "
				" %d,%d - %d,%d  %p %x %x\n",
				gr, tgt,tgtType, xOff,yOff, 
				xClip,yClip,wClip,hClip, fnt,fg,bg));

	if ( tgt ) {
	switch ( tgtType ) {
		case TGT_TYPE_WINDOW:  
			drw = (jView *)((Window)tgt)->FindView("_bkgnd_view_");
			break;     /* Window   */
		case TGT_TYPE_IMAGE:  
			drw = (jView *)((BBitmap *)((Image*)tgt)->bitmap)->FindView("_bkgnd_view_"); 
			break;     /* Image    */  
		case TGT_TYPE_GRAPHICS:  
			drw = ((Graphics*)tgt)->drw; 
			break;     /* Graphics */
		default: 
			fprintf( stderr, "illegal Graphics target: %d\n", tgtType);
			drw = 0;
	}
  }
  else {
	if ( gr )
	  drw = gr->drw;
	else {
	  fprintf( stderr, "attempt to set an uninitialized graphics");
	  drw = 0;
	}
  }

	DBG(AWT_GRA, printf("jView:%p\n", drw));

	rgb_color nbg = NATIVERGB(bg);
	rgb_color nfg = NATIVERGB(fg);
	 
	if (gr) {

	} else { 
		gr = new Graphics();
		DBG( AWT_GRA, printf(" ->gr: %p (%x)\n", gr, 0 /*gr->gc*/));
	}

	gr->fg   = nfg;
	gr->bg   = nbg;
	gr->drw  = drw;
	gr->x0   = xOff;
	gr->y0   = yOff;

    // remember that a bad deadlock can occur here if the BWindow/BLooper's 
    // thread isn't unlocked right after window creation
    if( drw->LockLooper() )
    {
       /* set graphics background color */
	   drw->SetViewColor(nbg);
	   drw->SetLowColor (nbg);
       drw->SetHighColor(nfg);

       /* set font */
       drw->SetFont((BFont *)fnt);

       drw->UnlockLooper();
    }

    /* set clipping rect */
#if CLIPPING_IS_WORKING
    gr->setClip(xClip, yClip, wClip, hClip);   
#endif

    gr->xor  = 0;
  
	if ( blank ) {
//		TOFIX();
		DBG(AWT_GRA, printf("!!! blank\n"));

        printf("Blanking out specified rect.....\n");
        if( drw->LockLooper() )
        {
           drw->SetHighColor(nbg);
           drw->FillRect( BRect(xOff+xClip, yOff+yClip, xOff+xClip+wClip, yOff+yClip+hClip) );
           drw->SetHighColor(nfg);
           
           drw->UnlockLooper();
        }
	}
  
	return gr;
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graFreeGraphics ( JNIEnv* env, jclass clazz, 
					Graphics* gr )
{
	DBG(AWT_GRA, printf("freeGraphics: %p\n", gr));

	delete gr ;
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graCopyArea ( JNIEnv* env, jclass clazz, 
					Graphics* gr, 
					jint x, jint y, 
					jint width, jint height,
					jint xDelta, jint yDelta )
{
	DBG(AWT_GRA, printf("copyArea: %p, %d,%d-%d,%d  %d,%d\n", gr, x,y,width,height, xDelta,yDelta));

/*
  x += gr->x0; y += gr->y0;
  XCopyArea( Tlk->dsp, gr->drw, gr->drw, gr->gc, x, y, width, height, x + xDelta, y + yDelta);
  XFLUSH( Tlk, False);
*/

	x += gr->x0; y += gr->y0;
	BView * vw = VIEW(gr);
	if (vw->LockLooper()) {	
		BRect src(x,y,x+width,y+height);  
    	vw->CopyBits( src, src.OffsetBySelf(BPoint(xDelta,yDelta)) );
    	vw->UnlockLooper();
	}
	FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graClearRect ( JNIEnv* env, jclass clazz, 
					Graphics* gr,
					jint x, jint y, 
					jint width, jint height )
{
  DBG(AWT_GRA, printf("clearRect: %p, %d,%d-%d,%d\n", gr, x,y,width,height));

  BView * vw = VIEW(gr);
  if (vw->LockLooper()) {	
  	vw->SetHighColor(gr->bg);
    x += gr->x0;
    y += gr->y0;
    vw->FillRect(BRect(x,y,x+width-1,y+height-1));
    vw->SetHighColor(gr->fg);
    vw->UnlockLooper();
  }
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawBytes ( JNIEnv* env, jclass clazz, Graphics* gr,
					 jarray jBytes, jint offset, jint len, jint x, jint y )
{
  jboolean isCopy;
  int      n;
  jbyte    *jb, *jbo;

  if ( !jBytes ) return;

  n = (*env)->GetArrayLength( env, jBytes);
  jb = (*env)->GetByteArrayElements( env, jBytes, &isCopy);
  jbo = jb + offset;

  DBG(AWT_GRA, printf("drawBytes: %p, %p,%d,%d  \"%s\"  %d,%d\n", gr,
				 jBytes,offset,len, jb, x,y));

  if ( offset+len > n )
	len = n - offset;

  BView * vw = VIEW(gr);
  if (vw->LockLooper())
  {
  	vw->MovePenTo(x+gr->x0, y+gr->y0);
  	vw->DrawString(jbo, len);
    vw->UnlockLooper();
  }
  
  (*env)->ReleaseByteArrayElements( env, jBytes, jb, JNI_ABORT);
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawChars ( JNIEnv* env, jclass clazz, Graphics* gr,
					 jarray jChars, jint offset, jint len, jint x, jint y )
{
  jboolean isCopy;
  int      n;
  jchar    *jc, *jco;
  char * b;
  
  if ( !jChars ) return;

  n   = (*env)->GetArrayLength( env, jChars);
  jc = (*env)->GetCharArrayElements( env, jChars, &isCopy);
  jco = jc + offset;

  DBG(AWT_GRA, printf("drawChars: %p, %p,%d,%d  \"%s\"  %d,%d\n", gr, jChars,offset,len,
				 jchar2CString(Tlk,jco,len), x,y));

  if ( offset+len > n )
	len = n - offset;

  // !!! burp
  b = (char *) jco;
  BView * vw = VIEW(gr);
  if (vw->LockLooper())
  {	  vw->MovePenTo(x+gr->x0, y+gr->y0);
  	  for(n=0;n<len;n++, b+=2)
  		vw->DrawString(b, 1);
  	  vw->UnlockLooper();
  }
  (*env)->ReleaseCharArrayElements( env, jChars, jc, JNI_ABORT);
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawString ( JNIEnv* env, jclass clazz,
					  Graphics* gr, jstring str, jint x, jint y )
{
  jboolean     isCopy;
  register int n = 0, len;
  const jchar  *jc;
  char * b;
  
  //DBG(AWT_GRA, printf("drawString: %p  \"%s\"  %d,%d\n", gr, java2CString(env,Tlk,str), x,y));

  if ( !str ) return;

  len = (*env)->GetStringLength( env, str);
  jc = (*env)->GetStringChars( env, str, &isCopy);

  b=(char *)jc;
  
  DBG(AWT_GRA, printf("drawString: len %d, %d \n", len, n));
//  for(n=0;n<2*len;n++) printf("%c",b[n]); 
  
  BView * vw = VIEW(gr);
  if (vw->LockLooper())
  {   vw->MovePenTo(x+gr->x0, y+gr->y0);
      // !!! WORLD-CLASS BURP
      for(n=0;n<len;n++, b+=2) vw->DrawString(b, 1);  
      vw->UnlockLooper();
  }

  (*env)->ReleaseStringChars( env, str, jc);
  FLUSH( gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawLine ( JNIEnv* env, jclass clazz, Graphics* gr,
					jint x1, jint y1, jint x2, jint y2 )
{
//TMP  DBG(AWT_GRA, printf("drawLine: %p, %d,%d - %d,%d\n", gr, x1,y1, x2,y2));

  BView * vw=VIEW(gr);
  if (vw->LockLooper())
  {   vw->StrokeLine(BPoint(x1+gr->x0,y1+gr->y0), BPoint(x2+gr->x0,y2+gr->y0));
      vw->UnlockLooper();
  }
  FLUSH(gr);  // !!! all output is flushed
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawArc ( JNIEnv* env, jclass clazz, Graphics* gr,
				   jint x, jint y, jint width, jint height,
				   jint startAngle, jint arcAngle )
{
  DBG(AWT_GRA, printf("drawArc: %p, %d,%d-%d,%d  %d,%d\n", gr,
				 x,y,width,height, startAngle,arcAngle));

  BView * vw= VIEW(gr);
  if (vw->LockLooper())
  {	  x += gr->x0;
      y += gr->y0;
      vw->StrokeArc(BRect(x, y, x+width-1, y+height-1), startAngle, arcAngle);
      vw->UnlockLooper();
  }
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graFillArc ( JNIEnv* env, jclass clazz, Graphics* gr,
				   jint x, jint y, jint width, jint height,
				   jint startAngle, jint arcAngle )
{
  DBG(AWT_GRA, printf("fillArc: %p, %d,%d-%d,%d  %d,%d\n", gr,
				 x,y,width,height, startAngle, arcAngle));

  BView * vw= VIEW(gr);
  if (vw->LockLooper())
  {	  x += gr->x0;
      y += gr->y0;
      vw->FillArc(BRect(x, y, x+width-1, y+height-1), startAngle, arcAngle);
      vw->UnlockLooper();
  }
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawOval ( JNIEnv* env, jclass clazz, Graphics* gr,
					jint x, jint y, jint width, jint height )
{
  DBG(AWT_GRA, printf("drawOval: %p, %d,%d - %d,%d\n", gr, x,y,width,height));

  BView * vw= VIEW(gr);
  if (vw->LockLooper())
  {	  x += gr->x0;
      y += gr->y0;
      vw->StrokeArc(BRect(x, y, x+width-1, y+height-1), 0, 360);
      vw->UnlockLooper();
  }
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graFillOval ( JNIEnv* env, jclass clazz, Graphics* gr,
					jint x, jint y, jint width, jint height )
{
  DBG(AWT_GRA, printf("fillOval: %p, %d,%d - %d,%d\n", gr, x,y,width,height));

  BView * vw= VIEW(gr);
  if (vw->LockLooper())
  {	  x += gr->x0;
      y += gr->y0;
      vw->FillArc(BRect(x, y, x+width-1, y+height-1), 0, 360);
      vw->UnlockLooper();
  }
  FLUSH(gr);
}

int jarray2Points ( JNIEnv* env, Toolkit* Tlk, BPoint** pp, int x0, int y0,
					jarray xPoints, jarray yPoints, int nPoints )
{
  register int i;
  int      n;
  jboolean isCopy;
  jint     *jx = (*env)->GetIntArrayElements( env, xPoints, &isCopy);
  jint     *jy = (*env)->GetIntArrayElements( env, yPoints, &isCopy);

  if ( (n = (*env)->GetArrayLength( env, xPoints)) < nPoints ) nPoints = n;
  if ( (n = (*env)->GetArrayLength( env, yPoints)) < nPoints ) nPoints = n;

  *pp = (BPoint *)getBuffer( Tlk, (nPoints+1)*sizeof(BPoint));

  for ( i=0; i<nPoints; i++){
	(*pp)[i].x = jx[i] + x0;
    (*pp)[i].y = jy[i] + y0;
  }

  (*env)->ReleaseIntArrayElements( env, xPoints, jx, JNI_ABORT);
  (*env)->ReleaseIntArrayElements( env, yPoints, jy, JNI_ABORT);

  return nPoints;
}

AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawPolygon ( JNIEnv* env, jclass clazz, Graphics* gr,
					   jarray xPoints, jarray yPoints, jint nPoints )
{
  BPoint *p;

  DBG(AWT_GRA, printf("drawPolygon: %p, %p,%p  %d\n", gr, xPoints, yPoints, nPoints));

  if ( !xPoints || !yPoints ) return;

  nPoints = jarray2Points( env, Tlk, &p, gr->x0, gr->y0, xPoints, yPoints, nPoints);

  BView * vw = VIEW(gr);
  if (vw->LockLooper())
  {   
      vw->StrokePolygon(p, nPoints, true);
      vw->UnlockLooper();
  }
  FLUSH(gr);  
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawPolyline ( JNIEnv* env, jclass clazz, Graphics* gr,
						jarray xPoints, jarray yPoints, jint nPoints )
{
  BPoint    *p;

  DBG(AWT_GRA, printf("drawPolyline: %p, %p,%p  %d\n", gr, xPoints, yPoints, nPoints));

  if ( !xPoints || !yPoints ) return;

  nPoints = jarray2Points( env, Tlk, &p, gr->x0, gr->y0, xPoints, yPoints, nPoints);

  BView *vw = VIEW(gr);
  if (vw->LockLooper())
  {
  	  vw->StrokePolygon(p, nPoints, false);
  	  vw->UnlockLooper();	
  }
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graFillPolygon ( JNIEnv* env, jclass clazz, Graphics* gr,
					   jarray xPoints, jarray yPoints, jint nPoints )
{
  BPoint * p;

  DBG(AWT_GRA, printf("fillPolygon: %p, %p,%p  %d\n", gr, xPoints, yPoints, nPoints));

  if ( !xPoints || !yPoints ) return;

  nPoints = jarray2Points( env, Tlk, &p, gr->x0, gr->y0, xPoints, yPoints, nPoints);

  BView *vw = VIEW(gr);
  if (vw->LockLooper())
  {
  	  vw->FillPolygon(p, nPoints);
  	  vw->UnlockLooper();	
  }
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawRect ( JNIEnv* env, jclass clazz, 
					Graphics* gr,
					jint x, jint y, 
					jint width, jint height )
{
	DBG(AWT_GRA, printf("drawRect: %p, %d,%d - %d,%d\n", gr, x,y,width,height));

	gr->drawRect( x, y, width, height );
/*  BView * vw = VIEW(gr);
  if ((width >= 0) && (height >= 0) && vw->LockLooper())
  {	x+=gr->x0;
    y+=gr->y0;
    vw->StrokeRect(BRect(x,y,x+width,y+height));
    vw->UnlockLooper();
  }
*/
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graFillRect ( JNIEnv* env, jclass clazz, Graphics* gr,
					jint x, jint y, jint width, jint height )
{
  DBG(AWT_GRA, printf("fillRect: %p, %d,%d - %d,%d\n", gr, x,y,width,height));

  BView * vw = VIEW(gr);
  if ((width >= 0) && (height >= 0) && vw->LockLooper())
  {	  
      x += gr->x0;
      y += gr->y0;
      if( width == 1)  // some swing gimmicks
         vw->StrokeLine( BPoint(x, y), BPoint(x, y+height-1) );
      else if( height == 1 )
         vw->StrokeLine( BPoint(x, y), BPoint(x+width-1, y) );
      else
         vw->FillRect(BRect(x,y,x+width-1,y+height-1));

      vw->UnlockLooper();
  }
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawRoundRect ( JNIEnv* env, jclass clazz, Graphics* gr,
					 jint x, jint y, jint width, jint height, 
					 jint wArc, jint hArc )
{
  DBG(AWT_GRA, printf("drawRoundRect: %p, %d,%d - %d,%d  %d,%d\n", gr,
				 x,y,width,height, wArc, hArc));
  
  BView * vw = VIEW(gr);
  if ((width >= 0) && (height >= 0) && vw->LockLooper())
  {	x+=gr->x0;
    y+=gr->y0;
    vw->StrokeRoundRect(BRect(x, y, x+width-1, y+height-1), wArc, hArc);
    vw->UnlockLooper();
  }
  FLUSH(gr);
}

AWT_EXPORT
void
Java_java_awt_Toolkit_graFillRoundRect ( JNIEnv* env, jclass clazz, Graphics* gr,
					 jint x, jint y, jint width, jint height, 
					 jint wArc, jint hArc )
{
  DBG(AWT_GRA, printf("fillRoundRect: %p, %d,%d - %d,%d  %d,%d\n", gr,
				 x,y,width,height, wArc, hArc));
  
  BView * vw = VIEW(gr);
  if ((width >= 0) && (height >= 0) && vw->LockLooper())
  {	x+=gr->x0;
    y+=gr->y0;
    vw->FillRoundRect(BRect(x, y, x+width-1, y+height-1), wArc, hArc);
    vw->UnlockLooper();
  }
  FLUSH(gr);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDraw3DRect ( JNIEnv* env, jclass clazz, Graphics* gr,
					  jint x, jint y, jint width, jint height,
					  jboolean raised, jint rgb )
{
  int      bright, dark; 
  int      xw, yh;

  DBG(AWT_GRA, printf("draw3DRect: %p, %d,%d - %d,%d  %d %x\n", gr,
				 x,y,width,height, raised, rgb));

  /* we should use the same mechanism like ordinary Graphics brighter()/darker() here */
  dark   = (int) (Java_java_awt_Toolkit_clrDark( env, clazz, rgb) >> 32);
  bright = (int) (Java_java_awt_Toolkit_clrBright( env, clazz, rgb) >> 32);

  // we don't have to subtract 1 from xw and yh here because the spec
  // says that draw3DRect is *supposed* to draw a rect that's one pixel
  // larger than the values passed in
  x += gr->x0; y += gr->y0;
  xw = x + width; 
  yh = y + height;

  BView *vw = VIEW(gr);
  if (vw->LockLooper())
  {	/* !!! ANYTHING TO OPTIMIZE ? :) */
    vw->SetHighColor(NATIVERGB((raised ? bright : dark)));
    vw->StrokeLine(BPoint(x, y), BPoint(xw-1, y));
    vw->StrokeLine(BPoint(x, y), BPoint(x, yh));
    
    vw->SetHighColor(NATIVERGB((raised ? dark : bright)));
    vw->StrokeLine(BPoint(x+1, yh), BPoint(xw, yh));
    vw->StrokeLine(BPoint(xw, y), BPoint(xw, yh));

    vw->SetHighColor(gr->fg);
    vw->UnlockLooper();
  }
}

AWT_EXPORT
void
Java_java_awt_Toolkit_graFill3DRect ( JNIEnv* env, jclass clazz, Graphics* gr,
					  jint x, jint y, jint width, jint height,
					  jboolean raised, jint rgb )
{
  DBG(AWT_GRA, printf("fill3DRect: %p, %d,%d - %d,%d  %d %x\n", gr,
				 x,y,width,height, raised, rgb));

  // !!! burp
  BView * vw = VIEW(gr);
  if (vw->LockLooper())
  {   
      jint x1 = x+gr->x0+1;
      jint y1 = y+gr->y0+1;
      vw->FillRect(BRect(x1,y1, x1+width-2, y1+height-2));
      vw->UnlockLooper();
  }
  Java_java_awt_Toolkit_graDraw3DRect( env, clazz, gr, x, y, width-1, height-1, raised, rgb);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graAddClip ( JNIEnv* env, jclass clazz, Graphics* gr,
				jint xClip, jint yClip, jint wClip, jint hClip )
{
	TOFIX();
	/* not implemented yet */
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graSetClip ( JNIEnv* env, jclass clazz, Graphics* gr,
				   jint xClip, jint yClip, jint wClip, jint hClip )
{
	DBG(AWT_GRA, printf("setClip: %p, %d,%d - %d,%d\n", gr, xClip, yClip, wClip, hClip));

	/* TEP, clipping is disabled here, 
	   we would need a hierarchical model of BViews
	   to handle this in the correct way,
	   but with our flat model (one view for all widgets),
	   this solution leads to problems 
	   - this will be addressed in the native widgets impl.
	     and maybe retrofitted here
	*/
#if CLIPPING_IS_WORKING
	gr->setClip( xClip, yClip, wClip, hClip );
#endif
}

AWT_EXPORT
void
Java_java_awt_Toolkit_graSetColor ( JNIEnv* env, jclass clazz, 
					Graphics* gr, 
					jint clr )
{
	DBG(AWT_GRA, printf("setColor: %p, %x\n", gr, clr));

	gr->setForeColor( NATIVERGB(clr) );
}

AWT_EXPORT
void
Java_java_awt_Toolkit_graSetBackColor ( JNIEnv* env, jclass clazz, Graphics* gr, jint clr )
{
	DBG(AWT_GRA, printf("setBackColor: %p, %x\n", gr, clr));

	gr->setBackColor( NATIVERGB(clr) );
}

AWT_EXPORT
void
Java_java_awt_Toolkit_graSetFont ( JNIEnv* env, jclass clazz, Graphics* gr, jobject fnt )
{
  DBG(AWT_GRA, printf("setFont: %p, %p\n", gr, fnt));

  FLUSH(gr);  // !!! added temporarily
  BView * vw = VIEW(gr);
  if (vw->LockLooper())
  {   vw->SetFont((BFont *)fnt);
      vw->UnlockLooper();
  }
}

AWT_EXPORT
void
Java_java_awt_Toolkit_graSetOffset ( JNIEnv* env, jclass clazz, Graphics* gr, jint xOff, jint yOff )
{
  DBG(AWT_GRA, printf("setOffset: %p, %d,%d\n", gr, xOff, yOff));

  gr->x0 = xOff;
  gr->y0 = yOff;
}

AWT_EXPORT
void
Java_java_awt_Toolkit_graSetPaintMode ( JNIEnv* env, jclass clazz, Graphics* gr )
{
  DBG(AWT_GRA, printf("setPaintMode: %p\n", gr));

  gr->setPaintMode();
}

AWT_EXPORT
void
Java_java_awt_Toolkit_graSetXORMode ( JNIEnv* env, jclass clazz, Graphics* gr, jint xorClr )
{
  DBG(AWT_GRA, printf("setXORMode: %p, %x\n", gr, xorClr));

  gr->setXORMode( NATIVERGB(xorClr) );
}

AWT_EXPORT
void
Java_java_awt_Toolkit_graSetVisible ( JNIEnv* env, jclass clazz, Graphics* gr, jint isVisible )
{
  DBG(AWT_GRA, printf("setVisble: %p  %d\n", gr, isVisible));
  
  /*
   * This is rather a hack to "defuse" a Graphics object, but we don't want to
   * add checks on every draw op to test if the target is invisible
   */
/*
  if ( !isVisible ) {
	if ( gr->y0 >= -10000 ) 
	  gr->y0 -= 100000;
  }
  else {
	if ( gr->y0 <= -10000 )
	  gr->y0 += 100000;
  }
*/
  printf("!!! setVisble: %p  %d\n", gr, isVisible);
  // !!! CHECK TWICE THE FOLLOWING
  gr->drw->Window()->Activate(isVisible);
}


/************************************************************************************
 * image rendering
 */

void
drawAlphaImage ( Graphics* gr, Image* img,
				 jint srcX, jint srcY, jint dstX, jint dstY,
				 jint width, jint height, jint bgval )
{

	TOFIX();

UNIMPLEMENTED((
  Image  *dstImg = 0;
  XImage *dstXim = 0;
  int    i, j, si, sj, alpha;
  unsigned long dpix, spix, bgpix = 0;
  int    sr, sg, sb, dr, dg, db;

  DBG(AWT_GRA, printf("drawAlphaImage: %p %x (%x, %x),  %d,%d  %d,%d  %d,%d  %x\n",
				 gr, img, img->xImg, img->alpha, srcX, srcY, dstX, dstY, width, height, bgval));

  if ( X->shm == USE_SHM ){
	dstImg = createImage( width, height);
	createXImage( X, dstImg);
	if ( dstImg->shmiImg ){
	  dstXim = dstImg->xImg;
	  XShmGetImage( X->dsp, gr->drw, dstXim, dstX, dstY, 0xffffffff);
	}
	else {  /* Shm failed, backup to normal XImage */
	  Java_java_awt_Toolkit_imgFreeImage( 0, 0, dstImg);
	  dstImg = 0;
	}
  }

  if ( !dstXim ) {
	dstXim = XGetImage( X->dsp, gr->drw, dstX, dstY, width, height, 0xffffffff, ZPixmap);
  }

  if ( bgval != -1 )
	bgpix = pixelValue( X, bgval);

  if ( dstXim ) {
	for ( j=0, sj=srcY; j<dstXim->height; j++, sj++ ) {
	  for ( i=0, si=srcX; i<dstXim->width; i++, si++ ) {
		dpix = (bgval == -1) ? XGetPixel( dstXim, i, j) : bgpix;
		spix = XGetPixel( img->xImg, si, sj);
		alpha = GetAlpha( img->alpha, si, sj);

		rgbValues( X, dpix, &dr, &dg, &db);

		if ( alpha ) {
		  /*
		   * ints still considered to be substantially faster than floats on most
		   * architectures (avoid div by 255), map all 0..255 -> 1..256
		   */
		  alpha++; sr++; sg++; sb++; dr++; dg++; db++;

		  rgbValues( X, spix, &sr, &sg, &sb);
		  dr = ((alpha * sr + (256 - alpha) * dr) + 128) >> 8;
		  dg = ((alpha * sg + (256 - alpha) * dg) + 128) >> 8;
		  db = ((alpha * sb + (256 - alpha) * db) + 128) >> 8;

		  dr--; dg--; db--;

		  XPutPixel( dstXim, i, j, pixelValue( X, (dr << 16)|(dg << 8)|(db) ));
		}
	  }
	}

	if ( dstImg != 0 ){
	  XShmPutImage( X->dsp, gr->drw, gr->gc, dstXim, 0, 0, dstX, dstY, width, height, False);
	  XSync( X->dsp, False);
	  Java_java_awt_Toolkit_imgFreeImage( 0, 0, dstImg);
	}
	else {
	  XPutImage( X->dsp, gr->drw, gr->gc, dstXim, 0, 0, dstX, dstY, width, height);
	  XFlush( X->dsp);
	  XDestroyImage( dstXim);
	}

	XFLUSH( X, True);
  }
));
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawImage ( JNIEnv* env, jclass clazz, Graphics* gr, Image* img,
					 jint srcX, jint srcY,
					 jint dstX, jint dstY,
					 jint width, jint height, jint bgval )
{
  DBG(AWT_IMG, printf("drawImage: %p %p (%p,%x,%x %d,%d) %d,%d, %d,%d, %d,%d, %x\n",
				 gr, img, img->bitmap, 0 /*img->xMask*/,0 /*img->alpha*/,  img->width, img->height,
				 srcX,srcY,  dstX,dstY,	 width,height, bgval));

  dstX += gr->x0;
  dstY += gr->y0;

  BView * vw = VIEW(gr);
  if (img && vw->LockLooper())
  {   
  	  drawing_mode saveMode = vw->DrawingMode();

      if ( bgval != -1 ) {
		vw->SetHighColor(NATIVERGB(bgval));
		vw->FillRect( BRect(dstX, dstY, dstX+width, dstY+height));
	  }

      if (img->trans<0)
      	vw->SetDrawingMode(B_OP_COPY);
      else {
      	vw->SetDrawingMode(B_OP_ALPHA);
      	vw->SetBlendingMode(B_PIXEL_ALPHA, B_ALPHA_OVERLAY);
      }	
      vw->DrawBitmap(img->bitmap, BPoint(dstX, dstY));
      vw->SetDrawingMode(saveMode);

      vw->UnlockLooper();
  }
  FLUSH(gr); 
}


AWT_EXPORT
void
Java_java_awt_Toolkit_graDrawImageScaled ( JNIEnv* env, jclass clazz, Graphics* gr, Image* img,
					   jint dx0, jint dy0, jint dx1, jint dy1,
					   jint sx0, jint sy0, jint sx1, jint sy1, jint bgval )
{
  DBG(AWT_IMG, printf("drawImageScaled: %p %p (%x), %d,%d,%d,%d, %d,%d,%d,%d, %x\n",
				 gr, img, 0/*img->xImg*/, dx0, dy0, dx1, dy1, sx0, sy0, sx1, sy1, bgval));
  dx0 += gr->x0;
  dx1 += gr->x0;
  dy0 += gr->y0;
  dy1 += gr->y0;

  BView * vw = VIEW(gr);
  if (img && vw->LockLooper())
  {   BRect dest(dx0,dy0,dx1,dy1);
      drawing_mode saveMode = vw->DrawingMode();
      if ( bgval != -1 ) {
		vw->SetHighColor(NATIVERGB(bgval));
		vw->FillRect(dest);
	  }

      if (img->trans<0)
      	vw->SetDrawingMode(B_OP_COPY);
      else {
      	vw->SetDrawingMode(B_OP_ALPHA);
      	vw->SetBlendingMode(B_PIXEL_ALPHA, B_ALPHA_OVERLAY);
      }	
      vw->DrawBitmap(img->bitmap, BRect(sx0,sy0,sx1,sy1), dest);
      vw->SetDrawingMode(saveMode);
      vw->UnlockLooper();
  }
  FLUSH(gr);   
}
