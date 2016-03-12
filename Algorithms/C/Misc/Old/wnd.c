/**
 * wnd.c - native toplevel window related functions
 *
 * Copyright (c) 1998
 *      Transvirtual Technologies, Inc.  All rights reserved.
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */

/*
#include <limits.h>
*/
#include <AppKit.h>
#include "toolkit.h"

#include "jview.h"
#include "jwindow.h"


Cursor
getCursor ( jint jCursor )
{
	Cursor cursor;

// SGY: TODO remove Tlk->cursors field
//	if ( jCursor > 13 ) jCursor = 0;
//	if ( !(cursor = Tlk->cursors[jCursor]) ){

	switch ( jCursor ) {
		case  2: /*  2: TEXT_CURSOR        */
			cursor = (Cursor) B_I_BEAM_CURSOR; 
			break;
		case  0: /*  0: DEFAULT_CURSOR     */
		case  1: /*  1: CROSSHAIR_CURSOR   */
		case  3: /*  3: WAIT_CURSOR        */
		case  4: /*  4: SW_RESIZE_CURSOR   */
		case  5: /*  5: SE_RESIZE_CURSOR   */
		case  6: /*  6: NW_RESIZE_CURSOR   */
		case  7: /*  7: NE_RESIZE_CURSOR   */
		case  8: /*  8: N_RESIZE_CURSOR    */
		case  9: /*  9: S_RESIZE_CURSOR    */
		case 10: /* 10: W_RESIZE_CURSOR    */
		case 11: /* 11: E_RESIZE_CURSOR    */
		case 12: /* 12: HAND_CURSOR        */
		case 13: /* 13: MOVE_CURSOR        */
		default: 
			cursor = (Cursor) B_HAND_CURSOR;
	}

//	cursor = Tlk->cursors[jCursor] = XCreateFontCursor( Tlk->dsp, shape);
//	}
	return cursor;
}


AWT_EXPORT
void
Java_java_awt_Toolkit_wndSetTitle ( JNIEnv* env, jclass clazz, void* wnd, jstring jTitle )
{
	JavaWindow *w = (JavaWindow*)wnd ;

	if( jTitle ) {
		Java2CString title(env,jTitle);

		DBG( AWT_WND, printf("setTitle: %p, \"%s\"\n", wnd, title.toChars()));

		w->SetTitle( title.toChars() );
	} else {
		w->SetTitle( "" );
	}
}


AWT_EXPORT
void
Java_java_awt_Toolkit_wndSetResizable ( JNIEnv* env, jclass clazz, void* wnd, 
					jboolean isResizable,
					int x, int y, int width, int height )
{
	DBG( AWT_WND, printf("setResizable: %p, %d, %d,%d,%d,%d\n", wnd, isResizable, x,y,width,height));

	TOFIX();
	isResizable = 1 ;	 // somehow AWT does not pass the right value
	((JavaWindow*)wnd)->SetResizable( isResizable );
}

Window
createWindow ( JNIEnv* env, jclass clazz, void* owner, 
		jint x, jint y, jint width, jint height,
		jint jCursor, jint clrBack, jboolean isResizable, int type )
{
	JavaWindow *wnd;

//	if ( width <= 0 )  width = 1;
//	if ( height <= 0 ) height = 1;

	uint32 flags = B_NOT_ZOOMABLE ;

	BRect frame;

	/* for menus and drop-down windows, make coordinates relative to
	parent window; otherwise just use coordinates passed to function */
	if (type == WND_WINDOW) {
	   frame = ((BWindow *)owner)->Frame();
	   frame.left += x;
	   frame.top += y;
	   frame.right = frame.left + width;
	   frame.bottom = frame.top + height; 
	}
	else
	   frame = BRect(x, y, x+width, y+height);
	
	wnd = new JavaWindow( frame, NULL, B_TITLED_WINDOW, flags );

	DBG( AWT_WND, printf("CreateWindow %d,%d,%d,%d %d -> %p\n", 
				x, y, width, height, isResizable, wnd));

	switch( type ) {
		case WND_FRAME :
			wnd->SetLook( B_TITLED_WINDOW_LOOK );
			wnd->SetFeel( B_NORMAL_WINDOW_FEEL );
			break ;
		case WND_DIALOG :
			wnd->SetLook( B_MODAL_WINDOW_LOOK );
			break ;
		case WND_WINDOW :
			wnd->SetLook( B_NO_BORDER_WINDOW_LOOK );
			// we don't want a menu or drop-down list to take focus away from
			// the parent window, so we should give it a floating app feel
			wnd->SetFeel( B_FLOATING_APP_WINDOW_FEEL );
			break ;
	} 

	if( wnd == 0 ) {
		TOFIX();
		// abort with exception throw
		return 0;
	}

	DBG(AWT_WND, wnd->Bounds().PrintToStream());

	/* every window gets a background view to draw onto */
	BView * vw = new jView(wnd->Bounds(), "_bkgnd_view_", B_FOLLOW_ALL | B_FULL_UPDATE_ON_RESIZE, B_WILL_DRAW);
	wnd->AddChild(vw);

	if (vw->LockLooper()) 
	{	
		DBG(AWT_WND, printf( "after lock looper" ));
		vw->SetViewColor(NATIVERGB(clrBack));	/* set the background color */ 
		vw->MakeFocus(true);					/* get ready for input */
		vw->UnlockLooper();
	}

	wnd->SetResizable( isResizable );

    // We unlock the Window's BLooper before its first Show() because
    // we want to let the Java app handle its own shows and hides
    // ! This replaces the ugly hack that called Show(), then Hide() immediately
    // afterwards to avoid the potential deadlock in graInitGraphics()
    // that happens right after Window creation !
    wnd->BLooper::Run();

	return wnd;
}

