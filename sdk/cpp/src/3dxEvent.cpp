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

#include <3dxware/3dxEvent.h>

#ifdef __cplusplus
extern "C" {
#endif

namespace dxware {

DeviceEvent::DeviceEvent(): eventType(NO_EVENT3D), eventKey(KEY_VOID), keyModifiers(0), mouseButton(0), eventPeriod(0)
{
}

DeviceEvent::~DeviceEvent()
{
}

void DeviceEvent::setType(EventType type) {
	eventType = type;
}

EventType DeviceEvent::getType() const {
	return eventType;
}

void DeviceEvent::setKey(EventKey key, ModifierKeyField modifiers) {
	eventKey = key;
	keyModifiers = modifiers;
	eventPeriod = 0;
}

EventKey DeviceEvent::getKey() const {
	return eventKey;
}

ModifierKeyField DeviceEvent::getKeyModifiers() const
{
	return keyModifiers;
}

void DeviceEvent::setButton(unsigned int button) {
	mouseButton = button;
	eventPeriod = 0;
}

unsigned int DeviceEvent::getButton() const {
	return mouseButton;
}

void DeviceEvent::setCoordinates(float x, float y, float z, float a, float b, float c)
{
	coordinates[COORD_X] = x;
	coordinates[COORD_Y] = y;
	coordinates[COORD_Z] = z;
	coordinates[COORD_A] = a;
	coordinates[COORD_B] = b;
	coordinates[COORD_C] = c;
	eventPeriod = 0;
}

float DeviceEvent::getCoordinate(MagellanCoordinate index) const
{
	return coordinates[index];
}


unsigned long DeviceEvent::getPeriod() const
{
	return eventPeriod;
}

void DeviceEvent::setPeriod(unsigned long period)
{
	eventPeriod = period;
}

} /* namespace dxware */

#ifdef __cplusplus
}
#endif

