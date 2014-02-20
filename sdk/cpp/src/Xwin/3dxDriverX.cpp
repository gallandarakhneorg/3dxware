/*
 * Copyright (c) 2008-2009,2014 Stéphane GALLAND <galland@arakhne.org>
 *
 * This file is part of ASMD.
 *
 * ASMD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ASMD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with ASMD.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <3dxware/debug.h>
#include <3dxware/Xwin/3dxDriverX.h>
#include <3dxware/3dxException.h>
#include <3dxware/3dxCmdLine.h>

#define XHigh32(__v__)        (((__v__)>>16)&0x0000FFFF)
#define XLow32(__v__)         ((__v__)&0x0000FFFF)

#define _QUOTEME(x)		#x
#define QUOTEME(x)		_QUOTEME(x)

#ifndef RUN_DIRECTORY
#  define RUN_DIRECTORY		/var/run/3dxware
#endif

#ifndef BIN_DIRECTORY
#  define BIN_DIRECTORY		/usr/bin
#endif

#define DRIVER_PID_FILE		QUOTEME(RUN_DIRECTORY) "/3dxsrv.pid"
#define MANAGER_EXEC		QUOTEME(BIN_DIRECTORY) "/3dxmanager"
#define MANAGER_CMD_START	MANAGER_EXEC " --nowait start"
#define MANAGER_CMD_STOP	MANAGER_EXEC " --nowait stop"

#define MAGELLAN_INIT_TRIES	5

#ifdef __cplusplus
extern "C" {
#endif

namespace dxware {

static char* WINNAME = (char*)("Magellan 3D Controller");

typedef union {
	float floatField;
	short shortField[2];
} MagellanTypeConversion;

const char* XWindowDriver::getOSName() const
{
	return "Unix/Xlib";
}

XWindowDriver::XWindowDriver(): display(0), window(0), sizehints(0), wmhints(0), classhints(0), display2(0), window2(0), is3DxWareDriverInternallyLaunched(false)
{
}

void XWindowDriver::ensureLaunched()
{
	if (!isLaunched()) {
		if (ensure3DxWareDriver()) {
			is3DxWareDriverInternallyLaunched = true;
		}
		dbg2("launch driver %s, %s", getAPIVersion(), getOSName());
		bool noWindow = (window==0);
		if (noWindow) {
			window = createXWindowContext();
		}
		else {
			dbg("use user-defined window");
		}
		initMagellan(window, is3DxWareDriverInternallyLaunched);
		if (noWindow) initXInput();
		setLaunched();
	}
}

Window XWindowDriver::createXWindowContext()
{
	Window window;
	Window root;
	int screenNumber/*, width, height*/;
	XTextProperty windowName;

	// Open a Window
	sizehints  = XAllocSizeHints();
	wmhints    = XAllocWMHints();
	classhints = XAllocClassHint();
	if ((sizehints==NULL)||(wmhints==NULL)||(classhints==NULL)) {
		throw DeviceException("Can't allocate X-Window memory",__FILE__,__LINE__);
	}

	display = XOpenDisplay(NULL);
	if (display==NULL) {
		throw DeviceException("Can't open display",__FILE__,__LINE__);
	}

	screenNumber = DefaultScreen(display);
	/*width  = DisplayWidth(display,screenNumber);*/
	/*height = DisplayHeight(display,screenNumber);*/
	root   = DefaultRootWindow(display);
	window = XCreateSimpleWindow( display, root,
			0,0, /*position*/
			1, /*width*/
			1, /*height*/
			0, /*border*/
			BlackPixel(display,screenNumber),
			WhitePixel(display,screenNumber) );

	XStringListToTextProperty( &WINNAME, 1, &windowName );

	wmhints->initial_state = IconicState;
	wmhints->input = true;
	wmhints->flags = StateHint | InputHint;

	classhints->res_name = (char*)("Magellan 3D Controller");
	classhints->res_class = (char*)("BasicWindow");

	dbg1("Command line option count=%d", getCommandLineOptionCount());
	dbg1("Command line options=0x%lX",(unsigned long)getCommandLineOptions());
	dbg1("First command line option=%s",getCommandLineOptions()[0]);

	XSetWMProperties(
		display, window, &windowName, NULL,
		getCommandLineOptions(),
		getCommandLineOptionCount(),
		sizehints, wmhints, classhints );

	// Make the window visible
	XMapWindow( display, window ); 

	return window;
}

