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
#ifndef __3DX_CMD_LINE_H__
#  define __3DX_CMD_LINE_H__

#  ifdef __cplusplus
extern "C" {
#  endif

namespace dxware {

/** Returns the number of parameters on the command line.
 *
 * \return the number of parameters on the command line.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
unsigned int getCommandLineOptionCount();

/** Returns the parameters on the command line.
 *
 * \return the parameters on the command line.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
char** getCommandLineOptions();

/** Returns the parameter at the specified index on the command line.
 *
 * \param index is the index of the parameter to reply.
 * \return the parameter at the specified index on the command line.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
const char* getCommandLineOption(unsigned int index);

/** Returns the name of the program on the command line.
 *
 * \return the name of the program on the command line.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
const char* getCommandLineProgram();

/** Save the information given to the main program about the command line.
 *
 * \param argc is the number of arguments on the command line.
 * \param argv is the list of the arguments on the command line.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
void saveCommandLine(unsigned int argc, char** argv);

} /* namespace dxware */

#  ifdef __cplusplus
}
#  endif

#endif // __3DX_CMD_LINE_H__

