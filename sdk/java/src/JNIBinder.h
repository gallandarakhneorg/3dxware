/*
 * Copyright (c) 2008-2014 Stéphane GALLAND <galland@arakhne.org>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; see the file COPYING. If not, write to the Free
 * Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */
#ifndef __JNI_BINDER_H__
#  define __JNI_BINDER_H__

#include <jni.h>

#include "3dxware/3dxDriver.h"

namespace dxwarejni {

/** Type of the peer component.
 */
typedef enum
{
	PEER_UNKNOW=0,
	PEER_FRAME=1,
	PEER_DIALOG=2
} PeerComponentType;

/** Bind the given driver with the GUI resource specified by
 * the given name.
 */
void bind(JNIEnv* env, jobject jcomponent, dxware::Driver* driver, const char* name, const char* title, const char* typeName, PeerComponentType type);

}

#endif // __JNI_BINDER_H__

