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

#include <stdlib.h>
#include <string.h>

#include <3dxware/3dxSpaceMouse.h>
#include <3dxware/3dxException.h>

namespace dxware {

/** Replies the version of the API that is supporting this device.
 */
const char* getAPIVersion()
{
#ifndef MAGELLAN_VERSION
#  error undefined macro MAGELLAN_VERSION
#else
#  define MAKE_VERSION(__v__) (#__v__)
	return MAKE_VERSION(MAGELLAN_VERSION);
#endif
}

SpaceMouse::SpaceMouse(): listeners(NULL), nListeners(0L)
{
	driver = new DXWARE_DRIVER();
}

SpaceMouse::SpaceMouse(const SpaceMouse& mouse): listeners(NULL), nListeners(0L)
{
	driver = new DXWARE_DRIVER();
	*this = mouse;
}

SpaceMouse::~SpaceMouse()
{
	if (listeners!=NULL) {
		::free(listeners);
		listeners = NULL;
		nListeners = 0L;
	}
	if (driver!=NULL) {
		delete driver;
		driver = NULL;
	}
}

SpaceMouse& SpaceMouse::operator=(const SpaceMouse& mouse)
{
	if (listeners!=NULL) {
		::free(listeners);
		listeners = NULL;
		nListeners = 0L;
	}
	if (mouse.listeners!=NULL) {
		listeners = (DeviceListener**)::malloc(sizeof(DeviceListener*)*mouse.nListeners);
		::memcpy(listeners, mouse.listeners, sizeof(DeviceListener*)*mouse.nListeners);
		nListeners = mouse.nListeners;
	}
	return *this;
}

SpaceMouse& SpaceMouse::operator+=(DeviceListener& listener)
{
	listeners = (DeviceListener**)::realloc(listeners, sizeof(DeviceListener*)*(nListeners+1));
	listeners[nListeners] = &listener;
	nListeners++;
	return *this;
}

SpaceMouse& SpaceMouse::operator-=(const DeviceListener& listener)
{
	for(unsigned long i=0; i<nListeners; i++) {
		if (listeners[i] == &listener) {
			::memmove(listeners+i, listeners+i+1, sizeof(DeviceListener*)*(nListeners-i-1));
			nListeners--;
			return *this;
		}
	}
	return *this;
}

unsigned long SpaceMouse::listenerCount() const
{
	return nListeners;
}

DeviceListener& SpaceMouse::operator[](unsigned long index)
{
	if (index<nListeners) {
		DeviceListener* ptr = listeners[index];
		if (ptr!=NULL) {
			return *ptr;
		}
	}
	throw DeviceException("index out of bounds",__FILE__,__LINE__);
}

const DeviceListener& SpaceMouse::operator[](unsigned long index) const
{
	if (index<nListeners) {
		DeviceListener* ptr = listeners[index];
		if (ptr!=NULL) {
			return *ptr;
		}
	}
	throw DeviceException("index out of bounds",__FILE__,__LINE__);
}

const DeviceEvent* SpaceMouse::nextEvent() {
	if (driver!=NULL) {
		return driver->nextEvent();
	}
	return NULL;
}

Driver* SpaceMouse::getDriver()
{
	return driver;
}

void SpaceMouse::loop()
{
	const DeviceEvent* event;

	continueLoop = true;

	while (continueLoop) {
		event = nextEvent();
		if (event!=NULL) {
				switch(event->getType()) {
				case dxware::KEY_PRESSED:
					fireKeyPressed(event);
					break;
				case dxware::KEY_RELEASED:
					fireKeyReleased(event);
					break;
				case dxware::MOUSE3D_MOTION:
					fireMouse3DMotion(event);
					break;
				case dxware::BUTTON3D_PRESSED:
					fireButton3DPressed(event);
					break;
				case dxware::BUTTON3D_RELEASED:
					fireButton3DReleased(event);
					break;
				case dxware::NO_EVENT3D:
					break;
			}
		}
	}
}

void SpaceMouse::stopLoop()
{
	continueLoop = false;
}

void SpaceMouse::fireKeyPressed(const DeviceEvent* event) const
{
	for(unsigned long i=0; i<nListeners; i++) {
		if (listeners[i]!=NULL) {
			listeners[i]->onKeyPressed(*event);
		}
	}
}

void SpaceMouse::fireKeyReleased(const DeviceEvent* event) const
{
	for(unsigned long i=0; i<nListeners; i++) {
		if (listeners[i]!=NULL) {
			listeners[i]->onKeyReleased(*event);
		}
	}
}

void SpaceMouse::fireMouse3DMotion(const DeviceEvent* event) const
{
	for(unsigned long i=0; i<nListeners; i++) {
		if (listeners[i]!=NULL) {
			listeners[i]->onDeviceMotion(*event);
		}
	}
}

void SpaceMouse::fireButton3DPressed(const DeviceEvent* event) const
{
	for(unsigned long i=0; i<nListeners; i++) {
		if (listeners[i]!=NULL) {
			listeners[i]->onDeviceButtonPressed(*event);
		}
	}
}

void SpaceMouse::fireButton3DReleased(const DeviceEvent* event) const
{
	for(unsigned long i=0; i<nListeners; i++) {
		if (listeners[i]!=NULL) {
			listeners[i]->onDeviceButtonReleased(*event);
		}
	}
}

} /* namespace dxware */

