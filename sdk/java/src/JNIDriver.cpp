/*
 * Copyright (c) 2008 Stéphane GALLAND <galland@arakhne.org>
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

#include <jawt.h>

#include "3dxware/debug.h"
#include "3dxware/3dxException.h"
#include "3dxware/3dxEvent.h"
#include "JNIDriver.h"
#include "JNIBinder.h"

#ifdef __cplusplus
extern "C" {
#endif

static void throwException(JNIEnv* env, const dxware::DeviceException& exception)
{
	jclass eClass = env->FindClass("Lorg/arakhne/dxware/DeviceException;");
	if (eClass!=NULL) {
		env->ThrowNew(eClass, exception.getMessage());
	}
	else {
		throw exception;
	}
}

static void throwError(JNIEnv* env)
{
	jclass eClass = env->FindClass("Lorg/arakhne/dxware/DeviceError;");
	if (eClass!=NULL) {
		env->ThrowNew(eClass, "internal error in the 3DxWare device driver");
	}
	fprintf(stderr, "Internal error in the 3DxWare device driver\n");
}

JNIEXPORT jlong JNICALL Java_org_arakhne_dxware_Driver_allocateDriverResources(JNIEnv* env, jobject object)
{
	dbg("initialize the JNI driver");
	try {
		dxware::Driver* driver = new DXWARE_DRIVER();
		driver->setBlocking(false);
		driver->setKeyEventAllowed(false);
		return (jlong)driver;
	}
	catch(dxware::DeviceException e) {
		throwException(env, e);
		return 0;
	}
	catch(...) {
		throwError(env);
		return 0;
	}
}

JNIEXPORT void JNICALL Java_org_arakhne_dxware_Driver_releaseDriverResources(JNIEnv* env, jobject object, jlong ptrDriver)
{
	dbg("destroy the JNI driver");
	try {
		dxware::Driver* driver = (dxware::Driver*)ptrDriver;
		if (driver!=NULL) {
			delete driver;
		}
	}
	catch(dxware::DeviceException e) {
		throwException(env, e);
	}
	catch(...) {
		throwError(env);
	}
}

JNIEXPORT jstring JNICALL Java_org_arakhne_dxware_Driver_getAPIVersion(JNIEnv* env, jobject object, jlong ptrDriver)
{
	try {
		dxware::Driver* driver = (dxware::Driver*)ptrDriver;
		dbg1("getAPIVersion=%s", driver->getAPIVersion());
		return env->NewStringUTF(driver->getAPIVersion());
	}
	catch(dxware::DeviceException e) {
		throwException(env, e);
		return NULL;
	}
	catch(...) {
		throwError(env);
		return NULL;
	}
}

JNIEXPORT jstring JNICALL Java_org_arakhne_dxware_Driver_getOSName(JNIEnv* env, jobject object, jlong ptrDriver)
{
	try {
		dxware::Driver* driver = (dxware::Driver*)ptrDriver;
		dbg1("getOSName=%s", driver->getOSName());
		return env->NewStringUTF(driver->getOSName());
	}
	catch(dxware::DeviceException e) {
		throwException(env, e);
		return NULL;
	}
	catch(...) {
		throwError(env);
		return NULL;
	}
}

JNIEXPORT void JNICALL Java_org_arakhne_dxware_Driver_bindPeer(JNIEnv* env, jobject object, jlong ptrDriver, jobject awtComponent, jstring componentName, jstring componentTitle, jstring componentClass, jbyte componentType)
{
	try {
		const char* name = (componentName==NULL) ? NULL : env->GetStringUTFChars(componentName,NULL); 
		const char* title = (componentTitle==NULL) ? NULL : env->GetStringUTFChars(componentTitle,NULL); 
		const char* clazz = (componentClass==NULL) ? NULL : env->GetStringUTFChars(componentClass,NULL); 

		dxware::Driver* driver = (dxware::Driver*)ptrDriver;
		dbg2("bind peer '%s' - '%s'", name, title);
		dxwarejni::bind(env, awtComponent, driver, name, title, clazz, (dxwarejni::PeerComponentType)componentType);
		if (name!=NULL) env->ReleaseStringUTFChars(componentName, name);
		if (title!=NULL) env->ReleaseStringUTFChars(componentTitle, title);
		if (clazz!=NULL) env->ReleaseStringUTFChars(componentClass, clazz);
	}
	catch(dxware::DeviceException e) {
		throwException(env, e);
	}
	catch(...) {
		throwError(env);
	}
}

JNIEXPORT jboolean JNICALL Java_org_arakhne_dxware_Driver_bindTo3DxWare(JNIEnv* env, jobject object, jlong ptrDriver)
{
	try {
		dxware::Driver* driver = (dxware::Driver*)ptrDriver;
		return driver->bindToRemote3DxWare();
	}
	catch(...) {
		return false;
	}
}

JNIEXPORT jboolean JNICALL Java_org_arakhne_dxware_Driver_treatNativeEvent(JNIEnv* env, jobject object, jlong ptrDriver, jlong eventPtr, jobject deviceEvent)
{
	try {
		dxware::Driver* driver = (dxware::Driver*)ptrDriver;
		void* nativeEvent = (void*)eventPtr;
		dxware::DeviceEvent dxevent;

		if (driver->treatNativeEvent(nativeEvent, &dxevent)) {
			jclass cls = env->GetObjectClass(deviceEvent);
			jmethodID mid = env->GetMethodID(cls, "set", "(IIIBFFFFFF)V");
			if (mid == 0) return false;

			env->CallVoidMethod(deviceEvent, mid,
				(jint)dxevent.getType(),
				(jint)dxevent.getKey(),
				(jint)dxevent.getKeyModifiers(),
				(jbyte)dxevent.getButton(),
				(jfloat)dxevent.getCoordinate(dxware::COORD_X),
				(jfloat)dxevent.getCoordinate(dxware::COORD_Y),
				(jfloat)dxevent.getCoordinate(dxware::COORD_Z),
				(jfloat)dxevent.getCoordinate(dxware::COORD_A),
				(jfloat)dxevent.getCoordinate(dxware::COORD_B),
				(jfloat)dxevent.getCoordinate(dxware::COORD_C));
			return true;
		}
	}
	catch(dxware::DeviceException e) {
		throwException(env, e);
	}
	catch(...) {
		throwError(env);
	}
	return false;
}

JNIEXPORT jboolean JNICALL Java_org_arakhne_dxware_Driver_isKeyboardEventFired(JNIEnv* env, jobject object, jlong ptrDriver)
{
	try {
		dxware::Driver* driver = (dxware::Driver*)ptrDriver;
		return driver->isKeyEventAllowed();
	}
	catch(dxware::DeviceException e) {
		throwException(env, e);
	}
	catch(...) {
		throwError(env);
	}
	return false;
}

JNIEXPORT void JNICALL Java_org_arakhne_dxware_Driver_setKeyboardEventFired(JNIEnv* env, jobject object, jlong ptrDriver, jboolean isAllowed)
{
	try {
		dxware::Driver* driver = (dxware::Driver*)ptrDriver;
		driver->setKeyEventAllowed(isAllowed);
	}
	catch(dxware::DeviceException e) {
		throwException(env, e);
	}
	catch(...) {
		throwError(env);
	}
}

JNIEXPORT void JNICALL Java_org_arakhne_dxware_Driver_setSensitivity(JNIEnv* env, jobject object, jlong ptrDriver, jfloat sensitivity)
{
	try {
		dxware::Driver* driver = (dxware::Driver*)ptrDriver;
		driver->setSensitivity((float)sensitivity);
	}
	catch(dxware::DeviceException e) {
		throwException(env, e);
	}
	catch(...) {
		throwError(env);
	}
}

#ifdef __cplusplus
}
#endif