/*
 * We register here (and not in evt.c, during evtRegisterSource) because
 * we want to be able to store attributes (flags, owner), without being
 * forced to use fancy intermediate cache mechanisms (or intermediate
 * register states). Storing own Window attributes (flags, owners) in the native
 * layer is essential for mechanisms like the popup focus forwarding, but can
 * be used in other places (like inset detection and mapping) as well, to avoid
 * costly round-trips or additional state passed in from the Java side
 */
int
registerSource ( Toolkit* Tlk, Window wnd, Window owner, int flags)
{
  int i = getFreeSourceIdx( Tlk, wnd);

  if ( i >= 0 ) {
/* !!!
	Tlk->windows[i].w = wnd;
	Tlk->windows[i].flags = flags;
	Tlk->windows[i].owner = owner;
*/
	Tlk->windows[i] = wnd;
	return i;
  }
  else {
	DBG( AWT_EVT, printf("window table out of space: %d", Tlk->nWindows));
	return -1;
  }
}

AWT_EXPORT
void*
Java_java_awt_Toolkit_wndCreateFrame ( JNIEnv* env, jclass clazz, 
		jstring jTitle, jint x, jint y, jint width, jint height,
		jint jCursor, jint clrBack, jboolean isResizable )
{
	DBG( AWT_WND, printf("createFrame( %p, %d,%d,%d,%d,..)\n", 
		jTitle,x,y,width,height));

	TOFIX();

	JavaWindow *w = createWindow( env, clazz,  
			0, x, y, width, height,
			jCursor, clrBack, isResizable, WND_FRAME );

	if ( w )
		registerSource( Tlk, w, 0, WND_FRAME);

	if( jTitle ) {
		Java2CString title(env,jTitle);

		w->SetTitle( title.toChars() );
	}

	DBG(AWT_WND, printf( "wndCreateFrame() -> %p\n", w ));

	return w ;
}


AWT_EXPORT
void*
Java_java_awt_Toolkit_wndCreateWindow ( JNIEnv* env, jclass clazz, 
	void* owner, jint x, jint y, jint width, jint height,
	jint jCursor, jint clrBack )
{
	DBG( AWT_WND, printf("createWindow( %p, %d,%d,%d,%d,..)\n", 
			owner,x,y,width,height));

	TOFIX();

	JavaWindow *w = createWindow( env, clazz,  
		owner, x, y, width, height,
		jCursor, clrBack, JNI_TRUE, WND_WINDOW );
	
	if ( w )
		registerSource( Tlk, w, (Window)owner, WND_WINDOW);

	w->SetParent( (BWindow*)owner );

	DBG(AWT_WND, printf( "wndCreateWindow() -> %p\n", w ));

	return w ;
}


AWT_EXPORT
void*
Java_java_awt_Toolkit_wndCreateDialog ( JNIEnv* env, jclass clazz, 
	void* owner, jstring jTitle, jint x, jint y, jint width, jint height,
	jint jCursor, jint clrBack, jboolean isResizable )
{
	DBG( AWT_WND, printf("createDialog( %p,%p, %d,%d,%d,%d,..)\n", 
			owner,jTitle,x,y,width,height));

	TOFIX();

	JavaWindow *w = createWindow( env, clazz,  
			owner, x, y, width, height,
			jCursor, clrBack, isResizable, WND_DIALOG );

	if ( w )
		registerSource( Tlk, w, (Window)owner, WND_DIALOG);

	if( jTitle ) {
		Java2CString title(env,jTitle);

		w->SetTitle( title.toChars() );
	}

	w->SetParent( (BWindow*)owner );

	return w ;
}


