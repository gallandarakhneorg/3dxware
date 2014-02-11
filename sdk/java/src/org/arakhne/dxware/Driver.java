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
import java.awt.Dialog;
import java.awt.Frame;

/**
 * This class represents a 3D device named a SpaceMouse.
 * 
 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 * @version $Name$ $Revision$ $Date$
 */
class Driver {

	static {
		System.loadLibrary("3dxware-jni"); //$NON-NLS-1$
	}
	
	/**
	 * C pointer on the 3DxWare driver.
	 */
	private final long ptr3DxWareDriver;
	
	/** Indicates if the object was disposed.
	 */
	private boolean isDisposed = false;
	
	/** Peer component.
	 */
	private volatile Component peerComponent = null;
	
	/**
	 */
	public Driver() {
		this.ptr3DxWareDriver = allocateDriverResources();
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
	public synchronized void dispose() {
		if (!this.isDisposed) {
			releaseDriverResources(this.ptr3DxWareDriver);
			this.isDisposed = true;
			this.peerComponent = null;
		}
	}

	/** Allocate the resources of the driver
	 * 
	 * @return C pointer on the 3DxWare driver.
	 */
	private native long allocateDriverResources();

	/** Release the resources of the driver
	 * 
	 * @param ptr is the C pointer on the 3DxWare driver.
	 */
	private native void releaseDriverResources(long ptr);

	/** Replies the version of the API that is supporting this device.
	 * 
	 * @return the version of the API that is supporting this device.
	 */
	public final synchronized String getAPIVersion() {
		if (this.isDisposed) return null;
		return getAPIVersion(this.ptr3DxWareDriver);
	}

	/** Replies the version of the API that is supporting this device.
	 * 
	 * @param ptr is the C pointer on the 3DxWare driver.
	 * @return the version of the API that is supporting this device.
	 */
	private native String getAPIVersion(long ptr);

	/** Replies the name of the operating system or of the
	 * window manager that is supported by this driver.
	 * 
	 * @return the name of the operating system or the window manager.
	 */
	public final synchronized String getOSName() {
		if (this.isDisposed) return null;
		return getOSName(this.ptr3DxWareDriver);
	}

	/** Replies the name of the operating system or of the
	 * window manager that is supported by this driver.
	 * 
	 * @param ptr is the C pointer on the 3DxWare driver.
	 * @return the name of the operating system or the window manager.
	 */
	private native String getOSName(long ptr);

	/** Attach the given component to this driver to use it as a peer.
	 * 
	 * @param component
	 * @return <code>true</code> if the component was binded, otherwise <code>false</code>
	 */
	synchronized boolean attachPeer(Component component) {
		if (!this.isDisposed && component!=null && this.peerComponent==null && component.isDisplayable()) {
			String title = null;
			byte superType = 0;
			if (component instanceof Frame) {
				title = ((Frame)component).getTitle();
				superType = 1;
			}
			else if (component instanceof Dialog) {
				title = ((Dialog)component).getTitle();
				superType = 2;
			}
			bindPeer(this.ptr3DxWareDriver,
						component,
						component.getName(),
						title,
						component.getClass().getName(),
						superType);
			this.peerComponent = component;
			return true;
		}
		return false;
	}
	
	/** Bind the specified component to the underlying driver.
	 * 
	 * @param ptr is the C pointer on the 3DxWare driver.
	 * @param awtComponent is the peer component.
	 * @param componentName is the name of the component to bind to.
	 * @param title is the title of the peer component or <code>null</code>
	 * @param className is the name of the class of the peer comonent.
	 * @param superType indicates the type of the peer component. <code>1</code>
	 * for Frame, <code>2</code> for Dialog.
	 */
	private native void bindPeer(long ptr, Component awtComponent, String componentName, String title, String className, byte superType);
	
	/** Initialize the connexion with the 3DxWare driver.
	 * <p>
	 * It is not required to invoked <code>bindTo3DxWare()</code>
	 * but with it youare able to select when the native layer must
	 * try to be connected to the remote 3DxWare driver.
	 * 
	 * @return <code>true</code> if the binding was successfully done,
	 * otherwise <code>false</code>
	 */
	public final synchronized boolean bindTo3DxWare() {
		if (this.peerComponent!=null && this.isDisposed) return false;
		return bindTo3DxWare(this.ptr3DxWareDriver);
	}

	/** Initialize the connexion with the 3DxWare driver.
	 * <p>
	 * This binding is automatically done by the native layer
	 * when {@link #nextEvent(DeviceEvent)} was invoked.
	 * <p>
	 * It is not required to invoked <code>bindTo3DxWare()</code>
	 * but with it youare able to select when the native layer must
	 * try to be connected to the remote 3DxWare driver.
	 * 
	 * @param ptr is the C pointer on the 3DxWare driver.
	 * @return <code>true</code> if the binding was successfully done,
	 * otherwise <code>false</code>
	 */
	private native boolean bindTo3DxWare(long ptr);

	/** Replies if this driver was disposed.
	 * <p>
	 * A driver was disposed when it was disconnected from its remote driver.
	 * 
	 * @return <code>true</code> if the driver was disposed, otherwise <code>false</code>
	 */
	public synchronized boolean isDisposed() {
		return this.isDisposed;
	}

	/** Ask to the driver to treat the given native event.
	 * 
	 * @param nativeEventPtr is a pointer/reference to the native data structure which is
	 * the event to treat.
	 * @param deviceEvent is the event to fill.
	 * @return <code>true</code> if the <var>deviceEvent</var> was filled, otherwise <code>false</code>
	 */
	final boolean treatNativeEvent(long nativeEventPtr, DeviceEvent deviceEvent) {
		if (this.peerComponent==null || this.isDisposed) return false;
		return treatNativeEvent(this.ptr3DxWareDriver, nativeEventPtr, deviceEvent);
	}

	/** Ask to the driver to treat the given native event.
	 * 
	 * @param ptr is the C pointer on the 3DxWare driver.
	 * @param nativeEventPtr is a pointer/reference to the native data structure which is
	 * the event to treat.
	 * @param deviceEvent is the event to fill.
	 * @return <code>true</code> if the <var>deviceEvent</var> was filled, otherwise <code>false</code>
	 */
	private native boolean treatNativeEvent(long ptr, long nativeEventPtr, DeviceEvent deviceEvent);

	/** Replies if this driver is supporting the keyboard events.
	 * 
	 * @return <code>true</code> if keyboard events should be supported, otherwise <code>false</code>
	 */
	public synchronized boolean isKeyboardEventFired() {
		return isKeyboardEventFired(this.ptr3DxWareDriver);
	}
	
	/** Replies if this driver is supporting the keyboard events.
	 * 
	 * @param ptr is the C pointer on the 3DxWare driver.
	 * @return <code>true</code> if keyboard events should be supported, otherwise <code>false</code>
	 */
	private native boolean isKeyboardEventFired(long ptr);

	/** Force this driver to fire or to ignore the keyboard events.
	 * 
	 * @param fireEvents is <code>true</code> to fire the keyboard events, otherwise <code>false</code>
	 */
	public synchronized void setKeyboardEventFired(boolean fireEvents) {
		setKeyboardEventFired(this.ptr3DxWareDriver, fireEvents);
	}
	
	/** Force this driver to fire or to ignore the keyboard events.
	 * 
	 * @param ptr is the C pointer on the 3DxWare driver.
	 * @param fireEvents is <code>true</code> to fire the keyboard events, otherwise <code>false</code>
	 */
	private native void setKeyboardEventFired(long ptr, boolean fireEvents);

	/** Force the sensitivity of the driver.
	 * 
	 * @param sensitivity is the new sensitivity. 
	 */
	public synchronized void setSensivity(float sensitivity) {
		if (this.peerComponent!=null && !this.isDisposed)
			setSensitivity(this.ptr3DxWareDriver, sensitivity);
	}
	
	/** Force the sensitivity of the driver.
	 * 
	 * @param ptr is the C pointer on the 3DxWare driver.
	 * @param sensitivity is the new sensitivity. 
	 */
	private native void setSensitivity(long ptr, float sensitivity);

}
