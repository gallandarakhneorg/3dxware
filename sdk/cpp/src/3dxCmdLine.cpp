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

#include <3dxware/3dxCmdLine.h>
#include <3dxware/3dxException.h>

#ifdef __cplusplus
extern "C" {
#endif

namespace dxware {

static unsigned int argCount = 0;
static char** argValues = NULL;

static const char _defaultProgramName[9] = {
	'p', 'r', 'o', 'g', 'r', 'a', 'm', '\0'
};
static const char* _defaultCommandLineList[1] = {
	_defaultProgramName
};

unsigned int getCommandLineOptionCount()
{
	return (argCount>=1) ? argCount : 1;
}

char** getCommandLineOptions()
{
	if (argCount>=1) return argValues;
	return (char**)_defaultCommandLineList;
}

const char* getCommandLineOption(unsigned int index)
{
	if ((index+1)<argCount) return argValues[index+1];
	throw DeviceException("index out of bounds",__FILE__,__LINE__);
}

const char* getCommandLineProgram()
{
	if (argCount>0) return argValues[0];
	throw DeviceException("no parameter saved",__FILE__,__LINE__);
}

void saveCommandLine(unsigned int argc, char** argv)
{
	argCount = argc;
	argValues = argv;
}

} /* namespace dxware */

#ifdef __cplusplus
}
#endif

