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
#ifndef __3DX_EXCEPTION_H__
#  define __3DX_EXCEPTION_H__

#  include <stdio.h>

namespace dxware {

/** Exception in the 3D device driver.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
class DeviceException {
	public:
		/**
		 * \param message is the error message.
		 * \param filename is the name of the file in which the error occured.
		 * \param lineNumber is the line number at which the error occured.
		 */
		inline DeviceException(const char* message, const char* filename, int lineNumber): msg(message), line(lineNumber), file(filename) {};
		/**
		 * \return the error message.
		 */
		inline const char* getMessage() const { return msg; };
		/**
		 * \return the name of the file in which the error occured.
		 */
		inline const char* getFile() const { return file; };
		/**
		 * \return the line in the file at which the error occured.
		 */
		inline int getLine() const { return line; };
		/**
		 * Display the exception on the standard error output.
		 */
#ifdef DEBUG
		inline void printf() {
			fprintf(stderr,"DeviceException(%s:%d): %s\n", getFile(), getLine(), getMessage());
		}
#else
		inline void printf() {
			fprintf(stderr,"DeviceException: %s\n", getMessage());
		}
#endif
	private:
		const char* msg;
		const int line;
		const char* file;
};

} /* namespace dxware */

#endif // __3DX_EXCEPTION_H__