void XWindowDriver::initMagellan(Window initWindow, bool waitForInit)
{
	// Define the Magellan Event types
	magellanMotionEvent       = XInternAtom( display, "MotionEvent", true );
	if (magellanMotionEvent==0)
		throw DeviceException("cannot create X-Window event type MotionEvent",__FILE__,__LINE__);

	magellanButtonPressEvent  = XInternAtom( display, "ButtonPressEvent", true );
	if (magellanButtonPressEvent==0)
		throw DeviceException("cannot create X-Window event type ButtonPressEvent",__FILE__,__LINE__);

	magellanButtonReleaseEvent= XInternAtom( display, "ButtonReleaseEvent",true);
	if (magellanButtonReleaseEvent==0)
		throw DeviceException("cannot create X-Window event type ButtonReleaseEvent",__FILE__,__LINE__);

	magellanCommandEvent      = XInternAtom( display, "CommandEvent", true );
	if (magellanCommandEvent==0)
		throw DeviceException("cannot create X-Window event type CommandEvent",__FILE__,__LINE__);

	dbg("Connecting to the Magellan driver window");
	bool isInit = setMagellanWindow(display, initWindow);
	unsigned short tries = 1;

	while (!isInit && waitForInit && tries<MAGELLAN_INIT_TRIES) {
		dbg("\tconnection failed, waiting for the Magellan driver window");
		sleep(1);
		tries++;
		dbg2("\ttry %u/%u",tries,MAGELLAN_INIT_TRIES);
		isInit = setMagellanWindow(display, initWindow);
	}

	if (!isInit) {
		throw DeviceException("cannot initialize X-Window window for Magellan device",__FILE__,__LINE__);
	}
}

bool XWindowDriver::setMagellanWindow(Display* display, Window initWindow)
{
	return sendMagellanCommand(display, 
			MAGELLAN_COMMAND_APPLICATION_WINDOW,
			(short) XHigh32( initWindow ),
			(short) XLow32( initWindow ));
}

void XWindowDriver::initXInput()
{
	XSelectInput( display, window, KeyPressMask | KeyReleaseMask );
}

XWindowDriver::~XWindowDriver()
{
	closeMagellan();
	if (display2!=0) display = 0;
	if (window2!=0) window = 0;
	if (sizehints!=0) XFree(sizehints);
	if (wmhints!=0) XFree(wmhints);
	if (classhints!=0) XFree(classhints);
	if (window!=0) XDestroyWindow(display, window);
	if (display!=0) XCloseDisplay(display);
	if (is3DxWareDriverInternallyLaunched) {
		stop3DxWareDriver();
	}
}

void XWindowDriver::closeMagellan()
{
	if (display!=0) {
		initMagellan((Window)InputFocus, false);
	}
}

int XWindowDriver::magellanErrorHandler(Display* display, XErrorEvent* event)
{
	char buffer[128];
	switch(event->error_code) {
	case BadWindow:
		break;
	default:
		XGetErrorText(display, event->error_code, buffer, 128*sizeof(char));
		fprintf(stderr, "Magellan: Error = %s.\n", buffer);
		break;
	}
	return 0;
}

const DeviceEvent* XWindowDriver::nextEvent()
{
	XEvent report;
	bool validEvent;

	ensureLaunched();

	do {
		if (!isBlocking()) {
			if (XPending(display)<=0) {
				return NULL;
			}
		}

		dbg("waiting for new Xlib event");
		XNextEvent(display, &report);
		dbg("new Xlib event arrived");

		validEvent = treatEvent(&report, &publicEvent, true);

		// Force the Magellan window to have the focus because
		// it is required to obtain the next X event.
		if (isBlocking())
			XSetInputFocus(display, window, RevertToParent, CurrentTime);

	}
	while (!validEvent);

	return &publicEvent;
}

bool XWindowDriver::treatEvent(XEvent* xEvent, DeviceEvent* driverEvent, bool consumeEvents)
{
	bool validEvent = true;
	KeySym keysym;

	switch(xEvent->type) {

	case KeyRelease:
		keysym = XLookupKeysym((XKeyEvent*)xEvent, 0);
		validEvent = treatKeyReleasedEvent(keysym, driverEvent);
		break;

	case KeyPress :
		keysym = XLookupKeysym((XKeyEvent*)xEvent, 0);
		validEvent = treatKeyPressedEvent(keysym, driverEvent);
		break;

	case ClientMessage :
		validEvent = treatMotionEvent(xEvent, driverEvent, consumeEvents);
		break;
	} // switch(xEvent->type)

	return validEvent;
}

