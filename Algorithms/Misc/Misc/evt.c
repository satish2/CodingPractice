/**
 * evt.c - 
 *
 * Copyright (c) 1998
 *      Transvirtual Technologies, Inc.  All rights reserved.
 *
 * Copyright (c) 1999 Sim IJskes
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */


#include <AppKit.h>

#include "toolkit.h"
#include "keysyms.h"

#include "jview.h"
#include "jwindow.h"
#include "japp.h"

#define MANAGE_BACKLOGS		0


#if !defined(USE_POLLING_AWT)
#include "jsyscall.h"
#include "../../../../kaffe/kaffevm/locks.h"
#endif /* !USE_POLLING_AWT */

/* X-to-Java key modifier mapping
 *                                     altGr   : PC
 *     shift       -    ctrl     alt    meta   : Java
 *     Shift    Lock    Ctrl    Mod1    Mod3   : X      symbol
 *  ----------------------------------------------------------
 *         1       1       2       8       4   : Java   value
 *         1       2       4       8      32   : X
 */

#define SHIFT_MASK	1
#define CTRL_MASK	2
#define META_MASK	4
#define ALT_MASK	8

__inline__ int keyMod ( int keyState )
{
  int mod = 0;
  if ( keyState & 3 ) mod |= 1; /* shift or lock */
  if ( keyState & 4 ) mod |= 2;
  if ( keyState & 8 ) mod |= 8;
  return mod;
}


jclass     AWTEvent;
jclass     ComponentEvent;
jclass     MouseEvent;
jclass     FocusEvent;
jclass     WindowEvent;
jclass     KeyEvent;
jclass     PaintEvent;
jclass     WMEvent;

jmethodID  getComponentEvent;
jmethodID  getMouseEvent;
jmethodID  getFocusEvent;
jmethodID  getWindowEvent;
jmethodID  getKeyEvent;
jmethodID  getPaintEvent;
jmethodID  getWMEvent;

jmethodID  sendEvent;

#define    KEY_PRESSED          401
#define    KEY_RELEASED         402

#define    PAINT                800

#define    WM_KILLED           1905

//#if defined(DEBUG)
static char *eventStr ( int evtId )
{
	switch (evtId) {
		case COMPONENT_RESIZED: return "ComponentResized";
		case COMPONENT_MOVED: return "ComponentMoved";

		case WINDOW_CLOSING: return "WindowClosing";
		case WINDOW_CLOSED: return "WindowClosed";
		case WINDOW_ICONIFIED: return "WindowIconified";
		case WINDOW_DEICONIFIED: return "WindowDeiconified";

		case KEY_PRESSED: return "KeyPressed";
		case KEY_RELEASED: return "KeyReleased";

		case MOUSE_DOWN: return "MouseDown";
		case MOUSE_UP: return "MouseUp";
		case MOUSE_MOVE: return "MouseMove";
		case MOUSE_ENTER: return "MouseEnter";
		case MOUSE_EXIT: return "MouseExit";

		case PAINT: return "Paint";
		case UPDATE: return "Update";
	
		case FOCUS_GAINED: return "FocusGained";
		case FOCUS_LOST: return "FocusLost";

		case WM_KILLED: return "WMKilled";

		default: return "<unknown>";
	}
};
//#endif


