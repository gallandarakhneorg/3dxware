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

import java.util.EventObject;

/**
 * Describe an event in a 3D device.
 * 
 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 * @version $Name$ $Revision$ $Date$
 */
public class DeviceEvent extends EventObject {

	private static final long serialVersionUID = 5988133832278960222L;

	/**
	 * Type of event
	 */
	private EventType type = EventType.NO_EVENT3D;
	
	/** Key embedded in this event.
	 */
	private EventKey key = EventKey.KEY_VOID;
	
	/** Modifier keys.
	 */
	private int modifiers = 0;
	
	/** 3D Mouse button.
	 */
	private byte button = -1;
	
	/** X translation coordinate.
	 */
	private float x = 0f;
	
	/** Y translation coordinate.
	 */
	private float y = 0f;

	/** Z translation coordinate.
	 */
	private float z = 0f;

	/** A rotation amount.
	 */
	private float a = 0f;

	/** B rotation amount.
	 */
	private float b = 0f;

	/** C rotation amount.
	 */
	private float c = 0f;

	/**
	 * @param source is the source of the event.
	 */
	public DeviceEvent(SpaceMouse source) {
		super(source);
	}

	/** Replies the type of the event.
	 * 
	 * @return the type of the event.
	 */
	public EventType getType() {
		return this.type;
	}
	
	/** Replies  the pressed/released key.
	 * 
	 * @return the key embedded in this event.
	 */
	public EventKey getKey() {
		return this.key;
	}
	
	/** Replies the list of keyboard modifiers.
	 * 
	 * @return the modifier keys embedded in this event.
	 */
	public int getKeyModifiers() {
		return this.modifiers;
	}
	
	/** Replies 3d device button embedded in this event.
	 * 
	 * @return the index of the 3D mouse button.
	 */
	public byte getButton() {
		return this.button;
	}
	
	/** Replies the coordinate at the specified index.
	 *
	 * @param index is the index of the coordinate to reply
	 * @return the coordinate value
	 */
	public float getCoordinate(MagellanCoordinate index) {
		switch(index) {
		case COORD_X:
			return this.x;
		case COORD_Y:
			return this.y;
		case COORD_Z:
			return this.z;
		case COORD_A:
			return this.a;
		case COORD_B:
			return this.c;
		case COORD_C:
			return this.c;
		}
		return 0f;
	}

	/** Replies the X translation coordinate.
	 *
	 * @return x
	 */
	public float getX() {
		return this.x;
	}

	/** Replies the Y translation coordinate.
	 *
	 * @return y
	 */
	public float getY() {
		return this.y;
	}

	/** Replies the Z translation coordinate.
	 *
	 * @return z
	 */
	public float getZ() {
		return this.z;
	}

	/** Replies the A rotation amount.
	 *
	 * @return a
	 */
	public float getA() {
		return this.a;
	}

	/** Replies the B rotation amount.
	 *
	 * @return b
	 */
	public float getB() {
		return this.b;
	}

	/** Replies the C rotation amount.
	 *
	 * @return c
	 */
	public float getC() {
		return this.c;
	}

	
	/** Set the event fields.
	 * 
	 * @param typeIdx
	 * @param keyIdx
	 * @param modifiers
	 * @param button
	 * @param x
	 * @param y
	 * @param z
	 * @param a
	 * @param b
	 * @param c
	 */
	void set(int typeIdx, int keyIdx, int modifiers, byte button, float x, float y, float z, float a, float b, float c) {
		this.type = EventType.values()[typeIdx];
		this.key = EventKey.fromCIndex(keyIdx);
		this.modifiers = modifiers;
		this.button = button;
		this.x = x;
		this.y = y;
		this.z = z;
		this.a = a;
		this.b = b;
		this.c = c;
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	public String toString() {
		StringBuffer buf = new StringBuffer();
		buf.append("*** DEVICE EVENT ***\n\ttype: "); //$NON-NLS-1$
		buf.append(this.type);
		buf.append("\n\tkey: "); //$NON-NLS-1$
		buf.append(this.key);
		buf.append("\n\tmodifiers: "); //$NON-NLS-1$
		buf.append(ModifierKey.toString(this.modifiers));
		buf.append("\n\tmouse button: "); //$NON-NLS-1$
		buf.append(this.button);
		buf.append("\n\t(x,y,z): ("); //$NON-NLS-1$
		buf.append(this.x);
		buf.append(";"); //$NON-NLS-1$
		buf.append(this.y);
		buf.append(";"); //$NON-NLS-1$
		buf.append(this.z);
		buf.append(")\n\t(a,b,c): ("); //$NON-NLS-1$
		buf.append(this.a);
		buf.append(";"); //$NON-NLS-1$
		buf.append(this.b);
		buf.append(";"); //$NON-NLS-1$
		buf.append(this.c);
		buf.append(")\n"); //$NON-NLS-1$
		return buf.toString();
	}

}
