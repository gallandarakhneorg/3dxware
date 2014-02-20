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
#ifndef __3DX_SPACE_MOUSE_H__
#  define __3DX_SPACE_MOUSE_H__

#  include <3dxware/3dxEvent.h>
#  include <3dxware/3dxDriver.h>

#  ifdef __cplusplus
extern "C" {
#  endif

namespace dxware {

/** This class represents a 3D device named a SpaceMouse.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
class SpaceMouse {
	public:
		SpaceMouse();
		SpaceMouse(const SpaceMouse& mouse);
		virtual ~SpaceMouse();

		SpaceMouse& operator=(const SpaceMouse& mouse);

		/** Add a listener on the device events.
		 */
		SpaceMouse& operator+=(DeviceListener& listener);
		/** Remove a listener on the device events.
		 */
		SpaceMouse& operator-=(const DeviceListener& listener);

		/** Replies the count of listeners binded with this device.
		 *
		 * \return the count of listeners binded with this device.
		 */
		unsigned long listenerCount() const;
		/** Replies the listener at the specified index.
		 *
		 * \return the listener at the specified index.
		 */
		DeviceListener& operator[](unsigned long index);
		/** Replies the listener at the specified index.
		 *
		 * \return the listener at the specified index.
		 */
		const DeviceListener& operator[](unsigned long index) const;

		/** Replies the next available event from the 3D device.
		 * <p>
		 * The replied value is a pointer on a static variable.
		 * You must not free the replied value and you must not retain
		 * the value to future uses.
		 * <p>
		 * This function does not invoke the listeners.
		 *
		 * \return a pointer on the next available event. You must not free the replied value!
		 */
		const DeviceEvent* nextEvent();

		/** Launch an infinite loop which is taken the next events
		 * and forward it to the listeners.
		 */
		void loop();

		/** Stop the loop.
		 */
		void stopLoop();

		/** Replies the driver associated to this device.
		 *
		 * \return a pointer to the device. This pointer should not be free.
		 */
		Driver* getDriver();

		/** Replies the version of the API that is supporting this device.
		 */
		static const char* getAPIVersion();

	protected:

		/** Notify listeners on a keyboard key pressed event.
		 */
		void fireKeyPressed(const DeviceEvent* event) const;

		/** Notify listeners on a keyboard key released event.
		 */
		void fireKeyReleased(const DeviceEvent* event) const;

		/** Notify listeners on a 3D mouse motion event.
		 */
		void fireMouse3DMotion(const DeviceEvent* event) const;

		/** Notify listeners on a 3D button pressed event.
		 */
		void fireButton3DPressed(const DeviceEvent* event) const;

		/** Notify listeners on a 3D button released event.
		 */
		void fireButton3DReleased(const DeviceEvent* event) const;

	private:
		DeviceListener** listeners;
		Driver* driver;
		unsigned long nListeners;
		bool continueLoop;
};

} /* namespace dxware */

#  ifdef __cplusplus
}
#  endif

#endif // __3DX_SPACE_MOUSE_H__

