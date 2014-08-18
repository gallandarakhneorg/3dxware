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

#include <stdio.h>
#include <math.h>

#include <3dxware/Xwin/MagellanUnixDrv.h>
#include <3dxware/debug.h>

#ifdef __cplusplus
extern "C" {
#endif

Atom MagellanMotionEvent;
Atom MagellanButtonPressEvent;
Atom MagellanReleaseEvent;
Window MagellanWindow;
int MagellanExist;

static dxware::Driver* dxDriver = NULL;

int MagellanInit(Display* display, Window window)
{
	if (display!=NULL && dxDriver==NULL) {
		dxDriver = new DXWARE_DRIVER();
		dxDriver->setKeyEventAllowed(false);
		if (MagellanSetWindow(display, window)) {
			MagellanExist = TRUE;
			MagellanWindow = window;
			MagellanMotionEvent = ((dxware::XWindowDriver*)dxDriver)->getXlibAtom(0);
			MagellanButtonPressEvent = ((dxware::XWindowDriver*)dxDriver)->getXlibAtom(1);
			MagellanReleaseEvent = ((dxware::XWindowDriver*)dxDriver)->getXlibAtom(2);
			return TRUE;
		}
	}
	MagellanExist = FALSE;
	MagellanWindow = (Window)NULL;
	MagellanMotionEvent = (Atom)NULL;
	MagellanButtonPressEvent = (Atom)NULL;
	MagellanReleaseEvent = (Atom)NULL;
	return FALSE;
}

int MagellanSetWindow(Display* display, Window window)
{
	if (display!=NULL && dxDriver!=NULL) {
		dxDriver->setDriverResourceAt(XDRIVER_RESOURCE_DISPLAY, display);
		dxDriver->setDriverResourceAt(XDRIVER_RESOURCE_WINDOW, &window);
		return dxDriver->bindToRemote3DxWare() ? TRUE : FALSE;
	}
	return FALSE;
}

int MagellanApplicationSensitivity(Display* display, double sensitivity)
{
	if (display!=NULL && dxDriver!=NULL) {
		dxDriver->setSensitivity((float)sensitivity);
		return TRUE;
	}
	return FALSE;
}

int MagellanInputEvent(Display* display, XEvent* xEvent, MagellanIntEvent* magellanEvent)
{
	if (display!=NULL && dxDriver!=NULL) {
		dxware::DeviceEvent deviceEvent;
		if (dxDriver->treatNativeEvent(xEvent, &deviceEvent)) {
			switch(deviceEvent.getType()) {
			case dxware::MOUSE3D_MOTION:
				magellanEvent->type = MagellanInputMotionEvent;
				magellanEvent->u.data[0] = deviceEvent.getCoordinate(dxware::COORD_X);
				magellanEvent->u.data[1] = deviceEvent.getCoordinate(dxware::COORD_Y);
				magellanEvent->u.data[2] = deviceEvent.getCoordinate(dxware::COORD_Z);
				magellanEvent->u.data[3] = deviceEvent.getCoordinate(dxware::COORD_A);
				magellanEvent->u.data[4] = deviceEvent.getCoordinate(dxware::COORD_B);
				magellanEvent->u.data[5] = deviceEvent.getCoordinate(dxware::COORD_C);
				magellanEvent->u.data[6] = deviceEvent.getPeriod()*1000/60; // Don't know why, but from 3D connexion driver
				return MagellanInputMotionEvent;
			case dxware::BUTTON3D_PRESSED:
				magellanEvent->type = MagellanInputButtonPressEvent;
				magellanEvent->u.button = deviceEvent.getButton();
				return MagellanInputButtonPressEvent;
			case dxware::BUTTON3D_RELEASED:
				magellanEvent->type = MagellanInputButtonReleaseEvent;
				magellanEvent->u.button = deviceEvent.getButton();
				return MagellanInputButtonReleaseEvent;
			default:
				{}
			}
		}
	}
	return 0;
}

int MagellanTranslateEvent(Display* display, XEvent* xEvent, MagellanFloatEvent* magellanEvent, double magellanTranslationScale, double magellanRotationScale)
{
	if (display!=NULL && dxDriver!=NULL) {
		dxware::DeviceEvent deviceEvent;
		if (dxDriver->treatNativeEvent(xEvent, &deviceEvent)) {
			switch(deviceEvent.getType()) {
			case dxware::MOUSE3D_MOTION:
				magellanEvent->MagellanType = MagellanInputMotionEvent;
				magellanEvent->MagellanData[MagellanX] = deviceEvent.getCoordinate(dxware::COORD_X) * magellanTranslationScale;
				magellanEvent->MagellanData[MagellanY] = deviceEvent.getCoordinate(dxware::COORD_Y) * magellanTranslationScale;
				magellanEvent->MagellanData[MagellanZ] = deviceEvent.getCoordinate(dxware::COORD_Z) * magellanTranslationScale;
				magellanEvent->MagellanData[MagellanA] = deviceEvent.getCoordinate(dxware::COORD_A) * magellanRotationScale;
				magellanEvent->MagellanData[MagellanB] = deviceEvent.getCoordinate(dxware::COORD_B) * magellanRotationScale;
				magellanEvent->MagellanData[MagellanC] = deviceEvent.getCoordinate(dxware::COORD_C) * magellanRotationScale;
				magellanEvent->MagellanPeriod = deviceEvent.getPeriod();
				return MagellanInputMotionEvent;
			case dxware::BUTTON3D_PRESSED:
				magellanEvent->MagellanType = MagellanInputButtonPressEvent;
				magellanEvent->MagellanButton = deviceEvent.getButton();
				return MagellanInputButtonPressEvent;
			case dxware::BUTTON3D_RELEASED:
				magellanEvent->MagellanType = MagellanInputButtonReleaseEvent;
				magellanEvent->MagellanButton = deviceEvent.getButton();
				return MagellanInputButtonReleaseEvent;
			default:
				{}
			}
		}
	}
	return 0;
}

int MagellanClose(Display* display)
{
	if (display!=NULL && dxDriver!=NULL) {
		delete dxDriver;
		dxDriver = NULL;
		return TRUE;
	}
	return FALSE;
}

int MagellanRotationMatrix(double rotate[4][4], double c, double b, double a)
{
	double ca,cb,cc,sa,sb,sc;

	ca = cos( a ); sa = sin( a );
	cb = cos( b ); sb = sin( b );
	cc = cos( c ); sc = sin( c );

	rotate[0][0] = ca*cb;
	rotate[1][0] = sa*cb;
	rotate[2][0] =-sb;

	rotate[0][1] =-sa*cc+ca*sc*sb;
	rotate[1][1] = ca*cc+sa*sc*sb;
	rotate[2][1] = cb*sc;

	rotate[0][2] = sa*sc+ca*cc*sb;
	rotate[1][2] =-ca*sc+sa*cc*sb;
	rotate[2][2] = cb*cc;

	rotate[0][3] = 0.0;
	rotate[1][3] = 0.0;
	rotate[2][3] = 0.0;

	rotate[3][0] = 0.0;
	rotate[3][1] = 0.0;
	rotate[3][2] = 0.0;

	rotate[3][3] = 1.0;

	return TRUE;
}

int MagellanMultiplicationMatrix(double matrixA[4][4], double matrixB[4][4], double matrixC[4][4])
{
	double matrixR[4][4];

	matrixR[0][0] = matrixB[0][0]*matrixC[0][0] + matrixB[0][1]*matrixC[1][0] + matrixB[0][2]*matrixC[2][0];
	matrixR[0][1] = matrixB[0][0]*matrixC[0][1] + matrixB[0][1]*matrixC[1][1] + matrixB[0][2]*matrixC[2][1];
	matrixR[0][2] = matrixB[0][0]*matrixC[0][2] + matrixB[0][1]*matrixC[1][2] + matrixB[0][2]*matrixC[2][2];
	matrixR[1][0] = matrixB[1][0]*matrixC[0][0] + matrixB[1][1]*matrixC[1][0] + matrixB[1][2]*matrixC[2][0];
	matrixR[1][1] = matrixB[1][0]*matrixC[0][1] + matrixB[1][1]*matrixC[1][1] + matrixB[1][2]*matrixC[2][1];
	matrixR[1][2] = matrixB[1][0]*matrixC[0][2] + matrixB[1][1]*matrixC[1][2] + matrixB[1][2]*matrixC[2][2];
	matrixR[2][0] = matrixB[2][0]*matrixC[0][0] + matrixB[2][1]*matrixC[1][0] + matrixB[2][2]*matrixC[2][0];
	matrixR[2][1] = matrixB[2][0]*matrixC[0][1] + matrixB[2][1]*matrixC[1][1] + matrixB[2][2]*matrixC[2][1];
	matrixR[2][2] = matrixB[2][0]*matrixC[0][2] + matrixB[2][1]*matrixC[1][2] + matrixB[2][2]*matrixC[2][2];
	matrixR[0][3] = matrixR[1][3] = matrixR[2][3] = matrixR[3][0] = matrixR[3][1] = matrixR[3][2] = 0.0;
	matrixR[3][3] = 1.0;

	const int memsize = sizeof(matrixA); // [#2] move sizeof outside the call for avoiding warning.
	memcpy( matrixA, matrixR, memsize );

	return TRUE;
}

Bool MagellanCheckMotionEvent(Display* display, XEvent* event, char* arg)
{
	return ((event->type==ClientMessage)&&(event->xclient.message_type==(Atom)arg));
}

int MagellanErrorHandler(Display* display, XErrorEvent* event)
{
	char buffer[128];
	switch(event->error_code) {
	case BadWindow:
		break;
	default:
		XGetErrorText(display, event->error_code, buffer, 128*sizeof(char));
		fprintf(stderr, "Magellan: Error = %s.\n", buffer);
		break;
	}
	return 0;
}

int MagellanRemoveMotionEvents(Display* display)
{
	XEvent event;

	while (XCheckIfEvent(display,&event,MagellanCheckMotionEvent,(char*)MagellanMotionEvent) == True ) {
	}

	return true;
}

#ifdef __cplusplus
}
#endif

