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

#include <3dxware/debug.h>
#include <3dxware/3dxDriver.h>

#define _QUOTEME(x)		#x
#define QUOTEME(x)		_QUOTEME(x)

#ifdef __cplusplus
extern "C" {
#endif

namespace dxware {

Driver::Driver(): isDriverLaunched(false), allowKeyEventFlag(false), isBlockingState(true)
{
}

void Driver::setKeyEventAllowed(bool allowKeyEvents)
{
	dbg1("setKeyEventAllowed=%s",(allowKeyEvents ? "true":"false"));
	allowKeyEventFlag = allowKeyEvents;
}

bool Driver::isKeyEventAllowed() const
{
	return allowKeyEventFlag;
}

bool Driver::isLaunched() const {
	return isDriverLaunched;
}

void Driver::setLaunched()
{
	isDriverLaunched = true;
}

bool Driver::isBlocking() const
{
	return isBlockingState;
}

void Driver::setBlocking(bool blocking)
{
	dbg1("setBlocking=%s",(blocking ? "true":"false"));
	isBlockingState = blocking;
}


const char* Driver::getAPIVersion() const
{
#ifndef MAGELLAN_VERSION
#  error undefined macro MAGELLAN_VERSION
#else
#  define _QUOTEME(x) #x
#  define QUOTEME(x) _QUOTEME(x)
	return QUOTEME(MAGELLAN_VERSION);
#endif
}

} /* namespace dxware */

#ifdef __cplusplus
}
#endif

