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


/** List of supported modifier keys by the 3DxWare C++ driver.
*
 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 * @version $Name$ $Revision$ $Date$
*/
public enum ModifierKey {

	/** Left Shift */
	KEY_LEFT_SHIFT(0x0001),
	/** Right Shift */
	KEY_RIGHT_SHIFT(0x0002),
	/** Left Control */
	KEY_LEFT_CONTROL(0x0004),
	/** Right Control */
	KEY_RIGHT_CONTROL(0x0008),
	/** Caps lock */
	KEY_CAPS_LOCK(0x0010),
	/** Shift lock */
	KEY_SHIFT_LOCK(0x0020),
	/** Left Meta */
	KEY_LEFT_META(0x0040),
	/** Right Meta */
	KEY_RIGHT_META(0x0080),
	/** Left Alt */
	KEY_LEFT_ALT(0x00100),
	/** Right Alt */
	KEY_RIGHT_ALT(0x0200),
	/** Alt Gr */
	KEY_ALT_GR(0x0400),
	/** Left Super */
	KEY_LEFT_SUPER(0x0800),
	/** Right Super */
	KEY_RIGHT_SUPER(0x1000),
	/** Left Hyper */
	KEY_LEFT_HYPER(0x2000),
	/** Right Hyper */
	KEY_RIGHT_HYPER(0x4000);
	
	private final int mask;
	
	private ModifierKey(int c) {
		this.mask = c;
	}

	/** Replies the numerical value usable in a bitfield.
	 * 
	 * @return a numerical value usable in a bitfield.
	 */
	public int getBitValue() {
		return this.mask;
	}
	
	/** Add the bitfield mask of this ModifierKey to the given modifier bitfield.
	 * 
	 * @param modifiers is the bitfield of modifier keys.
	 * @return the modified bitfield
	 */
	public int add(int modifiers) {
		return modifiers | this.mask;
	}
	
	/** Replies if this modifier key is set in the given bitfield.
	 * 
	 * @param bitfield is the lsit of modifier keys to test.
	 * @return <code>true</code> if this modifier key is appearing in the given bitfield,
	 * otherwise <code>false</code>
	 */
	public boolean isModifierSet(int bitfield) {
		return (bitfield & this.mask) != 0;
	}

	/** Remove the bitfield mask of this ModifierKey from the given modifier bitfield.
	 * 
	 * @param modifiers is the bitfield of modifier keys.
	 * @return the modified bitfield
	 */
	public int remove(int modifiers) {
		return modifiers & (~this.mask);
	}

	/** Replies if the given list of modifiers contains a Ctrl key.
	 *
	 * @param modifiers is the list of modifier keys to test.
	 * @return <code>true</code> if a Ctrl key is inside the given modifiers, otherwise <code>false</code>.
	 */
	public boolean isCtrlModifierKey(int modifiers) {
		return (modifiers & (KEY_LEFT_CONTROL.mask|KEY_RIGHT_CONTROL.mask)) != 0;
	}

	/** Replies if the given list of modifiers contains a Shift key.
	 *
	 * @param modifiers is the list of modifier keys to test.
	 * @return <code>true</code> if a Shift key is inside the given modifiers, otherwise <code>false</code>.
	 */
	public boolean isShiftModifierKey(int modifiers) {
		return (modifiers & (KEY_LEFT_SHIFT.mask|KEY_RIGHT_SHIFT.mask)) != 0;
	}

	/** Replies if the given list of modifiers contains a Meta key.
	 *
	 * @param modifiers is the list of modifier keys to test.
	 * @return <code>true</code> if a Meta key is inside the given modifiers, otherwise <code>false</code>.
	 */
	public boolean isMetaModifierKey(int modifiers) {
		return (modifiers & (KEY_LEFT_META.mask|KEY_RIGHT_META.mask)) != 0;
	}

	/** Replies if the given list of modifiers contains an Alt key.
	 *
	 * @param modifiers is the list of modifier keys to test.
	 * @return <code>true</code> if an Alt key is inside the given modifiers, otherwise <code>false</code>.
	 */
	public boolean isAltModifierKey(int modifiers) {
		return (modifiers & (KEY_LEFT_ALT.mask|KEY_RIGHT_ALT.mask|KEY_ALT_GR.mask)) != 0;
	}

	/** Replies if the given list of modifiers contains a Super key.
	 *
	 * @param modifiers is the list of modifier keys to test.
	 * @return <code>true</code> if a Super key is inside the given modifiers, otherwise <code>false</code>.
	 */
	public boolean isSuperModifierKey(int modifiers) {
		return (modifiers & (KEY_LEFT_SUPER.mask|KEY_RIGHT_SUPER.mask)) != 0;
	}

	/** Replies if the given list of modifiers contains a Hyper key.
	 *
	 * @param modifiers is the list of modifier keys to test.
	 * @return <code>true</code> if a Hyper key is inside the given modifiers, otherwise <code>false</code>.
	 */
	public boolean isHyperModifierKey(int modifiers) {
		return (modifiers & (KEY_LEFT_HYPER.mask|KEY_RIGHT_HYPER.mask)) != 0;
	}

	/** Replies if the given list of modifiers contains a Lock key.
	 *
	 * @param modifiers is the list of modifier keys to test.
	 * @return <code>true</code> if a Lock key is inside the given modifiers, otherwise <code>false</code>.
	 */
	public boolean isLockModifierKey(int modifiers) {
		return (modifiers & (KEY_CAPS_LOCK.mask|KEY_SHIFT_LOCK.mask)) != 0;
	}
	
	/** Replies a string representation of the given modifier field.
	 * 
	 * @param bitfield is the list of modifiers to display.
	 * @return a string representation
	 */
	public static String toString(int bitfield) {
		StringBuffer buffer = new StringBuffer();
		for(ModifierKey k : ModifierKey.values()) {
			if (k.isModifierSet(bitfield)) {
				if (buffer.length()>0) {
					buffer.append('|');
				}
				buffer.append(k.name());
			}
		}
		return buffer.toString();
	}

}
