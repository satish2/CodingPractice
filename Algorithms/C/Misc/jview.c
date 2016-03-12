/**
 * jview.c 
 *
 *	(c) Copyright 1999 others......
 *	(c) Copyright 1999 Sim IJskes
 *
 * See the file "license.terms" for information on usage and redistribution 
 * of this file. 
 */

#include "japp.h"

#include "toolkit.h"

#include "jview.h"


const char * sourceTag = "*wnd*";


void
jView::Draw(BRect update)
{
	DBG(AWT_EVT, printf( "jView::Draw(" ));
	DBG(AWT_EVT, update.PrintToStream());
	DBG(AWT_EVT, printf( "\n" ));

#if 0
  DBG(AWT_EVT, printf("Draw\n"));

// !!! NOT THE BEST PLACE, 
//     it would be better to intercept events before they are dispatched to the handlers
//     (see event_hook)

  BMessage * msg = new BMessage();

  msg->what = UPDATE_EVENT;					/* custom update event */
  msg->AddPointer(sourceTag, Window()); 
  msg->AddRect("frame", Frame());           /* update the entire frame */
  
  bigtime_t t = system_time();
  msg->AddInt64("when", t);

	update.PrintToStream();

	javaApp->AddMessage( msg );
#endif
} 


void
jView::KeyDown(const char *bytes, int32 numBytes)
{
	DBG(AWT_EVT, printf("jView::KeyDown\n"));
}

void
jView::KeyUp(const char *bytes, int32 numBytes)
{
	DBG(AWT_EVT, printf("jView::KeyUp\n"));
}

void
jView::MouseDown(BPoint point)
{
	DBG(AWT_EVT, printf("jView::MouseDown\n"));
}

void
jView::MouseUp(BPoint point)
{
	DBG(AWT_EVT, printf("jView::MouseUp\n"));
}

void
jView::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
{
	DBG(AWT_EVT, printf("jView::MouseMoved\n"));
}

void
jView::FrameMoved(BPoint parentPoint)
{
	DBG(AWT_EVT, printf("jView::FrameMoved\n"));
	BView::FrameMoved( parentPoint );
}

void
jView::FrameResized(float width, float height)
{
	DBG(AWT_EVT, printf("jView::FrameResized\n"));
	BView::FrameResized( width, height );
}

void
jView::WindowActivated(bool active)
{
	DBG(AWT_EVT, printf("BView::WindowActivated\n"));
}

void
jView::MessageReceived(BMessage * msg)
{
	DBG(AWT_EVT, printf("BView::MessageReceived\n"));
	DBG(AWT_EVT, printf( "jview <<<<\n" ));
	DBG(AWT_EVT, msg->PrintToStream());

	if (msg)
	switch(msg->what)
	{
		default:
			BView::MessageReceived(msg);
	}

	DBG(AWT_EVT, printf( "<<<< jview\n" ));
}


