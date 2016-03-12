/**
 * jwindow.c 
 *	
 *	(c) Copyright 1999 Sim IJskes
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */

#include <AppKit.h>

#include "jwindow.h"
#include "japp.h"

#include "toolkit.h"

#define DEBUG
#undef DEBUG

JavaWindow::JavaWindow(BRect frame, const char *title, window_type type, uint32 flags, 
			uint32 workspaces = B_CURRENT_WORKSPACE) : 
	BWindow(frame, title, type, flags, workspaces)
{
}

JavaWindow::~JavaWindow()
{
//	Event( COMPONENT_HIDDEN );
	Event( WINDOW_CLOSED );
}

void JavaWindow::MouseMovedEvent( BMessage *message )
{
	int32 transit = 99 ;

	message->FindInt32( "be:transit", &transit );

	if( transit == B_ENTERED_VIEW ) {
		MsgEvent( MOUSE_ENTER, message );
		MsgEvent( MOUSE_MOVE, message );
	} else if( transit == B_EXITED_VIEW ) {
		MsgEvent( MOUSE_MOVE, message );
		MsgEvent( MOUSE_EXIT, message );
	} else {
		// B_INSIDE_VIEW
		MsgEvent( MOUSE_MOVE, message );
	}
}

void JavaWindow::DispatchMessage(BMessage *message, BHandler *target)
{
#ifdef DEBUG
	printf( ">>> window\n" );

	message->PrintToStream();
#endif

	BWindow::DispatchMessage( message, target );	

	switch( message->what ) {
		case B_KEY_DOWN :
			MsgEvent( KEY_PRESS, message );
			break ;
		case B_KEY_UP :
			MsgEvent( KEY_RELEASE, message );
			break ;

		case B_MOUSE_MOVED :
			MouseMovedEvent( message );
			break ;
		case B_MOUSE_UP :
			MsgEvent( MOUSE_UP, message );
			break ;
		case B_MOUSE_DOWN :
			MsgEvent( MOUSE_DOWN, message );
			break ;

		case _UPDATE_ :
			// TODO, update reactangle?
			Event( UPDATE );
			break ;
		case _EVENTS_PENDING_ :
			//debugger( "events pending" );
			break ;
	}

#ifdef DEBUG
	printf( "window <<<<\n" );
#endif
}

void JavaWindow::FrameResized(float width, float height)
{
	BWindow::FrameResized( width, height );
	Event( COMPONENT_RESIZED );
}

void JavaWindow::FrameMoved(BPoint screenPoint)
{
	BWindow::FrameMoved(screenPoint);
	Event( COMPONENT_MOVED );
}

void JavaWindow::WindowActivated(bool active)
{
	BWindow::WindowActivated(active);

	if( active ) {
		// do not send WINDOW_ACTIVATED, it is send by the AWT itself
		// but: the events arive at the application in the wrong order,
		// compared to the reference platform.
		Event( FOCUS_GAINED );
	} else {
		Event( FOCUS_LOST );
	}
}

void JavaWindow::Minimize(bool minimize)
{
	// be carefull, documentation seems to say that it's not a dummy hook
	// maybe intercept at messageloop here

	BWindow::Minimize( minimize );

	if( minimize ) {
		Event( WINDOW_ICONIFIED ); 
	} else {
		Event( WINDOW_DEICONIFIED ); 
	}
}

bool JavaWindow::QuitRequested(void)
{
	Event( WINDOW_CLOSING );
	return false ;
}

void JavaWindow::Event( int evtId )
{
#ifdef DEBUG
	printf( "JavaWindow::Event(%d)\n", evtId );
#endif
	javaApp->MsgEvent( this, evtId, CurrentMessage() );
}

void JavaWindow::MsgEvent( int evtId, BMessage *msg )
{
#ifdef DEBUG
	printf( "JavaWindow::MsgEvent(%d)\n", evtId );
#endif
	javaApp->MsgEvent( this, evtId, msg );
}

/////////////////////////////////////////
// wnd interfacing

void JavaWindow::SetResizable( bool sw )
{
	uint32 flags = Flags();

	flags &= ~B_NOT_RESIZABLE ;

	if( !sw ) {
		flags = B_NOT_RESIZABLE ;
	}

	SetFlags( flags );
}

void JavaWindow::SetBounds( int x, int y, int w, int h )
{
	MoveTo( x, y );
	ResizeTo( w, h );
}

void JavaWindow::SetVisible( bool sw )
{
	Lock();
	if( sw ) {
		Show();
	} else {
		Hide();
	}  
	Unlock();
}

void JavaWindow::SetParent( BWindow *wnd )
{
	wnd->AddToSubset( this );
}

// wnd interfacing
/////////////////////////////////////////