AWT_EXPORT
jobject
Java_java_awt_Toolkit_evtInit ( JNIEnv* env, jclass clazz )
{
	jclass Component;

	if ( ComponentEvent != NULL ){
		DBG( AWT_EVT, printf("evtInit called twice\n"));
		return NULL;
  	}
  	
	ComponentEvent = (*env)->FindClass( env, "java/awt/ComponentEvt");
	MouseEvent     = (*env)->FindClass( env, "java/awt/MouseEvt");
	FocusEvent     = (*env)->FindClass( env, "java/awt/FocusEvt");
	WindowEvent    = (*env)->FindClass( env, "java/awt/WindowEvt");
	KeyEvent       = (*env)->FindClass( env, "java/awt/KeyEvt");
	PaintEvent     = (*env)->FindClass( env, "java/awt/PaintEvt");
	WMEvent        = (*env)->FindClass( env, "java/awt/WMEvent");

	getComponentEvent = (*env)->GetStaticMethodID( env, ComponentEvent, "getEvent", 
													"(IIIIII)Ljava/awt/ComponentEvt;");
	getMouseEvent     = (*env)->GetStaticMethodID( env, MouseEvent, "getEvent", 
													"(IIIII)Ljava/awt/MouseEvt;");
	getFocusEvent     = (*env)->GetStaticMethodID( env, FocusEvent, "getEvent",
													"(IIZ)Ljava/awt/FocusEvt;");
	getWindowEvent    = (*env)->GetStaticMethodID( env, WindowEvent, "getEvent",
													"(II)Ljava/awt/WindowEvt;");
	getKeyEvent       = (*env)->GetStaticMethodID( env, KeyEvent, "getEvent",
													"(IIIII)Ljava/awt/KeyEvt;");
	getPaintEvent     = (*env)->GetStaticMethodID( env, PaintEvent, "getEvent",
													"(IIIIII)Ljava/awt/PaintEvt;");
	getWMEvent        = (*env)->GetStaticMethodID( env, WMEvent, "getEvent",
													"(II)Ljava/awt/WMEvent;");  	

UNIMPLEMENTED((
#if !defined(USE_POLLING_AWT)
  /*
   * we need a target for evtWakeup(), which is used to unblock nextEvent() in
   * case we post a event to the localqueue
   */
  mask = CWEventMask;
  attrs.override_redirect = True;
  attrs.event_mask = StructureNotifyMask;

  X->wakeUp = XCreateWindow( X->dsp, X->root, -1000, -1000, 1, 1, 0, CopyFromParent,
							   InputOutput, CopyFromParent, mask, &attrs);

  /*
   * make X connection non-blocking (to get SIGIOs)
   * NOTE: this requires all Xlib calls doing IO via the X conn to be synced! In addition,
   * no Xlib function doing blocked reads on the connection should be called without
   * ensuring that there is input available.
   */
  jthreadedFileDescriptor( ConnectionNumber(X->dsp));
#endif
));

	Component = (*env)->FindClass( env, "java/awt/Component");

	DBG( AWT_EVT, printf("evtInit (%d)\n", Tlk->nWindows));

	return (*env)->NewObjectArray( env, Tlk->nWindows, Component, NULL);
}



// HERE

