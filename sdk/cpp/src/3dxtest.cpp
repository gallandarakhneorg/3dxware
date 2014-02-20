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

#include <stdio.h>

#include <3dxware/3dxSpaceMouse.h>
#include <3dxware/3dxCmdLine.h>
#include <3dxware/3dxException.h>

#ifdef __cplusplus
extern "C" {
#endif

int main(int argc, char** argv)
{
	try {
		dxware::saveCommandLine(argc, argv);

		dxware::SpaceMouse spaceMouse;
		bool endDemo = false;

		spaceMouse.getDriver()->setKeyEventAllowed(true);
		dxware::EventKey key = dxware::KEY_VOID;

		while (!endDemo) {
			const dxware::DeviceEvent* event = spaceMouse.nextEvent();
			if (event!=NULL) {
				switch(event->getType()) {
				case dxware::KEY_PRESSED:
					key = event->getKey();
					if (key>=32 && key<256) {
						printf("KEY PRESSED=0x%X,0x%X,'%c'\n", key,(unsigned int)event->getKeyModifiers(),(char)key);
					}
					else {
						printf("KEY PRESSED=0x%X,0x%X\n", key,(unsigned int)event->getKeyModifiers());
					}
					if (event->getKey() == dxware::KEY_ESC) {
						endDemo = true;
					}
					break;
				case dxware::KEY_RELEASED:
					if (key>=32 && key<256) {
						printf("KEY RELEASED=0x%X,0x%X,'%c'\n", key,(unsigned int)event->getKeyModifiers(),(char)key);
					}
					else {
						printf("KEY RELEASED=0x%X,0x%X\n", key,(unsigned int)event->getKeyModifiers());
					}
					break;
				case dxware::MOUSE3D_MOTION:
					printf("MOUSE MOTION(x=%f; y=%f; z=%f; a=%f; b=%f; c=%f\n",
						(float)event->getCoordinate(dxware::COORD_X),
						(float)event->getCoordinate(dxware::COORD_Y),
						(float)event->getCoordinate(dxware::COORD_Z),
						(float)event->getCoordinate(dxware::COORD_A),
						(float)event->getCoordinate(dxware::COORD_B),
						(float)event->getCoordinate(dxware::COORD_C));
					break;
				case dxware::BUTTON3D_PRESSED:
					printf("BUTTON PRESSED=%d\n", event->getButton());
					break;
				case dxware::BUTTON3D_RELEASED:
					printf("BUTTON RELEASED=%d\n", event->getButton());
					break;
				case dxware::NO_EVENT3D:
					break;
				}
			}
		}

		return 0;
	}
	catch(dxware::DeviceException e) {
		e.printf();
	}
}

#ifdef __cplusplus
}
#endif

