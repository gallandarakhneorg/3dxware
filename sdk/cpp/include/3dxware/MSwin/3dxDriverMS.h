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
#ifndef __3DX_DRIVER_MS_H__
#  define __3DX_DRIVER_MS_H__

#  include <windows.h>

#  include <3dxware/3dxDriver.h>

#  ifdef DXWARE_DRIVER
#    error a driver was already included.
#  else
#    define DXWARE_DRIVER dxware::MSWindowDriver
#  endif

#  ifdef __cplusplus
extern "C" {
#  endif

//#import "progid:TDxInput.Device.1" no_namespace

namespace dxware {

class MSWindowDriver: public Driver {
	public:
		MSWindowDriver();
		virtual ~MSWindowDriver();

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
		 * but with it you are able to select when the native layer must
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
			//treatEvent((XEvent*)nativeEvent, driverEvent, false);
			//return (driverEvent->getType()!=NO_EVENT3D);
			return false;
		}

	protected:

		/** Ensure that the driver is connected to the low-level 3DxWare driver.
		 * If not starts the connection.
		 */
		void ensureLaunched();

	private:

		double g3DSensitivity;
		//CComPtr<ISensor> g3DSensor;
		//CComPtr<IKeyboard> g3DKeyboard;

};

} /* namespace dxware */

#  ifdef __cplusplus
}
#  endif

#endif // __3DX_DRIVER_MS_H__