jobject
Java_java_awt_Toolkit_evtGetNextEvent0( JNIEnv* env, jclass clazz )
{
//	DBG( AWT_EVT, printf("getNextEvent..\n"));

	BMessage *evt = javaApp->NextMessage();
#ifdef USE_POLLING_AWT
	if( evt == 0 ) {
		DBG(AWT_EVT, printf( "null event\n" ));
		return 0 ;
	}
#else
	while( evt == 0 ) {
		evt = javaApp->NextMessage();
	}
#endif
        
	if( evt->what != CAFE ) {
		TOFIX();
		return 0 ;
	}
	
	jobject result = 0 ;
	
	DBG(AWT_EVT, evt->PrintToStream());

	int32 evtId = 0 ;
	JavaWindow *source = 0 ;

	evt->FindInt32( evtCode, &evtId );
	evt->FindPointer( evtSource, (void**)&source );

	BMessage *origmsg = 0 ;
	evt->FindPointer( "payload", (void**)&origmsg );

	if( getSourceIdx( Tlk, source) < 0 ) {
		DBG(AWT_EVT, printf( "source %p not found\n", source ));
		delete origmsg ;
		delete evt ;
		return 0 ;
	}

	if( origmsg ) {
//		origmsg->PrintToStream();
	}

	if( evtId == UPDATE  ) {

		DBG(AWT_EVT, printf( "sendoff %ld %s\n", evtId, eventStr(evtId) ));

		BRect bounds = source->Bounds();

		int x = (int)bounds.left ;
		int y = (int)bounds.top ;
		int w = (int)bounds.right - x ;
		int h = (int)bounds.bottom - y ;
		if( origmsg ) {
//			origmsg->PrintToStream();
		}
		result = (*env)->CallStaticObjectMethod( env, PaintEvent, 
				getPaintEvent, Tlk->srcIdx, evtId, 
				x, y, w, h);
	} else if( MOUSE_FIRST <= evtId && evtId <= MOUSE_LAST ) {

//		DBG(AWT_EVT, printf( "sendoff %ld %s\n", evtId, eventStr(evtId) ));

		BPoint where ;
		int32 buttons = 0 ;

		origmsg->FindPoint( "where", &where );
		origmsg->FindInt32( "buttons", &buttons );

		result = (*env)->CallStaticObjectMethod( env, MouseEvent,
				getMouseEvent, Tlk->srcIdx, evtId, 
				(int)buttons, (int)where.x, (int)where.y );

	} else if( KEY_FIRST <= evtId && evtId <= KEY_LAST ) {

		DBG(AWT_EVT, printf( "sendoff %ld %s\n", evtId, eventStr(evtId) ));

		//int  n ;
		int32 keySim;
		int keyCode = 0 ;
		int keyChar = 0 ;
		int mod = 0 ;
		const char * bytes;

		if (origmsg->FindString("bytes", &bytes) == B_OK)
			keySim = bytes[0];
		else
			keySim = 0;

		if (keySim == B_FUNCTION_KEY) {		/* function keys */
			
			origmsg->FindInt32("key", &keySim);
			if (keySim >= B_F1_KEY && keySim <= B_F12_KEY)
				keyCode = KEY_F1 + keySim - B_F1_KEY;
			/* !!! other "function" keys are not handled */
			keyChar = 0;
		}	
		else {
			keyCode = FKeyCode[ keySim & 0xFF];	/* !!! NOTE TRUNCATION */
			if ( keyCode < 0 ){				/* special keys */
	  			keyChar = keyCode = -keyCode;
			}
			else if ( keyCode == 0){		/* plain keys, no table */				
				keyCode = keyChar = keySim;
			}
			else {  						/* a "pure" special key */
	  			keyChar = 0;
			}
		}	
		
/*	if ( id == KEY_PRESSED ) {
		accelHint = true;
		if ( keyChar == 0 ){
			// update modifiers for function keys
			switch ( keyCode ) {
			case VK_SHIFT:        inputModifier |= SHIFT_MASK; break;
			case VK_CONTROL:      inputModifier |= CTRL_MASK;  break;
			case VK_ALT:          inputModifier |= ALT_MASK;   break;
			case VK_META:         inputModifier |= META_MASK;
			}
		}
*/		int32 natMods = origmsg->FindInt32("modifiers");
		if (natMods & B_SHIFT_KEY) 	 mod |= SHIFT_MASK;
		if (natMods & B_CONTROL_KEY) mod |= CTRL_MASK;
		if (natMods & B_OPTION_KEY)	 mod |= ALT_MASK;
  		// !!! if (natMods & ???) mod |= META_MASK;
		if (mod!=0) DBG(AWT_EVT, printf("modifiers: %d\n", mod));
		
		DBG(AWT_EVT, printf("keyEvent....%d -> %d %d\n", keySim, keyCode, keyChar));
  
		result = (*env)->CallStaticObjectMethod( env, KeyEvent, 
			getKeyEvent, Tlk->srcIdx, evtId, keyCode, keyChar, mod);


	} else if( COMPONENT_FIRST <= evtId && evtId <= COMPONENT_LAST ) {

		DBG(AWT_EVT, printf( "sendoff %ld %s\n", evtId, eventStr(evtId) ));

		BRect bounds = source->Bounds();

		int x = (int)bounds.left ;
		int y = (int)bounds.top ;
		int32 w = (int32)bounds.right - x ;
		int32 h = (int32)bounds.bottom - y ;
//		origmsg->PrintToStream();

		if( evtId == COMPONENT_RESIZED ) {
			origmsg->FindInt32( "width", &w );
			origmsg->FindInt32( "height", &h );
		}

		result = (*env)->CallStaticObjectMethod( env, ComponentEvent, 
				getComponentEvent, Tlk->srcIdx, evtId, x,y,w,h );
	} else  if( FOCUS_FIRST <= evtId && evtId <= FOCUS_LAST ) {

		DBG(AWT_EVT, printf( "sendoff %ld %s\n", evtId, eventStr(evtId) ));

		result = (*env)->CallStaticObjectMethod( env, FocusEvent, getFocusEvent, Tlk->srcIdx, evtId, JNI_FALSE);

	} else  if( WINDOW_FIRST <= evtId && evtId <= WINDOW_LAST ) {

		DBG(AWT_EVT, printf( "sendoff %ld %s\n", evtId, eventStr(evtId) ));

		result = (*env)->CallStaticObjectMethod( env, WindowEvent, 
				getWindowEvent, Tlk->srcIdx, evtId);

	}
	delete origmsg ;
	delete evt ;
	return result ;
}

