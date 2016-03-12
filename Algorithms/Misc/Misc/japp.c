/**
 * japp.c
 *
 *	(c) Copyright 1999 Sim IJskes
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */


#include "japp.h"

#include "toolkit.h"

#include "jwindow.h"

#undef DEBUG

JavaApplication *javaApp = 0 ;  

JavaApplication::JavaApplication( const char *s ) : 
	BApplication( s ) 
{
	DBG(AWT_EVT, printf( "application created\n" ));
	
	if( javaApp != 0 ) {
		printf( "app already running!" );
		// TODO abort
	}

	queue_sem = create_sem(0,"queue_sem");
	// TODO watch error

	queue = new BMessageQueue();

	javaApp = this ;
}

JavaApplication::~JavaApplication()
{
	delete queue ;

	// TODO guard for  error
	delete_sem( queue_sem );
}

void JavaApplication::ReadyToRun(void)
{
	
}

void JavaApplication::DispatchMessage(BMessage *message, BHandler *target)
{
	DBG(AWT_EVT, printf( "application >>>>\n" ));

	DBG(AWT_EVT, message->PrintToStream());

	BApplication::DispatchMessage( message, target );
	DBG(AWT_EVT, printf( "<<<< application \n" ));
}

/**
	a blocking call for the next event 
*/

BMessage *JavaApplication::NextMessage()
{
	BMessage *r ;

#ifdef DEBUG
	printf("NextMessage called (%ld)\n", queue->CountMessages() );
#endif

#if !defined(USE_POLLING_AWT)
	WaitQueueRead();
#else
	// still something wrong with the event flow.

//	status_t s = acquire_sem_etc( queue_sem, 1, B_TIMEOUT, 10 * 1000000 );
	status_t s = acquire_sem_etc( queue_sem, 1, B_TIMEOUT, 0 );
	if( s == B_TIMED_OUT || s == B_WOULD_BLOCK ) {
//		debugger( "it's a timeout" );
//		printf( "timeout\n" );
		return 0 ;
	}

	if( s != B_NO_ERROR ) {
		printf( "err from acquire %ld\n", s );
	}
#endif

	if( !queue->Lock() ) {
		printf( "NextMessage locking error\n" );
		return 0 ;
	}
	
	r = queue->NextMessage();

	queue->Unlock();

#ifdef DEBUG
	printf( "NextMessage returns\n" );
#endif

	return r ;
}

void JavaApplication::WaitQueueRead()
{
	status_t s = acquire_sem( queue_sem );	// decrement semaphore
	if( s != B_NO_ERROR ) {
		printf( "err from acquire %ld\n", s );
	}
}

void JavaApplication::NotifyQueueRead()
{
	release_sem( queue_sem );	// increment semaphore
}

// be sure to lock queue before entering
BMessage *JavaApplication::FindEvent( JavaWindow *win, int evtId, int32 &idx )  
{
	while(1) {
		BMessage *msg = queue->FindMessage( CAFE, idx );
		
		if( msg == 0 ) {
			return 0 ;
		}

		idx++ ;

		int32 eid = -1 ;
		JavaWindow *esrc = (JavaWindow*)-1 ;

		msg->FindInt32( evtCode, &eid );
		msg->FindPointer( evtSource, (void**)&esrc );

		if( evtId == eid && win == esrc ) {
			return msg ;
		}
	}
}

void JavaApplication::MsgEvent( JavaWindow *win, int evtId, BMessage *m )  
{
	if( !queue->Lock() ) {
		printf( "MsgEvent locking error\n" );
		return ;
	}

	BMessage *mcopy = 0 ;

	if( m ) {
		mcopy = new BMessage( *m );
	}

	BMessage *msg = new BMessage( CAFE );

	msg->AddInt32( evtCode, evtId );
	msg->AddPointer( evtSource, win );
	msg->AddPointer( "payload", mcopy );

	int32 cnt = queue->CountMessages();

#ifdef DEBUG
	printf( "AddMessage called (%ld)\n", cnt );
#endif

#ifdef COMPRESS_EVENTS
	if( cnt > 0 ) {
		if( evtId == COMPONENT_RESIZED || 
				evtId == UPDATE || 
				evtId == MOUSE_MOVE ) {

			int32 idx = 0 ;
			BMessage *msg = FindEvent( win, evtId, idx );
			while( msg ) {
				queue->RemoveMessage( msg );
				BMessage *origmsg = 0 ;
				msg->FindPointer( "payload", (void**)&origmsg );
				delete origmsg ;
				delete msg ;
				// should do WaitQueueRead() here. 
				msg = FindEvent( win, evtId, idx );
			}
		}
	}
#endif

	queue->AddMessage( msg );
	NotifyQueueRead();

#ifdef COMPRESS_EVENTS
	if( evtId == COMPONENT_RESIZED ) {
		BMessage *msg = new BMessage( CAFE );

		msg->AddInt32( evtCode, UPDATE );
		msg->AddPointer( evtSource, win );
		queue->AddMessage( msg );
		NotifyQueueRead();
	}
#endif

	queue->Unlock();

}

/** SGY
a tiny very tiny small todo thingy in mouse move compression:

what about the sequence:
	MOUSE_DOWN
	MOUSE_MOVE
	MOUSE_MOVE
	MOUSE_UP
	
	MOUSE_MOVE
	MOUSE_MOVE

	MOUSE_DOWN
	MOUSE_MOVE
	MOUSE_MOVE
	MOUSE_UP

when this is put in the event queue in one go, how will the compression of
the MOUSE_MOVE's affect the application.....

maybe traverse the queue in reverse order, from young to old, and stop before 
a state change in mouse handling.

*/

/** SGY
sometimes the window manager (eh, application_server) ends a user resize action
with a last resize event, so without another update event

	RESIZE
	UPDATE
	RESIZE
	silence....

Both the last and the one before have the same width and height parms.

i guess, and haven't checked yet, that a BView will compensate 
for this behaviour 

*/
