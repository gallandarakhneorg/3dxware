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
#ifndef __3DX_XWINDOW_KEY_H__
#  define __3DX_XWINDOW_KEY_H__

#  include <X11/Xlib.h>
#  include <X11/Xutil.h>
#  include <X11/keysym.h>

#  include <3dxware/3dxKey.h>

#  ifdef __cplusplus
extern "C" {
#  endif

namespace dxware {

/**
 * Key manager used on Xlib operating sytems.
 * This key manager is filtering the key events to
 * avoid modifier keys to be forward in the user-space application.
 * The modifier keys are analyzed by this manager and
 * translated as modifier flags.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
class XWindowKeyManager
{
	public:
		XWindowKeyManager();
		XWindowKeyManager(const XWindowKeyManager& manager);
		virtual ~XWindowKeyManager();

		XWindowKeyManager& operator=(const XWindowKeyManager& manager);

		/** Call this function when a KEY PRESSED event occured at
		 * Xlib level.
		 *
		 * \param xKey is the Xlib pressed key.
		 */
		XWindowKeyManager& operator+=(const KeySym& xKey);
		/** Call this function when a KEY RELEASED event occured at
		 * Xlib level.
		 *
		 * \param xKey is the Xlib released key.
		 */
		XWindowKeyManager& operator-=(const KeySym& xKey);

		/** Replies the Magellan key that corresponds to the last Xlib pressed/released
		 * key.
		 *
		 * \return the Magelland key that corresponds to the last Xlib key.
		 */
		operator EventKey() const;
		/** Replies the current modifier flags.
		 * 
		 * \return the current modifier flags.
		 */
		operator ModifierKeyField() const;

		/** Replies if a new key was registered since last call to the operators
		 * += or -=.
		 *
		 * \return <code>true</code> if a new key was registered, otherwise <code>false</code>.
		 */
		bool hasNewKey() const;
		/** Replies if a key is registered.
		 *
		 * \return <code>true</code> if a key is registered, otherwise <code>false</code>.
		 */
		bool isVoid() const;
	protected:
		/** Replies if the given Xlib key is a modifier key.
		 *
		 * \return <code>true</code> if the given Xlib key is a modifier key, otherwise <code>false</code>.
		 */
		static bool isModifierKey(const KeySym& xKey);
		/** Replies the Magellan modifier key that is corresponding to the given Xlib key.
		 *
		 * \param xKey is the Xlib key to translate.
		 * \return the Magellan modifier key for the given Xlib key.
		 */
		static ModifierKey toModifier(const KeySym& xKey);
		/** Replies the Magellan key that is corresponding to the given Xlib key.
		 *
		 * \param xKey is the Xlib key to translate.
		 * \return the Magellan key for the given Xlib key.
		 */
		static EventKey toKey(const KeySym& xKey);
	private:
		EventKey lastKey;
		ModifierKeyField modifiers;
		bool hasNewKeyValue;
};

} /* namespoace dxware */

#  ifdef __cplusplus
}
#  endif

#endif // __3DX_XWINDOW_KEY_H__

