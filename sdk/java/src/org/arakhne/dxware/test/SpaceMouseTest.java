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
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

import javax.swing.BoxLayout;
import javax.swing.Icon;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;

import org.arakhne.dxware.DeviceEvent;
import org.arakhne.dxware.DeviceListener;
import org.arakhne.dxware.ModifierKey;
import org.arakhne.dxware.SpaceMouse;

/**
 * This class represents a 3D device named a SpaceMouse.
 * 
 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 * @version $Name$ $Revision$ $Date$
 */
public class SpaceMouseTest extends JDialog implements DeviceListener, KeyListener {

	private static final long serialVersionUID = -5745853052288026196L;

	private final SpaceMouse mouse = SpaceMouse.createInstance(this);
	
	/**
	 * Icon for the keyboard.
	 */
	public static final Icon ICON_KEYBOARD = SpaceMousePanel.loadIcon("keyboard.jpg"); //$NON-NLS-1$

	/**
	 * Icon for the mouse button.
	 */
	public static final Icon ICON_BUTTON = SpaceMousePanel.loadIcon("button.png"); //$NON-NLS-1$

	/**
	 * Icon for the quit button.
	 */
	public static final Icon ICON_QUIT = SpaceMousePanel.loadIcon("quit.png"); //$NON-NLS-1$

	private final SpaceMousePanel jTranslationOx = new SpaceMousePanel(SpaceMousePanelType.TRANSLATION_OX);
	private final SpaceMousePanel jTranslationOy = new SpaceMousePanel(SpaceMousePanelType.TRANSLATION_OY);
	private final SpaceMousePanel jTranslationOz = new SpaceMousePanel(SpaceMousePanelType.TRANSLATION_OZ);
	private final SpaceMousePanel jRotationOx = new SpaceMousePanel(SpaceMousePanelType.ROTATION_OX);
	private final SpaceMousePanel jRotationOy = new SpaceMousePanel(SpaceMousePanelType.ROTATION_OY);
	private final SpaceMousePanel jRotationOz = new SpaceMousePanel(SpaceMousePanelType.ROTATION_OZ);
	private final JLabel jKeyboard = new JLabel();
	private final JLabel jButton = new JLabel();
	private final JButton buttonQuit = new JButton(ICON_QUIT);
	
	/**
	 * @param args are command line arguments
	 * @throws Exception is case of exception
	 */
	public static void main(String[] args) throws Exception {
		SpaceMouseTest gui = new SpaceMouseTest();
		gui.setVisible(true);
		System.out.println("Freeing memory"); //$NON-NLS-1$
		gui.dispose();
		gui = null;
	}
	
	
	
