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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef USE_X11_BINDING
#  include <jni.h>
#else
#  include <jawt_md.h>
#endif

#include "3dxware/debug.h"
#include "3dxware/3dxException.h"
#include "JNIBinder.h"

#define MAX_PROPERTY_VALUE_LEN 4096

#if defined(__LINUX__) || defined(LINUX)
namespace dxwarejni {

#ifdef USE_X11_BINDING

static char* getProperty(Display* disp, Window win, Atom xa_prop_type, char* prop_name, unsigned long *size) {
    Atom xa_prop_name;
    Atom xa_ret_type;
    int ret_format;
    unsigned long ret_nitems;
    unsigned long ret_bytes_after;
    unsigned long tmp_size;
    unsigned char *ret_prop;
    char *ret;
    
    xa_prop_name = XInternAtom(disp, prop_name, False);
    
    // MAX_PROPERTY_VALUE_LEN / 4 explanation (XGetWindowProperty manpage):
    //
    // long_length = Specifies the length in 32-bit multiples of the
    //               data to be retrieved.
    if (XGetWindowProperty(disp, win, xa_prop_name, 0, MAX_PROPERTY_VALUE_LEN / 4, False,
            xa_prop_type, &xa_ret_type, &ret_format,     
            &ret_nitems, &ret_bytes_after, &ret_prop) != Success) {
        dbg1("Cannot get %s property.", prop_name);
        return NULL;
    }
  
    if (xa_ret_type != xa_prop_type) {
        dbg1("Invalid type of %s property.", prop_name);
        XFree(ret_prop);
        return NULL;
    }

    // null terminate the result to make string handling easier
    tmp_size = (ret_format / 8) * ret_nitems;
    ret = (char*)malloc(tmp_size + 1);
    memcpy(ret, ret_prop, tmp_size);
    ret[tmp_size] = '\0';

    if (size) {
        *size = tmp_size;
    }
    
    XFree(ret_prop);
    return ret;
}

static Window* getClientList(Display* display, unsigned long* size) {
	Window* list;
	if ((list = (Window*)getProperty(display, DefaultRootWindow(display), 
		    XA_WINDOW, (char*)"_NET_CLIENT_LIST", size)) == NULL) {
		if ((list = (Window*)getProperty(display, DefaultRootWindow(display), 
				XA_CARDINAL, (char*)"_WIN_CLIENT_LIST", size)) == NULL) {
		    return NULL;
		}
	}
	return list;
}

static char* getWindowClass(Display* display, Window window) {
    char* wm_class;
    unsigned long size;

    wm_class = getProperty(display, window, XA_STRING, (char*)"WM_CLASS", &size);
    if (wm_class) {
        char* p_0 = strchr(wm_class, '\0');
        if (wm_class + size - 1 > p_0) {
            *(p_0) = '.';
        }
    }
    
    return wm_class;
}

static const char CLASSNAME_PREFIX_DIALOG[] = "sun-awt-X11-XDialogPeer.";
static const char CLASSNAME_PREFIX_FRAME[] = "sun-awt-X11-XFramePeer.";

static void bindX11(dxware::Driver* driver, const char* name, const char* title, const char* typeName, PeerComponentType type)
{
	Display* display = XOpenDisplay(NULL);

	if (display==NULL) {
		throw dxware::DeviceException("unable to get Xlib resources", __FILE__, __LINE__);
	}

	// Build the class of the Xlib window
	// "sun-awt-X11-XDialogPeer.<type>"
	// "sun-awt-X11-XFramePeer.<type>"
	// "<type>" should be a java class name in which the points are replaced by tirets
	char* className;
	unsigned long prefixLength;
	switch(type) {
	case PEER_FRAME:
		prefixLength = strlen(CLASSNAME_PREFIX_FRAME);
		className = (char*)malloc(prefixLength+strlen(typeName)+1);
		strncpy(className, CLASSNAME_PREFIX_DIALOG, prefixLength);
		break;
	case PEER_DIALOG:
		prefixLength = strlen(CLASSNAME_PREFIX_DIALOG);
		className = (char*)malloc(prefixLength+strlen(typeName)+1);
		strncpy(className, CLASSNAME_PREFIX_DIALOG, prefixLength);
		break;
	default:
		throw dxware::DeviceException("unsupported type of peer component", __FILE__, __LINE__);
	}
	strcpy(className+prefixLength,typeName);
	for(unsigned int i=prefixLength; className[i]!='\0'; i++) {
		if (className[i]=='.') {
			className[i] = '-';
		}
	}
	dbg1("WM_CLASS=%s", className);

	Window peerComponent = 0;

	unsigned long clientCount;
	Window* clientList = getClientList(display, &clientCount);
	if (clientList!=NULL) {

		for(unsigned int i=0; (i<clientCount)&&(peerComponent==0); i++) {
			char* xType = getWindowClass(display, clientList[i]);
			if (xType!=NULL) {
				if (strcmp(className,xType)==0) {
					peerComponent = clientList[i];
				}
				XFree(xType);
			}			
		}

		XFree(clientList);
	}

	XFree(className);

	if (peerComponent==0) {
		throw dxware::DeviceException("unable to retreive the peer Xlib component", __FILE__, __LINE__);
	}

	dbg2("bind to [0x%lX::0x%lX] with X11", (unsigned long)display, (unsigned long)peerComponent);

	driver->setDriverResourceAt(XDRIVER_RESOURCE_DISPLAY, display);
	driver->setDriverResourceAt(XDRIVER_RESOURCE_WINDOW, &peerComponent);
}

#else // USE_X11_BINDING

static void bindJAWT(JNIEnv* env, jobject jcomponent, dxware::Driver* driver)
{
	JAWT awt;
	jboolean result;

	// Get the AWT
	awt.version = JAWT_VERSION_1_4;
	result = JAWT_GetAWT(env, &awt);
	if (result!=JNI_FALSE) {
		JAWT_DrawingSurface* ds;

		// Get the drawing surface
		ds = awt.GetDrawingSurface(env, jcomponent);
		if (ds!=NULL) {
			jint lock;

			// Lock the drawing surface
			lock = ds->Lock(ds);
			if ((lock & JAWT_LOCK_ERROR) == 0) {
				JAWT_DrawingSurfaceInfo* dsi;
				JAWT_X11DrawingSurfaceInfo* dsi_x11;

				// Get the drawing surface info
				dsi = ds->GetDrawingSurfaceInfo(ds);
				// Get the platform-specific drawing info
				dsi_x11 = (JAWT_X11DrawingSurfaceInfo*)dsi->platformInfo;

				// We obtain the windon information
				Display* display = dsi_x11->display;
				Drawable drawable = dsi_x11->drawable;
				dbg2("set Xlib resources to [0x%lX::0x%lX] with JAWT", (unsigned long)display, (unsigned long)drawable);
				driver->setDriverResourceAt(XDRIVER_RESOURCE_DISPLAY, display);
				driver->setDriverResourceAt(XDRIVER_RESOURCE_WINDOW, &drawable);

				// Free the drawing surface info
				ds->FreeDrawingSurfaceInfo(dsi);

				// Unlock the drawing surface
				ds->Unlock(ds);
			}
			else {
				// Free the drawing surface
				awt.FreeDrawingSurface(ds);
				throw dxware::DeviceException("Cannot lock the JAWT drawing surface", __FILE__, __LINE__);
			}

			// Free the drawing surface
			awt.FreeDrawingSurface(ds);
		}
		else {
			throw dxware::DeviceException("Cannot get the JAWT drawing surface", __FILE__, __LINE__);
		}
	}
	else {
		throw dxware::DeviceException("Cannot get the JAWT layer", __FILE__, __LINE__);
	}
}

#endif //USE_X11_BINDING

void bind(JNIEnv* env, jobject jcomponent, dxware::Driver* driver, const char* name, const char* title, const char* typeName, PeerComponentType type)
{
#ifdef USE_X11_BINDING
	bindX11(driver, name, title, typeName, type);
#else
	bindJAWT(env, jcomponent, driver);
#endif
}

};

#endif

