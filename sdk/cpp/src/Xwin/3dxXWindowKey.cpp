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

#include <3dxware/Xwin/3dxXWindowKey.h>
#include <3dxware/3dxKey.h>

namespace dxware {

static unsigned long modifierMap[] = {
	KEY_LEFT_SHIFT,			XK_Shift_L,
	KEY_RIGHT_SHIFT,		XK_Shift_R,
	KEY_LEFT_CONTROL,		XK_Control_L,
	KEY_RIGHT_CONTROL,		XK_Control_R,
	KEY_CAPS_LOCK,			XK_Caps_Lock,
	KEY_SHIFT_LOCK,			XK_Shift_Lock,
	KEY_LEFT_META,			XK_Meta_L,
	KEY_RIGHT_META,			XK_Meta_R,
	KEY_LEFT_ALT,			XK_Alt_L,
	KEY_RIGHT_ALT,			XK_Alt_R,
	KEY_ALT_GR,			XK_ISO_Level3_Shift,
	KEY_LEFT_SUPER,			XK_Super_L,
	KEY_RIGHT_SUPER,		XK_Super_R,
	KEY_LEFT_HYPER,			XK_Hyper_L,
	KEY_RIGHT_HYPER,		XK_Hyper_R,
	0
};

static unsigned long keyMap[] = {
	KEY_VOID,			XK_VoidSymbol,
	KEY_BACKSPACE,			XK_BackSpace,
	KEY_SPACE,			XK_space,
	KEY_TAB,			XK_Tab,
	KEY_LINEFEED,			XK_Linefeed,
	KEY_RETURN,			XK_Return,
	KEY_ESC,			XK_Escape,
	KEY_0,				XK_0,
	KEY_1,				XK_1,
	KEY_2,				XK_2,
	KEY_3,				XK_3,
	KEY_4,				XK_4,
	KEY_5,				XK_5,
	KEY_6,				XK_6,
	KEY_7,				XK_7,
	KEY_8,				XK_8,
	KEY_9,				XK_9,
	KEY_a,				XK_a,
	KEY_b,				XK_b,
	KEY_c,				XK_c,
	KEY_d,				XK_d,
	KEY_e,				XK_e,
	KEY_f,				XK_f,
	KEY_g,				XK_g,
	KEY_h,				XK_h,
	KEY_i,				XK_i,
	KEY_j,				XK_j,
	KEY_k,				XK_k,
	KEY_l,				XK_l,
	KEY_m,				XK_m,
	KEY_n,				XK_n,
	KEY_o,				XK_o,
	KEY_p,				XK_p,
	KEY_q,				XK_q,
	KEY_r,				XK_r,
	KEY_s,				XK_s,
	KEY_t,				XK_t,
	KEY_u,				XK_u,
	KEY_v,				XK_v,
	KEY_w,				XK_w,
	KEY_x,				XK_x,
	KEY_y,				XK_y,
	KEY_z,				XK_z,
	KEY_A,				XK_A,
	KEY_B,				XK_B,
	KEY_C,				XK_C,
	KEY_D,				XK_D,
	KEY_E,				XK_E,
	KEY_F,				XK_F,
	KEY_G,				XK_G,
	KEY_H,				XK_H,
	KEY_I,				XK_I,
	KEY_J,				XK_J,
	KEY_K,				XK_K,
	KEY_L,				XK_L,
	KEY_M,				XK_M,
	KEY_N,				XK_N,
	KEY_O,				XK_O,
	KEY_P,				XK_P,
	KEY_Q,				XK_Q,
	KEY_R,				XK_R,
	KEY_S,				XK_S,
	KEY_T,				XK_T,
	KEY_U,				XK_U,
	KEY_V,				XK_V,
	KEY_W,				XK_W,
	KEY_X,				XK_X,
	KEY_Y,				XK_Y,
	KEY_Z,				XK_Z,
	KEY_LESS,			XK_less,
	KEY_GREATER,			XK_greater,
	KEY_AMPERSAND,			XK_ampersand,
	KEY_TILDE,			XK_asciitilde,
	KEY_DOUBLE_QUOTE,		XK_quotedbl,
	KEY_QUOTE,			XK_apostrophe,
	KEY_LEFT_BRACE,			XK_braceleft,
	KEY_RIGHT_BRACE,		XK_braceright,
	KEY_LEFT_PARENTHESIS,		XK_parenleft,
	KEY_RIGHT_PARENTHESIS,		XK_parenright,
	KEY_LEFT_BRAQUET,		XK_bracketleft,
	KEY_RIGHT_BRAQUET,		XK_bracketright,
	KEY_MINUS,			XK_minus,
	KEY_PIPE,			XK_bar,
	KEY_BACKQUOTE,			XK_grave,
	KEY_UNDERSCORE,			XK_underscore,
	KEY_BACKSLASH,			XK_backslash,
	KEY_CIRCUMFLEX,			XK_asciicircum,
	KEY_AT,				XK_at,
	KEY_EQUAL,			XK_equal,
	KEY_PLUS,			XK_plus,
	KEY_DOLLAR,			XK_dollar,
	KEY_PERCENT,			XK_percent,
	KEY_STAR,			XK_asterisk,
	KEY_QUESTION,			XK_question,
	KEY_COMMA,			XK_comma,
	KEY_POINT,			XK_period,
	KEY_SEMICOLUMN,			XK_semicolon,
	KEY_SLASH,			XK_slash,
	KEY_COLUMN,			XK_colon,
	KEY_EXCLAMATION,		XK_exclam,
	KEY_CLEAR,			XK_Clear,
	KEY_PAUSE,			XK_Pause,
	KEY_SCROLLLOCK,			XK_Scroll_Lock,
	KEY_SYSREQ,			XK_Sys_Req,
	KEY_DELETE,			XK_Delete,
	KEY_HOME,			XK_Home,
	KEY_LEFT,			XK_Left,
	KEY_UP,				XK_Up,
	KEY_RIGHT,			XK_Right,
	KEY_DOWN,			XK_Down,
	KEY_PAGE_DOWN,			XK_Page_Down,
	KEY_PAGE_UP,			XK_Page_Up,
	KEY_END,			XK_End,
	KEY_BEGIN,			XK_Begin,
	KEY_PAD_ADD,			XK_KP_Add,
	KEY_PAD_SUB,			XK_KP_Subtract,
	KEY_PAD_DIV,			XK_KP_Divide,
	KEY_PAD_MUL,			XK_KP_Multiply,
	KEY_PAD_EQUAL,			XK_KP_Equal,
	KEY_PAD_ENTER,			XK_KP_Enter,
	KEY_PAD_DECIMAL,		XK_KP_Decimal,
	KEY_PAD_0,			XK_KP_0,
	KEY_PAD_1,			XK_KP_1,
	KEY_PAD_2,			XK_KP_2,
	KEY_PAD_3,			XK_KP_3,
	KEY_PAD_4,			XK_KP_4,
	KEY_PAD_5,			XK_KP_5,
	KEY_PAD_6,			XK_KP_6,
	KEY_PAD_7,			XK_KP_7,
	KEY_PAD_8,			XK_KP_8,
	KEY_PAD_9,			XK_KP_9,
	KEY_F1,				XK_F1,
	KEY_F2,				XK_F2,
	KEY_F3,				XK_F3,
	KEY_F4,				XK_F4,
	KEY_F5,				XK_F5,
	KEY_F6,				XK_F6,
	KEY_F7,				XK_F7,
	KEY_F8,				XK_F8,
	KEY_F9,				XK_F9,
	KEY_F10,			XK_F10,
	KEY_F11,			XK_F11,
	KEY_F12,			XK_F12,
	(unsigned long)-1
};

static unsigned long keyMapSize = 0;
static unsigned long modifierMapSize = 0;
static bool mapsAreSorted = false;

static void sortMapByValues(unsigned long* content, unsigned long size)
{
	unsigned long val, key, tmp;
	const unsigned long _2size = 2 * size;
	for(unsigned long i=0; i<_2size-2; i+=2) {
		key = content[i];
		val = content[i+1];

		for(unsigned long j=i+2; j<_2size; j+=2) {

			if (val>content[j+1]) {
				// Swap key
				tmp = key;
				content[i] = content[j];
				content[j] = tmp;

				// Swap value
				tmp = val;
				content[i+1] = content[j+1];
				content[j+1] = tmp;
			}

		}
	}
}

static void ensureSortedMaps()
{
	if (!mapsAreSorted) {
		modifierMapSize = 0;
		while (modifierMap[modifierMapSize]!=0) {
			modifierMapSize += 2;
		}
		modifierMapSize /= 2;

		sortMapByValues(modifierMap, modifierMapSize);

		keyMapSize = 0;
		while (keyMap[keyMapSize]!=(unsigned long)-1) {
			keyMapSize += 2;
		}
		keyMapSize /= 2;

		sortMapByValues(keyMap, keyMapSize);

		mapsAreSorted = true;
	}
}

bool XWindowKeyManager::isModifierKey(const KeySym& xKey)
{
	unsigned long a = 0;
	unsigned long b = modifierMapSize - 1;
	unsigned long c = (a+b)/2;
	unsigned long k;
		
	while (a<=b) {

		k = modifierMap[c*2+1];

		if (k<xKey) {
			a = c+1;
			c = (a+b)/2;
		}
		else if (k>xKey) {
			b = c-1;
			c = (a+b)/2;
		}
		else {
			return true;
		}

	}

	return false;
}

ModifierKey XWindowKeyManager::toModifier(const KeySym& xKey)
{
	unsigned long a = 0;
	unsigned long b = modifierMapSize - 1;
	unsigned long c = (a+b)/2;
	unsigned long k;
		
	while (a<=b) {

		k = modifierMap[c*2+1];

		if (k<xKey) {
			a = c+1;
			c = (a+b)/2;
		}
		else if (k>xKey) {
			b = c-1;
			c = (a+b)/2;
		}
		else {
			return (ModifierKey)modifierMap[c*2];
		}

	}

	return (ModifierKey)0;
}

EventKey XWindowKeyManager::toKey(const KeySym& xKey)
{
	unsigned long a = 0;
	unsigned long b = keyMapSize - 1;
	unsigned long c = (a+b)/2;
	unsigned long k;
		
	while (a<=b) {

		k = keyMap[c*2+1];

		if (k<xKey) {
			a = c+1;
			c = (a+b)/2;
		}
		else if (k>xKey) {
			b = c-1;
			c = (a+b)/2;
		}
		else {
			return (EventKey)keyMap[c*2];
		}

	}

	return KEY_VOID;
}

XWindowKeyManager::XWindowKeyManager(): lastKey(KEY_VOID), modifiers(0), hasNewKeyValue(false)
{
	ensureSortedMaps();
}

XWindowKeyManager::XWindowKeyManager(const XWindowKeyManager& manager): lastKey(manager.lastKey), modifiers(manager.modifiers), hasNewKeyValue(manager.hasNewKeyValue)
{
	ensureSortedMaps();
}

XWindowKeyManager::~XWindowKeyManager()
{
}

XWindowKeyManager& XWindowKeyManager::operator=(const XWindowKeyManager& manager)
{
	lastKey = manager.lastKey;
	modifiers = manager.modifiers;
	hasNewKeyValue = manager.hasNewKeyValue;
	return *this;
}

XWindowKeyManager& XWindowKeyManager::operator+=(const KeySym& xKey)
{
	if (isModifierKey(xKey)) {
		modifiers = modifiers | toModifier(xKey);
		hasNewKeyValue = false;
	}
	else {
		lastKey = toKey(xKey);
		hasNewKeyValue = true;
	}	
	return *this;
}

XWindowKeyManager& XWindowKeyManager::operator-=(const KeySym& xKey)
{
	if (isModifierKey(xKey)) {
		modifiers = modifiers & (~toModifier(xKey));
		hasNewKeyValue = false;
	}
	else {
		lastKey = toKey(xKey);
		hasNewKeyValue = true;
	}	
	return *this;
}

XWindowKeyManager::operator EventKey() const
{
	return lastKey;
}

XWindowKeyManager::operator ModifierKeyField() const
{
	return modifiers;
}

bool XWindowKeyManager::isVoid() const
{
	return lastKey==KEY_VOID;
}

bool XWindowKeyManager::hasNewKey() const
{
	return hasNewKeyValue;
}

} // namespace dxware