AWT_EXPORT
jobject
Java_java_awt_Toolkit_evtGetNextEvent ( JNIEnv* env, jclass clazz )
{
	jobject res ;

	DBG( AWT_EVT, printf("evtGetNextEvent..\n"));

#if !defined(USE_POLLING_AWT)
	(*env)->MonitorExit( env, clazz);
#endif
	res = Java_java_awt_Toolkit_evtGetNextEvent0( env, clazz );
#if !defined(USE_POLLING_AWT)
	(*env)->MonitorEnter( env, clazz);
#endif

	return res ;
}

AWT_EXPORT
jobject
Java_java_awt_Toolkit_evtPeekEvent ( JNIEnv* env, jclass clazz )
{
  jobject jEvt = NULL;

	TOFIX();

  DBG( AWT_EVT, printf("peekEvent..\n"));

UNIMPLEMENTED((
  if ( nextEvent( env, clazz, X, False) && ((getSourceIdx( X, X->event.xany.window) >= 0)) ) {
	if ( (jEvt = (processEvent[X->event.xany.type])( env, X)) )
	  X->preFetched = 1;
  }

  DBG( AWT_EVT, printf("..peekEvent: %s %x, %x\n", eventStr(Tlk->evtId), jEvt, Tlk->event.xany.window));
));
  return jEvt;
}


/*
 * We can't do a XPeekIfEvent here because it would block until such an event
 * comes in
 */
AWT_EXPORT
jobject
Java_java_awt_Toolkit_evtPeekEventId ( JNIEnv* env, jclass clazz, jint id )
{
	TOFIX();

UNIMPLEMENTED((
  jobject jEvt;

  if ( (jEvt = Java_java_awt_Toolkit_evtPeekEvent( env, clazz)) && (X->evtId == id) ){
	return jEvt;
  }
));
  return NULL;
}


/*
 * This is just used to wakeup the getNextEvent call if we are multithreaded,
 * and we post an event from outside the dispatcher thread (which might be blocked
 * in a native getNextEvent). This is a tribute to the fact that we actually have
 * two different queues - the native one, and the queue for self-posted events.
 * We could also do a round trip here, but this would wake up the event dispatcher
 * immediately (i.e. before this func returns), which is probably a crude side effect
 * of postEvent().
 */
AWT_EXPORT
void
Java_java_awt_Toolkit_evtWakeup ( JNIEnv* env, jclass clazz )
{
//	DBG( AWT_EVT, printf("evtWakeup\n"));

	javaApp->MsgEvent( 0, 0, 0 );
}

/*
 * This is a helper for (IS_DISPATCH_EXCLUSIVE | NATIVE_DISPATCHER_LOOP) windowing
 * systems, where we need to execute certain requests (e.g. window creation) to
 * the native event thread. Not required here
 */
AWT_EXPORT
void
Java_java_awt_Toolkit_evtSendWMEvent ( JNIEnv* env, jclass clazz, jobject wmEvt )
{
}

AWT_EXPORT
jint
Java_java_awt_Toolkit_evtRegisterSource ( JNIEnv* env, jclass clazz, Window wnd )
{
  /*
   * We have done that already during the various wndCreateXX()
   */
  int i = getSourceIdx( Tlk, wnd);

  DBG( AWT_EVT, printf("registerSource( %p) -> %d\n", wnd, i));

  return i;
}


AWT_EXPORT
jint
Java_java_awt_Toolkit_evtUnregisterSource ( JNIEnv* env, jclass clazz, Window wnd )
{
  int i = getSourceIdx( Tlk, wnd);

  if ( i >= 0 ){
/* !!!	Tlk->windows[i].w = -1;
	Tlk->windows[i].flags = 0;
	Tlk->windows[i].owner = 0;
*/
	Tlk->windows[i] = (JavaWindow *)-1;
  }

  if ( Tlk->lastWindow == wnd )
	Tlk->lastWindow = 0;

  DBG( AWT_EVT, printf("unregisterSource( %p) -> %d\n", wnd, i));

  return i;
}

