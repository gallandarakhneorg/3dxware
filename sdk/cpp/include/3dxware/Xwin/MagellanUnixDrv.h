/*
 * Copyright (c) 2008-2010 Stéphane GALLAND <galland@arakhne.org>
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
#ifndef __MAGELLAN_UNIX_DRV_H__
#  define __MAGELLAN_UNIX_DRV_H__

#  include <3dxware/3dxDriver.h>

#  ifndef TRUE
#    define TRUE	(1==1)
#  endif

#  ifndef FALSE
#    define FALSE	(1==0)
#  endif

#define XHigh32(__value__)        (((__v__)>>16)&0x0000FFFF)
#define XLow32(__value__)         ((__v__)&0x0000FFFF)

//
// Data Structure for CADDS5 implementation
//
#define MagellanInputMotionEvent ((int)dxware::MAGELLAN_INPUT_MOTION_EVENT)
#define MagellanInputButtonPressEvent ((int)dxware::MAGELLAN_INPUT_BUTTON_PRESS_EVENT)
#define MagellanInputButtonReleaseEvent ((int)dxware::MAGELLAN_INPUT_BUTTON_RELEASE_EVENT)

#  ifdef __cplusplus
extern "C" {
#  endif

union _MagellanInputEventUnion_
{
	int data[7];
	int button;
};
typedef union _MagellanInputEventUnion_ MagellanIntUnion;

struct _MagellanIntEvent_
{
	int type;
	MagellanIntUnion u;
};
typedef struct _MagellanIntEvent_ MagellanIntEvent;

//
// Data Structure for Pro/ENGINEER implementation
//
enum _MagellanData_
{
	MagellanX = dxware::COORD_X,
	MagellanY = dxware::COORD_Y,
	MagellanZ = dxware::COORD_Z,
	MagellanA = dxware::COORD_A,
	MagellanB = dxware::COORD_B,
	MagellanC = dxware::COORD_C
};

struct _MagellanFloatEvent_
{
	int MagellanType;
	int MagellanButton;
	double MagellanData[6];
	int MagellanPeriod;
};
typedef struct _MagellanFloatEvent_ MagellanFloatEvent;


union _MagellanTypeConversion_
{
	float Float;
	short Short[ 2 ];
};
typedef union _MagellanTypeConversion_ MagellanTypeConversion;

enum _CommandMessages_
{
	NoCommandMessage = 0,
  	CommandMessageApplicationWindow = dxware::MAGELLAN_COMMAND_APPLICATION_WINDOW, 
	CommandMessageApplicationSensitivity = dxware::MAGELLAN_COMMAND_SENSITIVITY
};

extern Atom MagellanMotionEvent;
extern Atom MagellanButtonPressEvent;
extern Atom MagellanReleaseEvent;
extern Window MagellanWindow;
extern int MagellanExist;

/** Initialize the connexion to the Magellan driver.
 * \param display is the X11 display in which the Magellan driver is.
 * \param window is the X11 window to connect to Magellan.
 * \return TRUE on success, otherwise FALSE
 */
int MagellanInit(Display* display, Window window);

/** Send the client window to the Magellan driver
 * \param display is the X11 display in which the Magellan driver is.
 * \param window is the X11 window to connect to Magellan.
 * \return TRUE on success, otherwise FALSE
 */
int MagellanSetWindow(Display* display, Window window);

/** Set the mouse sensitivity.
 * \param display is the X11 display in which the Magellan driver is.
 * \param sensitivity is the new value of the sensitivity.
 * \return TRUE on success, otherwise FALSE
 */
int MagellanApplicationSensitivity(Display* display, double sensitivity);

/** Wait for an event.
 * \param display is the X11 display in which the Magellan driver is.
 * \param event is X11 event receive and that should be translated into a Magellan event.
 * \param magellanEvent is the description of the Magellan event.
 * \return TRUE on success, otherwise FALSE
 */
int MagellanInputEvent(Display* display, XEvent* event, MagellanIntEvent* magellanEvent);

/** Translate a X11 event into a Magellan event
 * \param display is the X11 display in which the Magellan driver is.
 * \param event is X11 event receive and that should be translated into a Magellan event.
 * \param magellanEvent is the description of the Magellan event.
 * \param magellanTranslationScale is the scaling factor that will be applied to the translations.
 * \param magellanRotationScale is the scaling factor that will be applied to the rotations.
 * \return the type of the event or 0
 */
int MagellanTranslateEvent(Display* display, XEvent* event, MagellanFloatEvent* magellanEvent, double magellanTranslationScale, double magellanRotationScale);

/** Close connexion to the Magellan driver.
 * \param display is the X11 display in which the Magellan driver is.
 * \return TRUE on success, otherwise FALSE
 */
int MagellanClose(Display* display);

/** Replies the rotation matrix that corresponds to the given rotations factors replied by the Magellan driver.
 * \param rotate is the matrix to fill
 * \param c is the C rotation from Magellan driver.
 * \param b is the C rotation from Magellan driver.
 * \param a is the C rotation from Magellan driver.
 * \return TRUE on success, otherwise FALSE
 */
int MagellanRotationMatrix(double rotate[4][4], double c, double b, double a);

/** Multiply matrix A and B and put the result in C.
 * \param matrixA
 * \param matrixB
 * \param matrixC
 * \return TRUE on success, otherwise FALSE
 */
int MagellanMultiplicationMatrix(double matrixA[4][4], double matrixB[4][4], double matrixC[4][4]);

Bool MagellanCheckMotionEvent(Display* display, XEvent* event, char* arg);

int MagellanErrorHandler(Display* display, XErrorEvent* error);

int MagellanRemoveMotionEvents(Display* display);

#  ifdef __cplusplus
}
#  endif

#endif  /* __MAGELLAN_UNIX_DRV_H__ */
