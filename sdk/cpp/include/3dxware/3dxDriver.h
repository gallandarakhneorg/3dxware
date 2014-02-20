/*
 * Copyright (c) 2008-2014 Stéphane GALLAND <galland@arakhne.org>
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
#ifndef __3DX_DRIVER_H__
#  define __3DX_DRIVER_H__

#  include <3dxware/3dxEvent.h>

#  ifdef __cplusplus
extern "C" {
#  endif

namespace dxware {

/** Data structure that representes a Magellan's message.
 *
 * \param argc is the number of arguments on the command line.
 * \param argv is the list of the arguments on the command line.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
typedef struct {
	/** Type of the Magellan's message. */
	int magellanType;
	/** Pressed button on the 3Dx device. */
	int magellanButton;
	/** Associated data. */
	double magellanData[6];
	/** Time period. */
	int magellanPeriod;
} MagellanFloatEvent;

/** List of the message types supported by the Magellan low-level driver as output.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
typedef enum {
	/** No message.
	 */
	MAGELLAN_NO_EVENT=0,
	/** The 3D device has a motion.
 	 */
	MAGELLAN_INPUT_MOTION_EVENT=1,
	/** A button on the 3D device was pressed.
	 */
	MAGELLAN_INPUT_BUTTON_PRESS_EVENT=2,
	/** A button on the 3D device was released.
	 */
	MAGELLAN_INPUT_BUTTON_RELEASE_EVENT=3
} MagellanEventType;

/** List of the message types supported by the Magellan low-level driver as input.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
typedef enum {
	/** Describe the application window to notify.
	 */
	MAGELLAN_COMMAND_APPLICATION_WINDOW = 27695, 
	/** Message about sensitivity.
	 */
	MAGELLAN_COMMAND_SENSITIVITY
} MagellanCommandType;

/** Abstract class for the low-level drivers.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
class Driver {

	public:
		Driver();
		virtual ~Driver() {};

		/** Set the sensitivity of the device.
		 * \param sensitivity is a value that describes the sensitivity of the device.
		 * \return true on success, otherwise false
		 */
		virtual bool setSensitivity(float sensitivity)=0;

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
		virtual bool bindToRemote3DxWare()=0;

		/** Replies the next available event from the 3D device.
		 * <p>
		 * The replied vlaue is a pointer on a static variable.
		 * You must not free the replied value and you must not retain
		 * the value to future uses.
		 *
		 * \return a pointer on the next available event. You must not free the replied value!
		 */
		virtual const DeviceEvent* nextEvent()=0;

		/** Set if this driver is able to forward the keyboard events.
		 *
		 * \param allowKeyEvents is <code>true</code> to allow keyboard events to be replied
		 * by this driver, otherwise <code>false</code>.
		 */
		void setKeyEventAllowed(bool allowKeyEvents);

		/** Replies if this driver is able to forward the keyboard events.
		 *
		 * \return <code>true</code> if this drvier is allowed to forward keyboard events,
		 * otherwise <code>false</code>.
		 */
		bool isKeyEventAllowed() const;

		/** Replies if this driver is blocking until an event arrived.
		 *
		 * \return <code>true</code> if this driver is blocking until an event arrived,
		 * otherwise <code>false</code>.
		 */
		bool isBlocking() const;

		/** Set if this driver is blocking until an event arrived.
		 *
		 * \param blocking is <code>true</code> to block the driver until an event arrived,
		 * otherwise <code>false</code>.
		 */
		void setBlocking(bool blocking);

		/** Replies the version of the API that is supporting this device.
		 */
		const char* getAPIVersion() const;

		/** Replies the name of the operating system or of the
		 * window manager that is supported by this driver.
		 */
		virtual const char* getOSName() const=0;

		/** Replies the number of driver resources embedded in this driver.
		 */
		virtual unsigned short getDriverResourceCount() const=0;

		/** Replies the driver resource embedded in this driver at the specified index.
		 * \param index is the index of the resource.
		 * \return the pointer to the resource or NULL.
		 */
		virtual const void* getDriverResourceAt(unsigned short index) const=0;

		/** Set the driver resource embedded in this driver at the specified index.
		 * \param index is the index of the resource.
		 * \param resource is the pointer to the resource or NULL.
		 * \return <code>true</code> if successfully set, otherwise <code>false</code>.
		 */
		virtual bool setDriverResourceAt(unsigned short index, void* resource)=0;

		/** Treat the given native event.
		 *
		 * \param nativeEvent is the native event to treat.
		 * \param driverEvent is the driver event which must receive the native event's data.
		 * \return true if the given event is supported by the driver, otherwise false
		 */
		virtual bool treatNativeEvent(void* nativeEvent, DeviceEvent* driverEvent)=0;

	protected:
		/** Replies if this driver was launched.
		 */
		bool isLaunched() const;

		/** Set that this driver was launched.
		 */
		void setLaunched();
	private:
		bool isDriverLaunched;
		bool allowKeyEventFlag;
		bool isBlockingState;

};

} /* namespace dxware */

#  ifdef __cplusplus
}
#  endif

#  ifdef X11
#    include <3dxware/Xwin/3dxDriverX.h>
#  elif defined(WIN32) || defined(WIN64)
#    include <3dxware/MSwin/3dxDriverMS.h>
#  else
#    error Operating system not supported.
#  endif

#endif // __3DX_DRIVER_H__