AWT_EXPORT
void
Java_java_awt_Toolkit_wndDestroyWindow ( JNIEnv* env, jclass clazz, Window wnd )
{
	DBG( AWT_WND, printf("destroy window: %p\n", wnd));

	BWindow * w = (BWindow *)wnd;

	w->Sync();
	w->Hide();
	if (w->Lock()) {
		w->Quit();
		// now w is gone and w points to nothing
	} else {
		printf("lock failed\n" );
		TOFIX();
	}
}


AWT_EXPORT
void
Java_java_awt_Toolkit_wndRequestFocus ( JNIEnv* env, jclass clazz, Window wnd )
{
	DBG( AWT_WND, printf("request focus: %p\n", wnd));

	TOFIX();
	
	((BWindow *)wnd)->Sync();
	((BWindow *)wnd)->Activate();
}


/*
 * We shift possible Frame / Dialog deco adaptions back to Java, because (in
 * order to get more compatible with JDK behavior) we not only have to apply
 * offsets in wndSetWindowBounds, but also when getting back via ComponentEvents
 * (ConfigureNotify), and during recursive child painting (to adapt the toplevel Graphics).
 * Since we don't have the window type info (frame / dialog / window)
 * in the native lib, this has to be done in the Java layer. In order to do it
 * all on one side, this means to shift the size adaption out of wndSetWindowBounds, too.
 *
 * Therefor Default frame/dialog Insets become the pivotal info, being passed into
 * the native lib as a (configurable 'Defaults') guess, turned into exact values
 * (of Frame.frameInsets, Dialog.dialogInsets) by means of native-to-Java callbacks,
 * computed during initial Frame/Dialog creation
 */

AWT_EXPORT
void
Java_java_awt_Toolkit_wndSetFrameInsets ( JNIEnv* env, jclass clazz,
										  jint top, jint left, jint bottom, jint right )
{
  Tlk->frameInsets.top  = top;
  Tlk->frameInsets.left = left;
  Tlk->frameInsets.bottom = bottom;
  Tlk->frameInsets.right = right;
  Tlk->frameInsets.guess = 1;
}

AWT_EXPORT
void
Java_java_awt_Toolkit_wndSetDialogInsets ( JNIEnv* env, jclass clazz,
										  jint top, jint left, jint bottom, jint right )
{
  Tlk->dialogInsets.top  = top;
  Tlk->dialogInsets.left = left;
  Tlk->dialogInsets.bottom = bottom;
  Tlk->dialogInsets.right = right;
  Tlk->dialogInsets.guess = 1;
}

AWT_EXPORT
void
Java_java_awt_Toolkit_wndSetBounds ( JNIEnv* env, jclass clazz, void* wnd,
				 jint x, jint y, jint width, jint height,
				 jboolean isResizable )
{
	DBG( AWT_WND, printf("setBounds: %p %d,%d,%d,%d\n", 
			wnd, x, y, width, height));

//	if ( width < 0 )  width = 1;
//	if ( height < 0 ) height = 1;

	((JavaWindow*)wnd)->SetBounds( x, y, width, height );
}

AWT_EXPORT
void
Java_java_awt_Toolkit_wndRepaint ( JNIEnv* env, jclass clazz, Window wnd,
				   jint x, jint y, jint width, jint height )
{
	DBG( AWT_WND, printf("wndRepaint: %p %d,%d,%d,%d\n", 
			wnd, x, y, width, height));

	BView * bgnd = ((BWindow *)wnd)->FindView("_bkgnd_view_");

	if (bgnd) {
		bgnd->Invalidate(BRect(x, y, x+width, y+height));
	}
}

AWT_EXPORT
void
Java_java_awt_Toolkit_wndSetIcon ( JNIEnv* env, jclass clazz, void* wnd, void* img )
{
	DBG( AWT_WND, printf("setIcon: %p \n", wnd));

	TOFIX();
}


AWT_EXPORT
void
Java_java_awt_Toolkit_wndSetVisible ( JNIEnv* env, jclass clazz, Window wnd, jboolean showIt )
{
	DBG( AWT_WND, printf("setVisible: %p %d\n", wnd, showIt));

	wnd->SetVisible( showIt );
}


AWT_EXPORT
void
Java_java_awt_Toolkit_wndToBack ( JNIEnv* env, jclass clazz, void* wnd )
{
	DBG( AWT_WND, printf("toBack: %p\n", wnd));

	((BWindow *)wnd)->Activate(false);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_wndToFront ( JNIEnv* env, jclass clazz, void* wnd )
{
	DBG( AWT_WND, printf("toFront: %p\n", wnd));

	((BWindow *)wnd)->Activate(true);
}


AWT_EXPORT
void
Java_java_awt_Toolkit_wndSetCursor ( JNIEnv* env, jclass clazz, void* wnd, jint jCursor )
{
	DBG( AWT_WND, printf("setCursor: %p, %d\n", wnd, jCursor));
	
	be_app->SetCursor( getCursor(jCursor) );
}

