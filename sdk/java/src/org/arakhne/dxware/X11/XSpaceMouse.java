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
package org.arakhne.dxware.X11;

import java.awt.Component;
import java.awt.Toolkit;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.Executors;

import javax.swing.JDialog;
import javax.swing.JFrame;

import org.arakhne.dxware.DeviceEvent;
import org.arakhne.dxware.SpaceMouse;

import sun.awt.X11.XConstants;
import sun.awt.X11.XEvent;
import sun.awt.X11.XToolkit;
import sun.awt.X11.XToolkit.XEventListener;

/**
 * This class represents a 3D device named a SpaceMouse.
 * 
 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
 * @version $Name$ $Revision$ $Date$
 */
public class XSpaceMouse extends SpaceMouse implements XEventListener {

	private final EventDispatcher eventDispatcher = new EventDispatcher();
	
	/**
	 * @param window is the AWT component that must be binded
	 * to the space mouse driver. 
	 */
	public XSpaceMouse(JFrame window) {
		super(window);
	}

	/**
	 * @param window is the AWT component that must be binded
	 * to the space mouse driver. 
	 */
	public XSpaceMouse(JDialog window) {
		super(window);
	}
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	protected void initializeDevice(Component peerComponent) {
		this.eventDispatcher.start();
		Toolkit toolkit = Toolkit.getDefaultToolkit();
		if (toolkit instanceof XToolkit) {
			((XToolkit)toolkit).addXEventListener(this);
		}
		else {
			throw new RuntimeException("unsupported AWT toolkit"); //$NON-NLS-1$
		}
		super.initializeDevice(peerComponent);
	}

	/** Dispose the resources.
	 */
	@Override
	public void dispose() {
		this.eventDispatcher.stop();
		super.dispose();
	}

	/**
	 * {@inheritDoc}
	 */
	public void eventProcessed(XEvent e) {
		DeviceEvent event;
		switch(e.get_type()) {
		case XConstants.KeyPress:
			if (isKeyboardEventFired()) {
				event = new DeviceEvent(this);
				if (treatNativeEvent(e.getPData(), event)) {
					fireKeyPressed(event);
				}
			}
			break;
		case XConstants.KeyRelease:
			if (isKeyboardEventFired()) {
				event = new DeviceEvent(this);
				if (treatNativeEvent(e.getPData(), event)) {
					fireKeyReleased(event);
				}
			}
			break;
		case XConstants.ClientMessage:
			event = new DeviceEvent(this);
			if (treatNativeEvent(e.getPData(), event)) {
				this.eventDispatcher.offer(event);
			}
			break;
		}
	}

	/**
	 * Dispatch 3DxWare events.
	 * 
	 * @author St&eacute;phane GALLAND &lt;galland@arakhne.org&gt;
	 * @version $Name$ $Revision$ $Date$
	 */
	private class EventDispatcher implements Runnable {

		private volatile boolean mustStop;
		
		private final Queue<DeviceEvent> queue = new ConcurrentLinkedQueue<DeviceEvent>();
		
		/**
		 */
		public EventDispatcher() {
			//
		}
		
		/** Offer an event for dispatching.
		 *
		 * @param event
		 */
		public void offer(DeviceEvent event) {
			this.queue.offer(event);
		}

		/**
		 * {@inheritDoc}
		 */
		public void run() {
			DeviceEvent event;
			this.mustStop = false;
			while (!this.mustStop) {
				event = this.queue.poll();
				if (event!=null) {
					switch(event.getType()) {
					case BUTTON3D_PRESSED:
						fireButton3DPressed(event);
						break;
					case BUTTON3D_RELEASED:
						fireButton3DReleased(event);
						break;
					case MOUSE3D_MOTION:
						fireMouse3DMotion(event);
						break;
					default:
					}
				}
				Thread.yield();
			}
		}
		
		/** Start the dispatcher.
		 */
		public void start() {
			Thread thread = Executors.defaultThreadFactory().newThread(this);
			thread.setName("XSpaceMouse Event Dispatcher"); //$NON-NLS-1$
			thread.start();
		}

		/** Stop the dispatcher.
		 */
		public void stop() {
			this.mustStop = true;
		}
		
	}
	
}
