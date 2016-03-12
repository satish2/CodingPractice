/**
 * tlk.c - 
 *
 * Copyright (c) 1998
 *      Transvirtual Technologies, Inc.  All rights reserved.
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */

#define MAIN

#include <AppKit.h>
#include <Screen.h>
#include <SupportKit.h>

#include "japp.h"

#include "toolkit.h"
#include "tlkprops.h"

const char * app_signature = "application/x-vnd.bekaffe";

/********************************************************************************
 * auxiliary functions
 */

#if TODO
int
xErrorHandler ( Display *dsp, XErrorEvent *err )
{
  char buf[128];
  char key[64];

  /*
   * If there are clueless apps using resident Graphics objects in
   * asnyc drawing ops (without checking for window visibility first),
   * we might get BadDrawable errors. Since this is clearly a bug
   * of the app (which has to clean up resident Graphics objects
   * before closing windows), we don't want to add costly checks
   * on every Graphics op (which couldn't be safe, anyway).
   * The only way to handle this safely would be to link Graphics
   * objects to their targets, and this would add the danger of
   * severe memory leaks in case the Graphics objects aren't disposed
   * (for efficiency reasons, we cach Graphics instances).
   * Ignoring BadDrawables is not very nice, but reasonably safe.
   */
  /*
  if ( err->error_code == BadDrawable )
	return 0;
  */

UNIMPLEMENTED((
  sprintf( key, "%d", err->error_code);
  XGetErrorDatabaseText( dsp, "XProtoError", key, "", buf, sizeof( buf));

  DBG( AWT, printf("X error:      %s\n", buf));

  sprintf( key, "%d", err->request_code);
  XGetErrorDatabaseText( dsp, "XRequest", key, "", buf, sizeof( buf));

  DBG( AWT, printf("  request:    %s\n", buf));
  DBG( AWT, printf("  resource:   %X\n", err->resourceid));

  //DBG( AWT, (*JniEnv)->ThrowNew( JniEnv, AWTError, "X error occured"));
));
  return 0;
}
#endif /* TODO */

/********************************************************************************
 * exported functions
 */


AWT_EXPORT
jint 
Java_java_awt_Toolkit_tlkProperties ( JNIEnv* env, jclass clazz )
{
	jint props = TLK_EXTERNAL_DECO;

#if !defined(USE_POLLING_AWT)
  
  props |= TLK_IS_BLOCKING;
/* !!!  props |= TLK_NEEDS_FLUSH; */
#else
  DBG(AWT_EVT, printf("using POLLING AWT\n")); 
#endif

	return props;
}

int32 poll_thread( void *data )
{
	DBG(AWT_EVT, printf("poll_thread start\n"));
	
	new JavaApplication( app_signature );
	javaApp->Run();

	DBG(AWT_EVT, printf("poll_thread exit\n"));
	return 0 ;
}

AWT_EXPORT
jboolean
Java_java_awt_Toolkit_tlkInit ( JNIEnv* env, jclass clazz, jstring name )
{
	JniEnv = env;
	AWTError = (*env)->FindClass( env, "java/awt/AWTError");

	Tlk->nWindows = 47;
	Tlk->windows = (Window *) AWT_CALLOC( Tlk->nWindows, sizeof(Window));
	// !!! MORE THAN REQUESTED ?
	for(unsigned int i=0;i<Tlk->nWindows;i++) {
		Tlk->windows[i]= (Window)(void*)-1;
	}

	thread_id poller ;
	poller = spawn_thread( poll_thread, "pollthread", B_NORMAL_PRIORITY, 0 );
	resume_thread( poller ); 

	snooze( 1000000 );	// aha! race-condition

	DBG(AWT, printf("tlkInit\n"));
	return JNI_TRUE;
}

AWT_EXPORT
void
Java_java_awt_Toolkit_tlkTerminate ( JNIEnv* env, jclass clazz )
{
	DBG(AWT, printf("tlkTerminate\n"));
  
  // unlink from the app_server
  if (be_app->Lock())
  {
   	  be_app->Quit();  
  }
  //delete be_app;  // we need this if we are running the app event loop
  
  /* !!!
     we still don't have a main application event loop,
     this is our way of being a killer app */
/* DBG(AWT, ("!!! kill team\n"));
  kill_team(0);     
*/
}


AWT_EXPORT
jstring
Java_java_awt_Toolkit_tlkVersion ( JNIEnv* env, jclass clazz )
{
	return (*env)->NewStringUTF( env, "BeOS-1.0");
}

AWT_EXPORT
jint
Java_java_awt_Toolkit_tlkGetResolution ( JNIEnv* env, jclass clazz )
{
UNIMPLEMENTED((
  /*
   * This is just a guess since WidthMMOfScreen most probably isn't exact.
   * We are interested in pixels per inch
   */
  Screen *scr = DefaultScreenOfDisplay( X->dsp);
  return ((WidthOfScreen( scr) * 254) + 5) / (WidthMMOfScreen( scr) *10);
));
	TOFIX();
	return 72; // !!!
}

AWT_EXPORT
jint
Java_java_awt_Toolkit_tlkGetScreenHeight ( JNIEnv* env, jclass clazz )
{
	return jint( BScreen().Frame().bottom );
}

AWT_EXPORT
jint
Java_java_awt_Toolkit_tlkGetScreenWidth ( JNIEnv* env, jclass clazz )
{
	return jint( BScreen().Frame().right );
}

AWT_EXPORT
void
Java_java_awt_Toolkit_tlkSync ( JNIEnv* env, jclass clazz )
{
  /*
   * this one flushes the request buffer and waits until all reqs have been processed
   * (a roundtrip for input based on prior requests)
   */
	DBG(AWT, printf("tlkSync\n"));
	TOFIX();
}

AWT_EXPORT
void
Java_java_awt_Toolkit_tlkFlush ( JNIEnv* env, jclass clazz )
{
  /* simply flush request buffer (mainly for background threads and blocked AWT) */

	DBG(AWT, printf("tlkFlush\n"));
	TOFIX();
}


AWT_EXPORT
void
Java_java_awt_Toolkit_tlkBeep ( JNIEnv* env, jclass clazz )
{
	beep();
}

AWT_EXPORT
void
Java_java_awt_Toolkit_tlkDisplayBanner ( JNIEnv* env, jclass clazz, jstring banner )
{
	if( !banner ) {
		// does this ever happen?
		return ;
	}

	char *buf = java2CString( env, Tlk, banner );
	DBG(AWT, printf( "display banner: %s\n", buf ));
}

