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
#include <3dxware/MSwin/3dxDriverMS.h>
#include <3dxware/3dxException.h>
#include <3dxware/3dxCmdLine.h>

#define __STRINGIFY(__v__) #__v__

namespace dxware {

const char* MSWindowDriver::getOSName() const
{
	return "Microsoft/" __STRINGIFY(PLATFORM);
}

MSWindowDriver::MSWindowDriver()
: g3DSensitivity(1.0)
{
}

MSWindowDriver::~MSWindowDriver()
{
}

unsigned short MSWindowDriver::getDriverResourceCount() const
{
	return 0;
}

const void* MSWindowDriver::getDriverResourceAt(unsigned short index) const
{
	return NULL;
}

bool MSWindowDriver::setDriverResourceAt(unsigned short index, void* resource)
{
	return false;
}

bool MSWindowDriver::setSensitivity(float sensitivity)
{
	return false;
}

void MSWindowDriver::ensureLaunched()
{
	if (!isLaunched()) {
		setLaunched();
	}
}

bool MSWindowDriver::bindToRemote3DxWare()
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

const DeviceEvent* MSWindowDriver::nextEvent()
{
	ensureLaunched();
	return NULL;
}

} /* namespace dxware */

