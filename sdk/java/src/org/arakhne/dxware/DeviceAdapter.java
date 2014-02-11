/* 
 * $Id$
 * 
 * Copyright (C) 2008 St&eacute;phane GALLAND
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * This program is free software; you can redistribute it and/or modify
 */
package org.arakhne.dxware;

/**
 * Describe an event listener on a 3D device.
 * 
 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 * @version $Name$ $Revision$ $Date$
 */
public class DeviceAdapter implements DeviceListener {

	/** 3D Mouse has moved.
	 * 
	 * @param event
	 */
	public void onDeviceMotion(DeviceEvent event) {
		//
	}
	
	/** 3D mouse button was pressed.
	 * 
	 * @param event
	 */
	public void onDeviceButtonPressed(DeviceEvent event) {
		//
	}

	/** 3D mouse button was released.
	 * 
	 * @param event
	 */
	public void onDeviceButtonReleased(DeviceEvent event) {
		//
	}

	/** Keyboard key was pressed.
	 * 
	 * @param event
	 */
	public void onKeyPressed(DeviceEvent event) {
		//
	}

	/** Keyboard key was released.
	 * 
	 * @param event
	 */
	public void onKeyReleased(DeviceEvent event) {
		//
	}

}