bool XWindowDriver::treatMotionEvent(XEvent* xEvent, DeviceEvent* driverEvent, bool consumeEvents)
{
	bool validEvent = false;
	MagellanFloatEvent magellanEvent;

	switch(magellanTranslateEvent(xEvent, &magellanEvent, 1.0, 1.0)) {
	case MAGELLAN_INPUT_MOTION_EVENT:
	 	if (consumeEvents) magellanRemoveMotionEvents();
		driverEvent->setCoordinates(
		  magellanEvent.magellanData[ COORD_X ],
		  magellanEvent.magellanData[ COORD_Y ],
		  magellanEvent.magellanData[ COORD_Z ],
		  magellanEvent.magellanData[ COORD_A ],
		  magellanEvent.magellanData[ COORD_B ],
		  magellanEvent.magellanData[ COORD_C ]);
		driverEvent->setPeriod(magellanEvent.magellanPeriod);
		driverEvent->setType(MOUSE3D_MOTION);
		validEvent = true;
		break;
	 
	case MAGELLAN_INPUT_BUTTON_PRESS_EVENT:
		driverEvent->setButton(magellanEvent.magellanButton);
		driverEvent->setType(BUTTON3D_PRESSED);
		validEvent = true;
		break;
	  
	case MAGELLAN_INPUT_BUTTON_RELEASE_EVENT:
		driverEvent->setButton(magellanEvent.magellanButton);
		driverEvent->setType(BUTTON3D_RELEASED);
		validEvent = true;
		break;

	default:
		break;
	}

	return validEvent;
}

bool XWindowDriver::treatKeyPressedEvent(KeySym keysym, DeviceEvent* driverEvent)
{
	bool validEvent = true;

	driverEvent->setType(NO_EVENT3D);

	if (isKeyEventAllowed()) {
		keyManager += keysym;
		if (!keyManager.hasNewKey() || keyManager.isVoid()) {
			validEvent = false;
		}
		else {
			driverEvent->setKey(keyManager,keyManager);
			driverEvent->setType(KEY_PRESSED);
		}
	}
	else {
		validEvent = false;
	}

	return validEvent;
}

bool XWindowDriver::treatKeyReleasedEvent(KeySym keysym, DeviceEvent* driverEvent)
{
	bool validEvent = true;

	driverEvent->setType(NO_EVENT3D);

	if (isKeyEventAllowed()) {
		keyManager += keysym;
		if (!keyManager.hasNewKey() || keyManager.isVoid()) {
			validEvent = false;
		}
		else {
			driverEvent->setKey(keyManager,keyManager);
			driverEvent->setType(KEY_RELEASED);
		}
	}
	else {
		validEvent = false;
	}

	return validEvent;
}

MagellanEventType XWindowDriver::magellanTranslateEvent(XEvent* event,
							MagellanFloatEvent* magellanEvent,
							double magellanTranslationScale,
							double magellanRotationScale) {
	if (event->type==ClientMessage) {
		if (event->xclient.message_type==magellanMotionEvent) {
			magellanEvent->magellanType = MAGELLAN_INPUT_MOTION_EVENT;
			magellanEvent->magellanData[ COORD_X ] = event->xclient.data.s[2] * magellanTranslationScale;
			magellanEvent->magellanData[ COORD_Y ] = event->xclient.data.s[3] * magellanTranslationScale;
			magellanEvent->magellanData[ COORD_Z ] = event->xclient.data.s[4] * magellanTranslationScale;
			magellanEvent->magellanData[ COORD_A ] = event->xclient.data.s[5] * magellanRotationScale;
			magellanEvent->magellanData[ COORD_B ] = event->xclient.data.s[6] * magellanRotationScale;
			magellanEvent->magellanData[ COORD_C ] = event->xclient.data.s[7] * magellanRotationScale;
			magellanEvent->magellanPeriod = event->xclient.data.s[8];
			return MAGELLAN_INPUT_MOTION_EVENT;
		}
		else if (event->xclient.message_type==magellanButtonPressEvent) {
			magellanEvent->magellanType = magellanButtonPressEvent;
			magellanEvent->magellanButton = event->xclient.data.s[2];
			return MAGELLAN_INPUT_BUTTON_PRESS_EVENT;
		}
		else if (event->xclient.message_type==magellanButtonReleaseEvent) {
			magellanEvent->magellanType = magellanButtonReleaseEvent;
			magellanEvent->magellanButton = event->xclient.data.s[2];
			return MAGELLAN_INPUT_BUTTON_RELEASE_EVENT;
		}
	}
	return MAGELLAN_NO_EVENT;
}

bool XWindowDriver::magellanRemoveMotionEvents()
{
	XEvent event;

	while (XCheckIfEvent(display,&event,magellanCheckMotionEvent,(char*)magellanMotionEvent) == True ) {
	}

	return true;
}

Bool XWindowDriver::magellanCheckMotionEvent(Display* display, XEvent* event, char* arg)
{
	return ((event->type==ClientMessage)&&(event->xclient.message_type==(Atom)arg));
}

unsigned short XWindowDriver::getDriverResourceCount() const
{
	return 5;
}

