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

import java.awt.Component;
import java.awt.Toolkit;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.util.ArrayList;
import java.util.Collection;

import javax.swing.JDialog;
import javax.swing.JFrame;

import org.arakhne.dxware.X11.XSpaceMouse;

import sun.awt.X11.XToolkit;

/**
 * This class represents a 3D device named a SpaceMouse.
 * 
 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 * @version $Name$ $Revision$ $Date$
 */
public abstract class SpaceMouse {

	/** Create an instance of the SpaceMouse device.
	 * 
	 * @param peerComponent is the AWt component that must be connected to
	 * the physical device.
	 * @return the new instance of the SpaceMouse
	 */
	public static SpaceMouse createInstance(JFrame peerComponent) {
		Toolkit toolkit = Toolkit.getDefaultToolkit();
		if (toolkit instanceof XToolkit) {
			return new XSpaceMouse(peerComponent);
		}
		throw new Error("unsupported type of AWT toolkit"); //$NON-NLS-1$
	}	
	
	/** Create an instance of the SpaceMouse device.
	 * 
	 * @param peerComponent is the AWt component that must be connected to
	 * the physical device.
	 * @return the new instance of the SpaceMouse
	 */
	public static SpaceMouse createInstance(JDialog peerComponent) {
		Toolkit toolkit = Toolkit.getDefaultToolkit();
		if (toolkit instanceof XToolkit) {
			return new XSpaceMouse(peerComponent);
		}
		throw new Error("unsupported type of AWT toolkit"); //$NON-NLS-1$
	}	

	/** Listeners.
	 */
	private Collection<DeviceListener> listeners = null;
	
	/** Low-level driver.
	 */
	protected final Driver driver;
	
	/**
	 * @param window is the AWT component that must be binded
	 * to the space mouse driver. 
	 */
	protected SpaceMouse(JFrame window) {
		this((Component)window);
	}

	/**
	 * @param window is the AWT component that must be binded
	 * to the space mouse driver. 
	 */
	protected SpaceMouse(JDialog window) {
		this((Component)window);
	}

	/**
	 * @param peerComponent is the AWT component that must be binded
	 * to the space mouse driver. 
	 */
	private SpaceMouse(final Component peerComponent) {
		this.driver = new Driver();
		peerComponent.addComponentListener(new ComponentAdapter() {
			@SuppressWarnings("synthetic-access")
			@Override
			public void componentShown(ComponentEvent e) {
				initializeDevice(peerComponent);
			}
			
		});
	}
	
	/** Invoked to initialize the device.
	 * 
	 * @param peerComponent is the AWt peer component that must be binded to the device. 
	 */
	protected void initializeDevice(Component peerComponent) {
		SpaceMouse.this.driver.attachPeer(peerComponent);
		SpaceMouse.this.bindTo3DxWare();
		peerComponent.requestFocus();
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	protected void finalize() throws Throwable {
		dispose();
		super.finalize();
	}
	
	/** Dispose the resources.
	 */
	public void dispose() {
		this.driver.dispose();
	}

	/** Replies if this space mouse is disposed.
	 * <p>
	 * A space mouse is disposed when it was disconnected from its driver.
	 * A disposed space mouse could not be connected again to a driver.
	 * 
	 * @return <code>true</code> if the driver was disposed, otherwise <code>false</code>
	 */
	public boolean isDisposed() {
		return this.driver.isDisposed();
	}

	/** Add a listener on the device events.
	 * 
	 * @param listener
	 */
	public void addDeviceListener(DeviceListener listener) {
		if (this.listeners==null) {
			this.listeners = new ArrayList<DeviceListener>(2);
		}
		this.listeners.add(listener);
	}

	/** Remove a listener on the device events.
	 * 
	 * @param listener
	 */
	public void removeDeviceListener(DeviceListener listener) {
		if (this.listeners==null) return;
		this.listeners.remove(listener);
		if (this.listeners.isEmpty()) {
			this.listeners = null;
		}
	}

	/** Replies the version of the API that is supporting this device.
	 * 
	 * @return the version of the API that is supporting this device.
	 */
	public String getAPIVersion() {
		return this.driver.getAPIVersion();
	}

	/** Fire Key-Pressed event
	 * 
	 * @param event
	 */
	public void fireKeyPressed(DeviceEvent event) {
		if (this.listeners!=null) {
			for(DeviceListener listener : this.listeners) {
				if (listener!=null) {
					listener.onKeyPressed(event);
				}
			}
		}
	}

	/** Fire Key-Released event
	 * 
	 * @param event
	 */
	public void fireKeyReleased(DeviceEvent event) {
		if (this.listeners!=null) {
			for(DeviceListener listener : this.listeners) {
				if (listener!=null) {
					listener.onKeyReleased(event);
				}
			}
		}
	}

	/** Fire Button-Pressed event
	 * 
	 * @param event
	 */
	public void fireButton3DPressed(DeviceEvent event) {
		if (this.listeners!=null) {
			for(DeviceListener listener : this.listeners) {
				if (listener!=null) {
					listener.onDeviceButtonPressed(event);
				}
			}
		}
	}

	/** Fire Button-Released event
	 * 
	 * @param event
	 */
	public void fireButton3DReleased(DeviceEvent event) {
		if (this.listeners!=null) {
			for(DeviceListener listener : this.listeners) {
				if (listener!=null) {
					listener.onDeviceButtonReleased(event);
				}
			}
		}
	}

	/** Fire Mouse3D-Motion event
	 * 
	 * @param event
	 */
	public void fireMouse3DMotion(DeviceEvent event) {
		if (this.listeners!=null) {
			for(DeviceListener listener : this.listeners) {
				if (listener!=null) {
					listener.onDeviceMotion(event);
				}
			}
		}
	}
	
	/** Initialize the connexion with the 3DxWare driver.
	 * <p>
	 * It is not required to invoked <code>bindTo3DxWare()</code>
	 * but with it youare able to select when the native layer must
	 * try to be connected to the remote 3DxWare driver.
	 * 
	 * @return <code>true</code> if the binding was successfully done,
	 * otherwise <code>false</code>
	 */
	public final boolean bindTo3DxWare() {
		return this.driver.bindTo3DxWare();
	}
	
	/** Ask to the driver to treat the given native event.
	 * 
	 * @param nativeEventPtr is a pointer/reference to the native data structure which is
	 * the event to treat.
	 * @param deviceEvent is the event to fill.
	 * @return <code>true</code> if the <var>deviceEvent</var> was filled, otherwise <code>false</code>
	 */
	protected final boolean treatNativeEvent(long nativeEventPtr, DeviceEvent deviceEvent) {
		return this.driver.treatNativeEvent(nativeEventPtr, deviceEvent);
	}
	
	/** Replies if this driver is supporting the keyboard events.
	 * 
	 * @return <code>true</code> if keyboard events should be supported, otherwise <code>false</code>
	 */
	public boolean isKeyboardEventFired() {
		return this.driver.isKeyboardEventFired();
	}
	
	/** Force this driver to fire or to ignore the keyboard events.
	 * 
	 * @param fireEvents is <code>true</code> to fire the keyboard events, otherwise <code>false</code>
	 */
	public void setKeyboardEventFired(boolean fireEvents) {
		this.driver.setKeyboardEventFired(fireEvents);
	}

}
