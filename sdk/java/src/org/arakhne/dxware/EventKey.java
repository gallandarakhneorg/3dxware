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


/** List of supported keys by the 3DxWare C++ driver.
*
 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 * @version $Name$ $Revision$ $Date$
*/
public enum EventKey {
	/** No key */
	KEY_VOID,
	/** Back-space */
	KEY_BACKSPACE('\b'),
	/** Space */
	KEY_SPACE(' '),
	/** Tabulation */
	KEY_TAB('\t'),
	/** Line feed */
	KEY_LINEFEED('\r'),
	/** Carriage return */
	KEY_RETURN('\n'),
	/** Escape */
	KEY_ESC((char)27),
	/** '0' */
	KEY_0('0'),
	/** '1' */
	KEY_1('1'),
	/** '2' */
	KEY_2('2'),
	/** '3' */
	KEY_3('3'),
	/** '4' */
	KEY_4('4'),
	/** '5' */
	KEY_5('5'),
	/** '6' */
	KEY_6('6'),
	/** '7' */
	KEY_7('7'),
	/** '8' */
	KEY_8('8'),
	/** '9' */
	KEY_9('9'),
	/** 'a' */
	KEY_a('a'),
	/** 'b' */
	KEY_b('b'),
	/** 'c' */
	KEY_c('c'),
	/** 'd' */
	KEY_d('d'),
	/** 'e' */
	KEY_e('e'),
	/** 'f' */
	KEY_f('f'),
	/** 'g' */
	KEY_g('g'),
	/** 'h' */
	KEY_h('h'),
	/** 'i' */
	KEY_i('i'),
	/** 'j' */
	KEY_j('j'),
	/** 'k' */
	KEY_k('k'),
	/** 'l' */
	KEY_l('l'),
	/** 'm' */
	KEY_m('m'),
	/** 'n' */
	KEY_n('n'),
	/** 'o' */
	KEY_o('o'),
	/** 'p' */
	KEY_p('p'),
	/** 'q' */
	KEY_q('q'),
	/** 'r' */
	KEY_r('r'),
	/** 's' */
	KEY_s('s'),
	/** 't' */
	KEY_t('t'),
	/** 'u' */
	KEY_u('u'),
	/** 'v' */
	KEY_v('v'),
	/** 'w' */
	KEY_w('w'),
	/** 'x' */
	KEY_x('x'),
	/** 'y' */
	KEY_y('y'),
	/** 'z' */
	KEY_z('z'),
	/** 'A' */
	KEY_A('A'),
	/** 'B' */
	KEY_B('B'),
	/** 'C' */
	KEY_C('C'),
	/** 'D' */
	KEY_D('D'),
	/** 'E' */
	KEY_E('E'),
	/** 'F' */
	KEY_F('F'),
	/** 'G' */
	KEY_G('G'),
	/** 'H' */
	KEY_H('H'),
	/** 'I' */
	KEY_I('I'),
	/** 'J' */
	KEY_J('J'),
	/** 'K' */
	KEY_K('K'),
	/** 'L' */
	KEY_L('L'),
	/** 'M' */
	KEY_M('M'),
	/** 'N' */
	KEY_N('N'),
	/** 'O' */
	KEY_O('O'),
	/** 'P' */
	KEY_P('P'),
	/** 'Q' */
	KEY_Q('Q'),
	/** 'R' */
	KEY_R('R'),
	/** 'S' */
	KEY_S('S'),
	/** 'T' */
	KEY_T('T'),
	/** 'U' */
	KEY_U('U'),
	/** 'V' */
	KEY_V('V'),
	/** 'W' */
	KEY_W('W'),
	/** 'X' */
	KEY_X('X'),
	/** 'Y' */
	KEY_Y('Y'),
	/** 'Z' */
	KEY_Z('Z'),
	/** '&lt;' */
	KEY_LESS('<'),
	/** '&gt;' */
	KEY_GREATER('>'),
	/** '&amp;' */
	KEY_AMPERSAND('&'),
	/** '~' */
	KEY_TILDE('~'),
	/** '"' */
	KEY_DOUBLE_QUOTE('"'),
	/** ''' */
	KEY_QUOTE('\''),
	/** '{' */
	KEY_LEFT_BRACE('{'),
	/** '}' */
	KEY_RIGHT_BRACE('}'),
	/** '(' */
	KEY_LEFT_PARENTHESIS('('),
	/** ')' */
	KEY_RIGHT_PARENTHESIS(')'),
	/** '[' */
	KEY_LEFT_BRAQUET('['),
	/** ']' */
	KEY_RIGHT_BRAQUET(']'),
	/** '-' */
	KEY_MINUS('-'),
	/** '|' */
	KEY_PIPE('|'),
	/** '`' */
	KEY_BACKQUOTE('`'),
	/** '_' */
	KEY_UNDERSCORE('_'),
	/** '\' */
	KEY_BACKSLASH('\\'),
	/** '^' */
	KEY_CIRCUMFLEX('^'),
	/** '@' */
	KEY_AT('@'),
	/** '=' */
	KEY_EQUAL('='),
	/** '+' */
	KEY_PLUS('+'),
	/** '$' */
	KEY_DOLLAR('$'),
	/** '%' */
	KEY_PERCENT('%'),
	/** '*' */
	KEY_STAR('*'),
	/** '?' */
	KEY_QUESTION('?'),
	/** ',' */
	KEY_COMMA(','),
	/** '.' */
	KEY_POINT('.'),
	/** ';' */
	KEY_SEMICOLUMN(';'),
	/** '/' */
	KEY_SLASH('/'),
	/** ':' */
	KEY_COLUMN(':'),
	/** '!' */
	KEY_EXCLAMATION('!'),
	/** &lt;CLEAR&gt; */
	KEY_CLEAR,
	/** &lt;PAUSE&gt; */
	KEY_PAUSE,
	/** &lt;SCROLL-LOCK&gt; */
	KEY_SCROLLLOCK,
	/** &lt;SYS-REQ&gt; */
	KEY_SYSREQ,
	/** &lt;DELETE&gt; */
	KEY_DELETE,
	/** &lt;HOME&gt; */
	KEY_HOME,
	/** &lt;LEFT&gt; */
	KEY_LEFT,
	/** &lt;UP&gt; */
	KEY_UP,
	/** &lt;RIGHT&gt; */
	KEY_RIGHT,
	/** &lt;DOWN&gt; */
	KEY_DOWN,
	/** &lt;PAGE_DOWN&gt; */
	KEY_PAGE_DOWN,
	/** &lt;PAGE_UP&gt; */
	KEY_PAGE_UP,
	/** &lt;END&gt; */
	KEY_END,
	/** &lt;BEGIN&gt; */
	KEY_BEGIN,
	/** '+' on PAD */
	KEY_PAD_ADD('+'),
	/** '-' on PAD */
	KEY_PAD_SUB('-'),
	/** '/' on PAD */
	KEY_PAD_DIV('/'),
	/** '*' on PAD */
	KEY_PAD_MUL('*'),
	/** '=' on PAD */
	KEY_PAD_EQUAL('='),
	/** &lt;RETURN&gt; on PAD */
	KEY_PAD_ENTER('\n'),
	/** '.' on PAD */
	KEY_PAD_DECIMAL('.'),
	/** '0' on PAD */
	KEY_PAD_0('0'),
	/** '1' on PAD */
	KEY_PAD_1('1'),
	/** '2' on PAD */
	KEY_PAD_2('2'),
	/** '3' on PAD */
	KEY_PAD_3('3'),
	/** '4' on PAD */
	KEY_PAD_4('4'),
	/** '5' on PAD */
	KEY_PAD_5('5'),
	/** '6' on PAD */
	KEY_PAD_6('6'),
	/** '7' on PAD */
	KEY_PAD_7('7'),
	/** '8' on PAD */
	KEY_PAD_8('8'),
	/** '9' on PAD */
	KEY_PAD_9('9'),
	/** &lt;F1&gt; */
	KEY_F1,
	/** &lt;F2&gt; */
	KEY_F2,
	/** &lt;F3&gt; */
	KEY_F3,
	/** &lt;F4&gt; */
	KEY_F4,
	/** &lt;F5&gt; */
	KEY_F5,
	/** &lt;F6&gt; */
	KEY_F6,
	/** &lt;F7&gt; */
	KEY_F7,
	/** &lt;F8&gt; */
	KEY_F8,
	/** &lt;F9&gt; */
	KEY_F9,
	/** &lt;F10&gt; */
	KEY_F10,
	/** &lt;F11&gt; */
	KEY_F11,
	/** &lt;F12&gt; */
	KEY_F12;
	
	private final char glyph;
	
	private EventKey(char c) {
		this.glyph = c;
	}

	private EventKey() {
		this.glyph = '\0';
	}
	
	/** Replies the graphical representation of this key.
	 * If no graphical representation is available, the character
	 * '\0' will be replied
	 * 
	 * @return the graphical representation or '\0'
	 */
	public char getGlyph() {
		return this.glyph;
	}
	
	/** Replies the event key thati s corresponding to the given C index.
	 * 
	 * @param index
	 * @return an event key
	 */
	static EventKey fromCIndex(int index) {
		int searchIndex = (index<0x100) ? index : 0x100;
		EventKey[] all = EventKey.values();
		for(int i=0; i<all.length; i++) {
			if (all[i].glyph==searchIndex) {
				if (index<0x100) return all[i];
				return all[i+(index-0x100)];
			}
		}
		return KEY_VOID;
	}

}
