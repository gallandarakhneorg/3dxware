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
package org.arakhne.dxware.test;

import java.awt.BorderLayout;
import java.awt.Image;
import java.io.IOException;
import java.net.URL;

import javax.imageio.ImageIO;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

/**
 * This panel draw a mouse pad and its coordinate.
 * 
 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 * @version $Name$ $Revision$ $Date$
 */
public class SpaceMousePanel extends JPanel {
	
	private static final long serialVersionUID = -2744886335123988996L;
	
	/**
	 * Load an icon.
	 * @param name is the icon name
	 * @return the icon
	 */
	static Icon loadIcon(String name) {
		try {
			String rname = "/org/arakhne/dxware/test/"+name; //$NON-NLS-1$
			URL url = SpaceMousePanel.class.getResource(rname);
			if (url==null) throw new Error("Unable to find the resource "+rname); //$NON-NLS-1$
			Image img = ImageIO.read(url);
			if (img==null) throw new Error("Unable to load the resource "+rname); //$NON-NLS-1$
			return new ImageIcon(img);
		}
		catch(IOException e) {
			throw new Error(e);
		}
	}
	
	/** Icon for the translation along OX axis.
	 */
	public static final Icon ICON_TRANSLATION_OX = loadIcon("t_lr.png"); //$NON-NLS-1$
	
	/** Icon for the translation along OY axis.
	 */
	public static final Icon ICON_TRANSLATION_OY = loadIcon("t_ud.png"); //$NON-NLS-1$

	/** Icon for the translation along OZ axis.
	 */
	public static final Icon ICON_TRANSLATION_OZ = loadIcon("t_fb.png"); //$NON-NLS-1$

	/** Icon for the rotation around OX axis.
	 */
	public static final Icon ICON_ROTATION_OX = loadIcon("r_fb.png"); //$NON-NLS-1$

	/** Icon for the rotation around OY axis.
	 */
	public static final Icon ICON_ROTATION_OY = loadIcon("r_turn.png"); //$NON-NLS-1$

	/** Icon for the rotation around OZ axis.
	 */
	public static final Icon ICON_ROTATION_OZ = loadIcon("r_lr.png"); //$NON-NLS-1$

	private final SpaceMousePanelType type;
	private final JLabel value = new JLabel();
	
	/**
	 * @param type is the type of the panel
	 */
	public SpaceMousePanel(SpaceMousePanelType type) {
		super(new BorderLayout());
		this.type = type;
		JLabel iconLabel = new JLabel(getIcon());
		add(iconLabel, BorderLayout.CENTER);
		JPanel p = new JPanel();
		p.add(this.value);
		add(p, BorderLayout.SOUTH);
	}
	
	/** Replies the icon associated to this panel.
	 * 
	 * @return an icon
	 */
	public Icon getIcon() {
		switch(this.type) {
		case TRANSLATION_OX:
			return ICON_TRANSLATION_OX;
		case TRANSLATION_OY:
			return ICON_TRANSLATION_OY;
		case TRANSLATION_OZ:
			return ICON_TRANSLATION_OZ;
		case ROTATION_OX:
			return ICON_ROTATION_OX;
		case ROTATION_OY:
			return ICON_ROTATION_OY;
		case ROTATION_OZ:
			return ICON_ROTATION_OZ;
		}
		return null;
	}
	
	/** Set the value.
	 * 
	 * @param value
	 */
	public void setValue(float value) {
		this.value.setText(Float.toString(value));
	}
	
	/** Set the value.
	 * 
	 * @param value
	 */
	public void setValue(double value) {
		this.value.setText(Double.toString(value));
	}
	
	/** Set the value.
	 * 
	 * @param value
	 */
	public void setValue(long value) {
		this.value.setText(Long.toString(value));
	}

}
