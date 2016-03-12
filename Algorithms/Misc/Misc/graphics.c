/**
 * graphics.h
 *
 *	(c) Copyright others....
 *	(c) Copyright Sim IJskes 1999
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */

#include "toolkit.h"

#include "graphics.h"

int Graphics::lock()
{
status_t res;
	view = VIEW(this);	// dirty
//	return view->LockLooper();
	res = view->LockLooperWithTimeout(5e6);  // !!! TIMING OUT, SIR
	DBG(AWT_GRA, if (res!=B_OK) printf("AWT_GRA LOCK FAILED\n") );
	return res == B_OK;
}

void Graphics::unlock()
{
	view->UnlockLooper();
}

void Graphics::setBackColor( rgb_color clr )
{
	backColor = clr ; 

	bg = backColor ; // REMOVE

	if( !lock() ) {
		return ;
	}

	view->SetViewColor(backColor);

	unlock();
}

void Graphics::setForeColor( rgb_color clr )
{
	foreColor = clr ; 

	fg = foreColor ; // REMOVE

	if( !lock() ) {
		return ;
	}

	view->SetHighColor( foreColor );

	unlock();
}

void Graphics::setPaintMode()
{
	xor = 0;
	if( !lock() ) {
		return;
	}

	view->SetLowColor(0xff, 0xff, 0xff);
	view->SetHighColor(foreColor);
	view->SetDrawingMode(B_OP_COPY);
	unlock();
}

void Graphics::setXORMode(rgb_color clr)
{
    xor = 1;
	if( !lock() ) {
		return;
	}
	xclr = clr;
	view->SetDrawingMode(B_OP_INVERT);
	view->SetLowColor( xclr );
	view->SetHighColor(foreColor);
	unlock();
}

void Graphics::setClip( int xClip, int yClip, int wClip, int hClip )
{
	// TODO SGY see how BeOS manages references here

#ifdef DEBUG
	// for debugging purpouses "scroll lock" disables clipping	
//	if (modifiers() & B_SCROLL_LOCK) return;
#endif

	BRect *rect = new BRect();

	xClip += x0 ;
	yClip += y0 ;

	rect->left = xClip ;
	rect->top = yClip ;
	rect->right = rect->left + wClip - 1 ;
	rect->bottom = rect->top + hClip - 1 ;

    newreg.Set( *rect );
	
	BRegion *region = new BRegion();

	if( lock() ) {   
	   view->GetClippingRegion( region );
       region->Exclude( &oldreg );
       region->Include( &newreg );	   
	   view->ConstrainClippingRegion( region );
       unlock();
    }

    oldreg = newreg;    

	delete region ;
	delete rect ;
}

void Graphics::drawRect( int x, int y, int width, int height )
{
//	if( (width >= 0) && (height >= 0) )

	if( !lock() ) {
		return ;
	}

	x += x0 ;
	y += y0 ;
	view->StrokeRect(BRect(x,y,x+width,y+height));
	view->Flush();

	unlock();
}
