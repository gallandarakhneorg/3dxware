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


/** List of types of events forwarded by the 3D device driver.
*
 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 * @version $Name$ $Revision$ $Date$
*/
public enum EventType {
	/** No event.
	 */
	NO_EVENT3D,
	/** A keyboard key was pressed.
	 */
	KEY_PRESSED,
	/** A keyboard key was released.
	 */
	KEY_RELEASED,
	/** The 3D device has motion.
	 */
	MOUSE3D_MOTION,
	/** A button on the 3D device was pressed.
	 */
	BUTTON3D_PRESSED,
	/** A button on the 3D device was released.
	 */
	BUTTON3D_RELEASED
}
