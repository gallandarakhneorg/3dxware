/*
 * Copyright (c) 2008-2009 Stéphane GALLAND <galland@arakhne.org>
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
#ifndef __3DX_EVENT_H__
#  define __3DX_EVENT_H__

#  include <3dxware/3dxKey.h>

namespace dxware {

/** List of types of events forwarded by the 3D device driver.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
typedef enum {
	/** No event.
	 */
	NO_EVENT3D=0,
	/** A keyboard key was pressed.
	 */
	KEY_PRESSED=1,
	/** A keyboard key was released.
	 */
	KEY_RELEASED=2,
	/** The 3D device has motion.
	 */
	MOUSE3D_MOTION=3,
	/** A button on the 3D device was pressed.
	 */
	BUTTON3D_PRESSED=4,
	/** A button on the 3D device was released.
	 */
	BUTTON3D_RELEASED=5
} EventType;

/** List of data replied by the 3D driver.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
typedef enum {
	/** X translation coordinate. */
	COORD_X,
	/** Y translation coordinate. */
	COORD_Y,
	/** Z translation coordinate. */
	COORD_Z,
	/** Axis A rotation. */
	COORD_A,
	/** Axis B rotation. */
	COORD_B,
	/** Axis C rotation. */
	COORD_C
} MagellanCoordinate;

/** Describe an event in a 3D device.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
class DeviceEvent {
	public:
		DeviceEvent();
		virtual ~DeviceEvent();

		/** Set the type of the event. */
		void setType(EventType type);
		/** Replies the type of the event. */
		EventType getType() const;
		/** Set key embedded in this event.
		 * \param key is the pressed/released key.
		 * \param modifiers is the list of keyboard modifiers.
		 */
		void setKey(EventKey key, ModifierKeyField modifiers);
		/** Replies  the pressed/released key.
		 */
		EventKey getKey() const;
		/** Replies the list of keyboard modifiers.
		 */
		ModifierKeyField getKeyModifiers() const;
		/** Set 3d device button embedded in this event.
		 */
		void setButton(unsigned int button);
		/** Replies 3d device button embedded in this event.
		 */
		unsigned int getButton() const;
		/** Set coordinates embedded in this event.
		 */
		void setCoordinates(float x, float y, float z, float a, float b, float c);
		/** Replies the coordinate at the specified index.
		 *
		 * \param index is the index of the coordinate to reply
		 * \return the coordinate value
		 */
		float getCoordinate(MagellanCoordinate index) const;

		/** Replies the period of the last motion event in milliseconds.
		 * \return period of the last event.
		 */
		unsigned long getPeriod() const;

		/** Set the period of the last motion event in milliseconds.
		 * \param period of the last event.
		 */
		void setPeriod(unsigned long period);

	private:
		EventType eventType;
		EventKey eventKey;
		ModifierKeyField keyModifiers;
		unsigned int mouseButton;
		float coordinates[6];
		unsigned long eventPeriod;
};

/** Describe an event listener on a 3D device.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
class DeviceListener {
	public:
		virtual void onDeviceMotion(const DeviceEvent& event) = 0;
		virtual void onDeviceButtonPressed(const DeviceEvent& event) = 0;
		virtual void onDeviceButtonReleased(const DeviceEvent& event) = 0;
		virtual void onKeyPressed(const DeviceEvent& event) = 0;
		virtual void onKeyReleased(const DeviceEvent& event) = 0;
};

}

#endif // __3DX_EVENT_H__

