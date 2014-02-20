/*
 * Copyright (c) 2008-2013 Stéphane GALLAND <galland@arakhne.org>
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
#ifndef __3DX_DRIVER_X_H__
#  define __3DX_DRIVER_X_H__

#  include <X11/Xlib.h>
#  include <X11/Xutil.h>
#  include <X11/Xos.h>
#  include <X11/Xatom.h>
#  include <X11/keysym.h>

#  include <3dxware/3dxDriver.h>

#  ifdef DXWARE_DRIVER
#    error a driver was already included.
#  else
#    define DXWARE_DRIVER dxware::XWindowDriver
#  endif

/** Index of the Xlib Window resource
 */
#  define XDRIVER_RESOURCE_WINDOW 0

/** Index of the Xlib Display resource
 */
#  define XDRIVER_RESOURCE_DISPLAY 1

/** Index of the Xlib XSizeHints resource
 */
#  define XDRIVER_RESOURCE_SIZEHINTS 2

/** Index of the Xlib XWMHints resource
 */
#  define XDRIVER_RESOURCE_WMHINTS 3

/** Index of the Xlib XWMHints resource
 */
#  define XDRIVER_RESOURCE_CLASSHINTS 4

#  ifdef __cplusplus
extern "C" {
#  endif

namespace dxware {

class XWindowDriver: public Driver {
	public:
		XWindowDriver();
		virtual ~XWindowDriver();

		/** Set the sensitivity of the device.
		 * \param sensitivity is a value that describes the sensitivity of the device.
		 * \return true on success, otherwise false
		 */
		bool setSensitivity(float sensitivity);

		/** Initialize the connexion with the 3DxWare driver.
		 * <p>
		 * This binding is automatically done by the native layer
		 * when {\link #nextEvent()} was invoked.
		 * <p>
		 * It is not required to invoked <code>bindTo3DxWare()</code>
		 * but with it youare able to select when the native layer must
		 * try to be connected to the remote 3DxWare driver.
		 * 
		 * \return <code>true</code> if the binding was successfully done,
		 * otherwise <code>false</code>
		 */
		bool bindToRemote3DxWare();

		/** Replies the next available event from the 3D device.
		 * <p>
		 * The replied vlaue is a pointer on a static variable.
		 * You must not free the replied value and you must not retain
		 * the value to future uses.
		 *
		 * \return a pointer on the next available event. You must not free the replied value!
		 */
		const DeviceEvent* nextEvent();

		/** Replies the name of the operating system or of the
		 * window manager that is supported by this driver.
		 */
		const char* getOSName() const;

		/** Replies the number of driver resources embedded in this driver.
		 */
		unsigned short getDriverResourceCount() const;

		/** Replies the driver resource embedded in this driver at the specified index.
		 */
		const void* getDriverResourceAt(unsigned short index) const;

		/** Set the driver resource embedded in this driver at the specified index.
		 * \param index is the index of the resource.
		 * \param resource is the pointer to the resource or NULL.
		 * \return <code>true</code> if successfully set, otherwise <code>false</code>.
		 */
		bool setDriverResourceAt(unsigned short index, void* resource);

		/** Treat the given native event.
		 *
		 * \param nativeEvent is the native event to treat.
		 * \param driverEvent is the driver event which must receive the native event's data.
		 * \return true if the given event is supported by the driver, otherwise false
		 */
		inline bool treatNativeEvent(void* nativeEvent, DeviceEvent* driverEvent)
		{
			if (nativeEvent==NULL || driverEvent==NULL) return false;
			treatEvent((XEvent*)nativeEvent, driverEvent, false);
			return (driverEvent->getType()!=NO_EVENT3D);
		}

		/** Replies the atoms associated to this driver.
		 * \param id of the atom (0 for motion event, 1 for button press event,
		 * 2 for button release event, 3 for command event)
		 * \return the atom
		 */
		inline Atom getXlibAtom(unsigned char id) const {
			switch(id) {
			case 0:
				return magellanMotionEvent;
			case 1:
				return magellanButtonPressEvent;
			case 2:
				return magellanButtonReleaseEvent;
			case 3:
				return magellanCommandEvent;
			default:
				return (Atom)NULL;
			}
		}

	protected:

		/** Treat the given native event.
		 *
		 * \param xEvent is the native event to treat.
		 * \param driverEvent is the driver event which must receive the native event's data.
		 * \param consumeEvents is true to consume the pending events, otherwise false.
		 * \return true if the given event is supported by the driver, otherwise false
		 */
		bool treatEvent(XEvent* xEvent, DeviceEvent* driverEvent, bool consumeEvents);

		/** Treat a key-pressed event.
		 *
		 * \param keysym is the code of the pressed key.
		 * \param driverEvent is the driver event which must receive the native event's data.
		 * \return true if the given event is supported by the driver, otherwise false
		 */
		bool treatKeyPressedEvent(KeySym keysym, DeviceEvent* driverEvent);

		/** Treat a key-released event.
		 *
		 * \param keysym is the code of the released key.
		 * \param driverEvent is the driver event which must receive the native event's data.
		 * \return true if the given event is supported by the driver, otherwise false
		 */
		bool treatKeyReleasedEvent(KeySym keysym, DeviceEvent* driverEvent);

		/** Treat a device-motion event.
		 *
		 * \param xEvent is the native event to treat.
		 * \param driverEvent is the driver event which must receive the native event's data.
		 * \param consumeEvents is true to consume the pending events, otherwise false.
		 * \return true if the given event is supported by the driver, otherwise false
		 */
		bool treatMotionEvent(XEvent* xEvent, DeviceEvent* driverEvent, bool consumeEvents);

		/** Replies if the 3DxWare Unix driver was launched.
		 * <p>
		 * The driver is launched when the file /var/run/3dxware/3dxsrv.pid
		 * is existing.
		 *
		 * \return <code>true</code> if the driver was launched, otherwise <code>false</code>.
		 */
		static bool is3DxWareLaunched();

		/** Replies if the 3DxWare Unix driver is able to be launched.
		 * <p>
		 * The driver is ready to be launched when the directory /var/run/3dxware
		 * is existing. If the directory does not exist, the administrator of
		 * your operating system should launch the 3DxWare activator.
		 *
		 * \return <code>true</code> if the driver was launched, otherwise <code>false</code>.
		 */
		static bool is3DxWareLaunchable();

		/** Check if the 3DxWare driver is launched. If not, try to load it.
		 *
		 * \return <code>true</code> if the driver was launched during this invocation,
		 * otherwise <code>false</code> if the driver was not launched or it was
		 * launched before the invocation to this method.
		 */
		static bool ensure3DxWareDriver();

		/** Start the 3DxWare driver.
		 */
		static bool start3DxWareDriver();

		/** Stop the 3DxWare driver.
		 */
		static bool stop3DxWareDriver();

	private:
		/** Invoked to test if this driver was launched, and if not,
		 * to launch it.
		 */
		void ensureLaunched();

		/** Create and reply the Xlib window which is required by this driver.
		 *
		 * \return a Xlib window.
		 */
		Window createXWindowContext();
		/** Initialize the Magelland device.
		 *
		 * \param initWindow a Xlib window that should be used as the client of the Magellan device.
		 * \param waitForInit indicates if this function should way for the magellan driver window.
		 */
		void initMagellan(Window initWindow, bool waitForInit);

		/** Bind the magellan device this the given Xlib context (display and window).
		 *
		 * \param display is the graphical context that owns the Xlib window.
		 * \param initWindow a Xlib window that should be used as the client of the Magellan device.
		 * \return <code>true</code> if sucessfully binded, otherwise <code>false</code>.
		 */
		bool setMagellanWindow(Display* display, Window initWindow);
		/** Initialize the Xlib input mechanisms.
		 */
		void initXInput();
		/** Unbind to the Magellan device.
		 */
		void closeMagellan();
		/** Translate a Xlib event into a Magellan event.
		 *
		 * \param event is the Xlib event to translate.
		 * \param magellanEvent is the Magellan event to fill.
		 * \param magellanTranslationScale is used to scale the translations.
		 * \param magellanRotationScale is used to scale the rotations.
		 * \return the type of Magellan event.
		 */
		MagellanEventType magellanTranslateEvent(XEvent* event, MagellanFloatEvent* magellanEvent, double magellanTranslationScale, double magellanRotationScale);
		/** Consume all the motion events in the event queue.
		 *
		 * \return <code>true</code> on success, otherwise <code>false</code>.
		 */
		bool magellanRemoveMotionEvents();

		/** Function invoked by the Xlib API when an error occurs during initialization.
		 *
		 * \param display is the display in which the error occured.
		 * \param event describes the error event.
		 * \return always 0
		 */
		static int magellanErrorHandler(Display* display,XErrorEvent* event);

		/** Function invoked by the Xlib to detect motion events.
		 * This function is invoked when motion events should be consumed.
		 * \param display is the display in which the error occured.
		 * \param event describes the event to test.
		 * \param args are the values passed to the Xlib checking function.
		 * \return <code>True</code> if the given event is a motion event,
		 * otherwise <code>False</code>.
		 */
		static Bool magellanCheckMotionEvent(Display* display, XEvent* event, char* arg);

		/** Send a command to the Magellan driver.
		 * \param display is the display that own the driver.
		 * \param commandType is the type of the command to send.
		 * \param v1 is the first value to send.
		 * \param v2 is the second value to send.
		 * \return true on success, otherwise false
		 */
		bool sendMagellanCommand(Display* display, MagellanCommandType commandType, short v1, short v2);

		Display* display;
		Window window;
		Window magellanWindow;
		XSizeHints* sizehints;
		XWMHints* wmhints;
		XClassHint* classhints;
		Atom magellanMotionEvent;		/* MotionEvent */
		Atom magellanButtonPressEvent;		/* ButtonPressEvent */
		Atom magellanButtonReleaseEvent;	/* ButtonReleaseEvent */ 
		Atom magellanCommandEvent;		/* CommandEvent */

		DeviceEvent publicEvent;

		XWindowKeyManager keyManager;

		Display* display2;
		Window window2;

		bool is3DxWareDriverInternallyLaunched;
};

} /* namespace dxware */

#  ifdef __cplusplus
}
#  endif

#endif // __3DX_DRIVER_X_H__