	/**
	 */
	public SpaceMouseTest() {
		super((JDialog)null, "Test 3DxWare Java Wrapper"); //$NON-NLS-1$
		setModal(true);
		getContentPane().setPreferredSize(new Dimension(640,480));
		getContentPane().setLayout(new BorderLayout());
		
		JPanel centrePanel = new JPanel();

		centrePanel.setLayout(new GridLayout(2,3));
		centrePanel.add(this.jTranslationOx);
		centrePanel.add(this.jTranslationOy);
		centrePanel.add(this.jTranslationOz);
		centrePanel.add(this.jRotationOx);
		centrePanel.add(this.jRotationOy);
		centrePanel.add(this.jRotationOz);
		getContentPane().add(centrePanel, BorderLayout.CENTER);
		
		JPanel bottomPanel = new JPanel();
		bottomPanel.setLayout(new BoxLayout(bottomPanel,BoxLayout.X_AXIS));
		getContentPane().add(bottomPanel, BorderLayout.SOUTH);

		Dimension dim = new Dimension(100, 64);
		
		this.jKeyboard.setIcon(ICON_KEYBOARD);
		this.jKeyboard.setText("<None>"); //$NON-NLS-1$
		this.jKeyboard.setMinimumSize(dim);
		this.jKeyboard.setPreferredSize(dim);
		bottomPanel.add(this.jKeyboard);

		this.jButton.setIcon(ICON_BUTTON);
		this.jButton.setText("<None>"); //$NON-NLS-1$
		this.jButton.setMinimumSize(dim);
		this.jButton.setPreferredSize(dim);
		bottomPanel.add(this.jButton);

		this.buttonQuit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				SpaceMouseTest.this.setVisible(false);
			}
		});
		bottomPanel.add(this.buttonQuit);
		
		pack();

		this.mouse.addDeviceListener(this);
		this.addKeyListener(this);
	}
	
	

	/**
	 * {@inheritDoc}
	 */
	@Override
	public void dispose() {
		this.mouse.dispose();
		super.dispose();
	}
	
	private void setButtonText(String prefix, DeviceEvent event) {
		StringBuffer buf = new StringBuffer();
		buf.append(prefix);
		buf.append(": "); //$NON-NLS-1$
		buf.append(event.getButton());
		this.jButton.setText(buf.toString());
	}

	private void setKeyText(String prefix, DeviceEvent event) {
		StringBuffer buf = new StringBuffer();
		buf.append(prefix);
		buf.append(": "); //$NON-NLS-1$
		if (event.getKeyModifiers()!=0) {
			buf.append(ModifierKey.toString(event.getKeyModifiers()));
			buf.append("+"); //$NON-NLS-1$
		}
		buf.append("<"); //$NON-NLS-1$
		buf.append(event.getKey().name());
		buf.append(">"); //$NON-NLS-1$
		this.jKeyboard.setText(buf.toString());
	}

	private void setKeyText(String prefix, KeyEvent event) {
		StringBuffer buf = new StringBuffer();
		buf.append(prefix);
		buf.append(": "); //$NON-NLS-1$
		if (event.getModifiers()!=0) {
			buf.append(KeyEvent.getKeyModifiersText(event.getModifiers()));
			buf.append("+"); //$NON-NLS-1$
		}
		buf.append("<"); //$NON-NLS-1$
		buf.append(KeyEvent.getKeyText(event.getKeyCode()));
		buf.append(">"); //$NON-NLS-1$
		this.jKeyboard.setText(buf.toString());
	}

	/**
	 * {@inheritDoc}
	 */
	public void onDeviceButtonPressed(DeviceEvent event) {
		setButtonText("Pressed", event); //$NON-NLS-1$
	}

	/**
	 * {@inheritDoc}
	 */
	public void onDeviceButtonReleased(DeviceEvent event) {
		setButtonText("Released", event); //$NON-NLS-1$
	}

	/**
	 * {@inheritDoc}
	 */
	public void onDeviceMotion(DeviceEvent event) {
		this.jTranslationOx.setValue(event.getX());
		this.jTranslationOy.setValue(event.getY());
		this.jTranslationOz.setValue(event.getZ());
		this.jRotationOx.setValue(event.getA());
		this.jRotationOy.setValue(event.getB());
		this.jRotationOz.setValue(event.getC());
	}

	/**
	 * {@inheritDoc}
	 */
	public void onKeyPressed(DeviceEvent event) {
		setKeyText("Pressed", event); //$NON-NLS-1$
	}

	/**
	 * {@inheritDoc}
	 */
	public void onKeyReleased(DeviceEvent event) {
		setKeyText("Released", event); //$NON-NLS-1$
	}

	/**
	 * {@inheritDoc}
	 */
	public void keyPressed(KeyEvent event) {
		setKeyText("Pressed", event); //$NON-NLS-1$
	}

	/**
	 * {@inheritDoc}
	 */
	public void keyReleased(KeyEvent event) {
		setKeyText("Released", event); //$NON-NLS-1$
	}

	/**
	 * {@inheritDoc}
	 */
	public void keyTyped(KeyEvent event) {
		//
	}
	
}