const void* XWindowDriver::getDriverResourceAt(unsigned short index) const
{
	switch(index) {
	case XDRIVER_RESOURCE_WINDOW:
		return (window==0) ? &window2 : &window;
	case XDRIVER_RESOURCE_DISPLAY:
		return (display==0) ? display2 : display;
	case XDRIVER_RESOURCE_SIZEHINTS:
		return sizehints;
	case XDRIVER_RESOURCE_WMHINTS:
		return wmhints;
	case XDRIVER_RESOURCE_CLASSHINTS:
		return classhints;
	default:
		return NULL;
	}
}

bool XWindowDriver::setDriverResourceAt(unsigned short index, void* resource)
{
	switch(index) {
	case XDRIVER_RESOURCE_WINDOW:
		if ((resource!=NULL)&&(window==0)) {
			window2 = *(Window*)resource;
			window = window2;
			return true;
		}
		break;
	case XDRIVER_RESOURCE_DISPLAY:
		if ((resource!=NULL)&&(display==0)) {
			display2 = (Display*)resource;
			display = display2;
			return true;
		}
		break;
	}
	return false;
}

bool XWindowDriver::is3DxWareLaunched()
{
	struct stat buf;
	if (stat(DRIVER_PID_FILE, &buf)==0) {
		return S_ISREG(buf.st_mode);
	}
	return false;
}

bool XWindowDriver::is3DxWareLaunchable()
{
	struct stat buf;
	if (stat(QUOTEME(RUN_DIRECTORY), &buf)==0) {
		return S_ISDIR(buf.st_mode);
	}
	return false;
}

bool XWindowDriver::ensure3DxWareDriver()
{
	if (!is3DxWareLaunched() && is3DxWareLaunchable()) {
		return start3DxWareDriver();
	}
	return false;
}

bool XWindowDriver::start3DxWareDriver()
{
	dbg1("launch 3DxWare user-space driver with %s", MANAGER_EXEC);
	if (system(MANAGER_CMD_START)==0) {
		dbg("\twaiting for the daemon launching");
		while (is3DxWareLaunchable() && !is3DxWareLaunched()) {
			//
		}
		return true;
	}
	return false;
}

bool XWindowDriver::stop3DxWareDriver()
{
	dbg1("stop 3DxWare user-space driver with %s", MANAGER_EXEC);
	return (system(MANAGER_CMD_STOP)==0);
}

bool XWindowDriver::bindToRemote3DxWare()
{
	dbg("ensure binding to remote 3DxWare driver");
	try {
		ensureLaunched();
		return true;
	}
	catch(...) {
		return false;
	}
}

bool XWindowDriver::setSensitivity(float sensitivity)
{
	MagellanTypeConversion magellanType;
	magellanType.floatField = sensitivity;
	return sendMagellanCommand(display,
			MAGELLAN_COMMAND_SENSITIVITY,
			magellanType.shortField[0],
			magellanType.shortField[1]);
}

bool XWindowDriver::sendMagellanCommand(Display* display, MagellanCommandType commandType, short v1, short v2)
{
	XTextProperty magellanWindowName;
	XEvent commandMessage;
	Atom actualType;
	int actualFormat;
	unsigned long nItems, bytesReturn;
	unsigned char* propReturn;
	Window root;
	int (*applicationErrorHandler)(Display*,XErrorEvent*);
	bool result;

	result = false;
	applicationErrorHandler = XSetErrorHandler( magellanErrorHandler );

	// Read the window of the Magellan Driver
	root = RootWindow(display, DefaultScreen(display));

	propReturn = NULL;
	XGetWindowProperty( display, root, magellanCommandEvent, 0, 1, false,
		     AnyPropertyType, &actualType, &actualFormat, &nItems,
		     &bytesReturn, &propReturn );

	magellanWindow = InputFocus;
	if (propReturn!=NULL) {
		magellanWindow = *(Window*)propReturn;
		XFree(propReturn);

		if (XGetWMName( display, magellanWindow, &magellanWindowName ) != 0 ) {
			if ( strcmp( (char *) "Magellan Window", (char *) magellanWindowName.value) == 0 ) {
				// Send the application window to the Magellan X Window Driver
				commandMessage.type = ClientMessage;
				commandMessage.xclient.format = 16;
				commandMessage.xclient.send_event = false;
				commandMessage.xclient.display = display;
				commandMessage.xclient.window = magellanWindow;
				commandMessage.xclient.message_type = magellanCommandEvent;

				commandMessage.xclient.data.s[0] = v1;
				commandMessage.xclient.data.s[1] = v2;
				commandMessage.xclient.data.s[2] = commandType;

				result = XSendEvent( display, magellanWindow, false, 0x0000, &commandMessage ) != 0;

				XFlush( display );
			};
		}
	}

	XSetErrorHandler(applicationErrorHandler);

	return result;
}

} /* namespace dxware */

#ifdef __cplusplus
}
#endif

