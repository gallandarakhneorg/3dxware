/*|--------------------------------------------------------------------------

 MAGELLAN X-Window  example application               Version 4.00 15.10.97

 Copyright (C) 1984, 2002 3Dconnexion GmbH / Inc.
 An der Hartmuehle 8
 D - 82229 Seefeld

 mailto:development@3dconnexion.com

----------------------------------------------------------------------------|*/
#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#include <xdrvlib.h>


double MagellanSensitivity = 1.0;

int main(int argc, char** argv )
{
Display *display;
Window root, window;

int screennumber,width,height;
XSizeHints *sizehints;
XWMHints *wmhints;
XClassHint *classhints;

char *WinName = (char*)"Magellan 3D Controller";
XTextProperty WindowName;
GC wingc;
XGCValues xgcvalues;

XEvent report;
MagellanFloatEvent MagellanEvent;

XComposeStatus compose;
KeySym keysym;

int MagellanDemoEnd = FALSE;
char MagellanBuffer[ 256 ];


/****************** Open a Window ******************************************/
 sizehints  = XAllocSizeHints();
 wmhints    = XAllocWMHints();
 classhints = XAllocClassHint();
 if ( (sizehints==NULL) || (wmhints==NULL) || (classhints==NULL) )
  {
   fprintf( stderr, "Can't allocate memory! Exit ... \n" );
   exit( -1 );
  };

 display = XOpenDisplay( NULL );
 if ( display == NULL )
  {
   fprintf( stderr, "Can't open display! Exit ... \n");
   exit( -1 );
  };

 screennumber = DefaultScreen(display);
 width  = DisplayWidth(display,screennumber);
 height = DisplayHeight(display,screennumber);
 root   = DefaultRootWindow(display);
 window = XCreateSimpleWindow( display, root, 0,0, width/5*3,height/8, 20,
			       BlackPixel(display,screennumber),
			       WhitePixel(display,screennumber) );

 printf("Magellan: xapp.c\n" );
 printf("Magellan Root Window=%08X \nMagellan Application Window=%08X \n\n",
 	 (unsigned int)root, (unsigned int)window );

 XStringListToTextProperty( &WinName, 1, &WindowName );

 wmhints->initial_state = NormalState;
 wmhints->input = TRUE;
 wmhints->flags = StateHint | InputHint;

 classhints->res_name = (char*)"Magellan 3D Controller";
 classhints->res_class = (char*)"BasicWindow";
 XSetWMProperties( display, window, &WindowName, NULL, argv,
		   argc, sizehints, wmhints, classhints );

 XMapWindow( display, window ); 
 xgcvalues.foreground = BlackPixel( display, 0 );
 xgcvalues.background = WhitePixel( display, 0 );
 wingc = XCreateGC( display, window, GCForeground | GCBackground, &xgcvalues );

 /************************* Create 3D Event Types ***************************/
 if ( !MagellanInit( display, window ) )
  {
   fprintf( stderr, "No driver is running. Exit ... \n" );
   exit(-1);
  };

 /************************* Main Loop ***************************************/
 XSelectInput( display, window, KeyPressMask | KeyReleaseMask );

 while( MagellanDemoEnd == FALSE )
  {
   XNextEvent( display, &report );
   switch( report.type )
    {
     case KeyRelease : /* ... */
                       break;
 
     case KeyPress :
      XLookupString( (XKeyEvent*)&report, MagellanBuffer,
     		     sizeof(MagellanBuffer), &keysym, &compose );
      MagellanDemoEnd = keysym == XK_Escape;
      break;
			
     case ClientMessage :
      switch( MagellanTranslateEvent( display, &report, &MagellanEvent, 1.0, 1.0 ) )
       {
        case MagellanInputMotionEvent :
         MagellanRemoveMotionEvents( display );
         sprintf( MagellanBuffer, 
            "x=%+5.0f y=%+5.0f z=%+5.0f a=%+5.0f b=%+5.0f c=%+5.0f   ",
		  (float)MagellanEvent.MagellanData[ MagellanX ],
		  (float)MagellanEvent.MagellanData[ MagellanY ],
		  (float)MagellanEvent.MagellanData[ MagellanZ ],
		  (float)MagellanEvent.MagellanData[ MagellanA ],
		  (float)MagellanEvent.MagellanData[ MagellanB ],
		  (float)MagellanEvent.MagellanData[ MagellanC ] );

         XClearWindow( display, window );
	 XDrawString( display, window, wingc, 10,40,
	  	       MagellanBuffer, (int)strlen(MagellanBuffer) );
         XFlush( display );
	 break;
	 
        case MagellanInputButtonPressEvent :
         sprintf( MagellanBuffer, "Button pressed [%c]  ",
		   MagellanEvent.MagellanButton ==  9 ? '*' :
		   MagellanEvent.MagellanButton == 10 ? '+' :
		   MagellanEvent.MagellanButton == 11 ? '-' :
		             '0'+MagellanEvent.MagellanButton );
         XClearWindow( display, window );
         XDrawString( display, window, wingc, 10,40,
                       MagellanBuffer, (int)strlen(MagellanBuffer) );
         XFlush( display );

	 switch ( MagellanEvent.MagellanButton )
	  {
	   case 5: MagellanApplicationSensitivity( display, MagellanSensitivity / 2.0 ); break;
	   case 6: MagellanApplicationSensitivity( display, MagellanSensitivity * 2.0 ); break;
	   case 7: MagellanApplicationSensitivity( display, 1.0 ); break;
	  };

	 switch( MagellanEvent.MagellanButton )
	  {
 	   case 5: MagellanSensitivity = MagellanSensitivity <= 1.0/32.0 ? 1.0/32.0 : MagellanSensitivity/2.0; break;
 	   case 6: MagellanSensitivity = MagellanSensitivity >= 32.0 ? 32.0 : MagellanSensitivity*2.0; break;
	   case 7: MagellanSensitivity = 1.0;  break;
	  };

	 switch( MagellanEvent.MagellanButton )
	  {
	   case 5:
	   case 6:
	   case 7:
	   printf("Application Sensitivity = %f \n", (float)MagellanSensitivity );
	   break;
	  };
	 break;
	  
        case MagellanInputButtonReleaseEvent :
         sprintf( MagellanBuffer, "Button released [%c] ",
		   MagellanEvent.MagellanButton == 9  ? '*' :
		   MagellanEvent.MagellanButton == 10 ? '+' :
		   MagellanEvent.MagellanButton == 11 ? '-' :
		             '0'+MagellanEvent.MagellanButton ); 
         XClearWindow( display, window );
         XDrawString( display, window, wingc, 10,40,
                       MagellanBuffer, (int)strlen(MagellanBuffer) );
         XFlush( display );
         break;
	
       default : /* another ClientMessage event */
 	 break;
       };
      break;
     };
  };

 MagellanClose( display );
 XFree( sizehints );
 XFree( wmhints );
 XFree( classhints );
 XFreeGC( display, wingc );
 XDestroyWindow( display, window );
 XCloseDisplay( display );
 return TRUE;
}
