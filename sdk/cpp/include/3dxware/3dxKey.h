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
#ifndef __3DX_KEY_H__
#  define __3DX_KEY_H__

#  ifdef __cplusplus
namespace dxware {
#  endif

/** List of supported keys by the 3DxWare C++ driver.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
typedef enum {
	KEY_VOID		=	'\0',
	KEY_BACKSPACE		=	'\b',
	KEY_SPACE		=	' ',
	KEY_TAB			=	'\t',
	KEY_LINEFEED		=	'\r',
	KEY_RETURN		=	'\n',
	KEY_ESC			=	27,

	KEY_0 			=	'0',
	KEY_1 			=	'1',
	KEY_2			=	'2',
	KEY_3			=	'3',
	KEY_4			=	'4',
	KEY_5			=	'5',
	KEY_6			=	'6',
	KEY_7			=	'7',
	KEY_8			=	'8',
	KEY_9			=	'9',

	KEY_a			=	'a',
	KEY_b			=	'b',
	KEY_c			=	'c',
	KEY_d			=	'd',
	KEY_e			=	'e',
	KEY_f			=	'f',
	KEY_g			=	'g',
	KEY_h			=	'h',
	KEY_i			=	'i',
	KEY_j			=	'j',
	KEY_k			=	'k',
	KEY_l			=	'l',
	KEY_m			=	'm',
	KEY_n			=	'n',
	KEY_o			=	'o',
	KEY_p			=	'p',
	KEY_q			=	'q',
	KEY_r			=	'r',
	KEY_s			=	's',
	KEY_t			=	't',
	KEY_u			=	'u',
	KEY_v			=	'v',
	KEY_w			=	'w',
	KEY_x			=	'x',
	KEY_y			=	'y',
	KEY_z			=	'z',

	KEY_A			=	'A',
	KEY_B			=	'B',
	KEY_C			=	'C',
	KEY_D			=	'D',
	KEY_E			=	'E',
	KEY_F			=	'F',
	KEY_G			=	'G',
	KEY_H			=	'H',
	KEY_I			=	'I',
	KEY_J			=	'J',
	KEY_K			=	'K',
	KEY_L			=	'L',
	KEY_M			=	'M',
	KEY_N			=	'N',
	KEY_O			=	'O',
	KEY_P			=	'P',
	KEY_Q			=	'Q',
	KEY_R			=	'R',
	KEY_S			=	'S',
	KEY_T			=	'T',
	KEY_U			=	'U',
	KEY_V			=	'V',
	KEY_W			=	'W',
	KEY_X			=	'X',
	KEY_Y			=	'Y',
	KEY_Z			=	'Z',

	KEY_LESS		=	'<',
	KEY_GREATER		=	'>',
	KEY_AMPERSAND		=	'&',
	KEY_TILDE		=	'~',
	KEY_DOUBLE_QUOTE	=	'"',
	KEY_QUOTE		=	'\'',
	KEY_LEFT_BRACE		=	'{',
	KEY_RIGHT_BRACE		=	'}',
	KEY_LEFT_PARENTHESIS	=	'(',
	KEY_RIGHT_PARENTHESIS	=	')',
	KEY_LEFT_BRAQUET	=	'[',
	KEY_RIGHT_BRAQUET	=	']',
	KEY_MINUS		=	'-',
	KEY_PIPE		=	'|',
	KEY_BACKQUOTE		=	'`',
	KEY_UNDERSCORE		=	'_',
	KEY_BACKSLASH		=	'\\',
	KEY_CIRCUMFLEX		=	'^',
	KEY_AT			=	'@',
	KEY_EQUAL		=	'=',
	KEY_PLUS		=	'+',
	KEY_DOLLAR		=	'$',
	KEY_PERCENT		=	'%',
	KEY_STAR		=	'*',
	KEY_QUESTION		=	'?',
	KEY_COMMA		=	',',
	KEY_POINT		=	'.',
	KEY_SEMICOLUMN		=	';',
	KEY_SLASH		=	'/',
	KEY_COLUMN		=	':',
	KEY_EXCLAMATION		=	'!',

	KEY_CLEAR		=	0x000100,
	KEY_PAUSE,
	KEY_SCROLLLOCK,
	KEY_SYSREQ,
	KEY_DELETE,
	KEY_HOME,
	KEY_LEFT,
	KEY_UP,
	KEY_RIGHT,
	KEY_DOWN,
	KEY_PAGE_DOWN,
	KEY_PAGE_UP,
	KEY_END,
	KEY_BEGIN,

	KEY_PAD_ADD,
	KEY_PAD_SUB,
	KEY_PAD_DIV,
	KEY_PAD_MUL,
	KEY_PAD_EQUAL,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,

	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12
} EventKey;

/** List of supported modifier keys by the 3DxWare C++ driver.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
typedef enum {
	KEY_LEFT_SHIFT			=	0x0001,
	KEY_RIGHT_SHIFT			=	0x0002,
	KEY_LEFT_CONTROL		=	0x0004,
	KEY_RIGHT_CONTROL		=	0x0008,
	KEY_CAPS_LOCK			=	0x0010,
	KEY_SHIFT_LOCK			=	0x0020,
	KEY_LEFT_META			=	0x0040,
	KEY_RIGHT_META			=	0x0080,
	KEY_LEFT_ALT			=	0x0100,
	KEY_RIGHT_ALT			=	0x0200,
	KEY_ALT_GR			=	0x0400,
	KEY_LEFT_SUPER			=	0x0800,
	KEY_RIGHT_SUPER			=	0x1000,
	KEY_LEFT_HYPER			=	0x2000,
	KEY_RIGHT_HYPER			=	0x4000
} ModifierKey;

/** Bitwise list of modifier keys.
 *
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
typedef unsigned long ModifierKeyField;

/** Replies if the given list of modifiers contains a Ctrl key.
 *
 * \param modifiers is the list of modifier keys to test.
 * \return <code>true</code> if a Ctrl key is inside the given modifiers, otherwise <code>false</code>.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
inline bool isCtrlModifierKey(ModifierKeyField modifiers)
{
	return (modifiers & (KEY_LEFT_CONTROL|KEY_RIGHT_CONTROL)) != 0;
}

/** Replies if the given list of modifiers contains a Shift key.
 *
 * \param modifiers is the list of modifier keys to test.
 * \return <code>true</code> if a Shift key is inside the given modifiers, otherwise <code>false</code>.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
inline bool isShiftModifierKey(ModifierKeyField modifiers)
{
	return (modifiers & (KEY_LEFT_SHIFT|KEY_RIGHT_SHIFT)) != 0;
}

/** Replies if the given list of modifiers contains a Meta key.
 *
 * \param modifiers is the list of modifier keys to test.
 * \return <code>true</code> if a Meta key is inside the given modifiers, otherwise <code>false</code>.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
inline bool isMetaModifierKey(ModifierKeyField modifiers)
{
	return (modifiers & (KEY_LEFT_META|KEY_RIGHT_META)) != 0;
}

/** Replies if the given list of modifiers contains an Alt key.
 *
 * \param modifiers is the list of modifier keys to test.
 * \return <code>true</code> if an Alt key is inside the given modifiers, otherwise <code>false</code>.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
inline bool isAltModifierKey(ModifierKeyField modifiers)
{
	return (modifiers & (KEY_LEFT_ALT|KEY_RIGHT_ALT|KEY_ALT_GR)) != 0;
}

/** Replies if the given list of modifiers contains a Super key.
 *
 * \param modifiers is the list of modifier keys to test.
 * \return <code>true</code> if a Super key is inside the given modifiers, otherwise <code>false</code>.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
inline bool isSuperModifierKey(ModifierKeyField modifiers)
{
	return (modifiers & (KEY_LEFT_SUPER|KEY_RIGHT_SUPER)) != 0;
}

/** Replies if the given list of modifiers contains a Hyper key.
 *
 * \param modifiers is the list of modifier keys to test.
 * \return <code>true</code> if a Hyper key is inside the given modifiers, otherwise <code>false</code>.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
inline bool isHyperModifierKey(ModifierKeyField modifiers)
{
	return (modifiers & (KEY_LEFT_HYPER|KEY_RIGHT_HYPER)) != 0;
}

/** Replies if the given list of modifiers contains a Lock key.
 *
 * \param modifiers is the list of modifier keys to test.
 * \return <code>true</code> if a Lock key is inside the given modifiers, otherwise <code>false</code>.
 * \author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 */
inline bool isLockModifierKey(ModifierKeyField modifiers)
{
	return (modifiers & (KEY_CAPS_LOCK|KEY_SHIFT_LOCK)) != 0;
}

#  ifdef __cplusplus
} // namespace dxware
#  endif

#  ifdef X11
#    include <3dxware/Xwin/3dxXWindowKey.h>
#  elif defined(WIN32) || defined(WIN64) || defined(MINGW) || defined(MINGW32)
#    include <3dxware/MSwin/3dxMSWindowKey.h>
#  else
#    error unsupported operating system
#  endif

#endif // __3DX_KEY_H__

