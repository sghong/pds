package com.qeexo.fingersensedemo;

import java.util.HashMap;
import java.util.Map;

/** The FingerSense touch type
 * 
 * @author brx
 *
 */
public enum TouchKind {
	/* This file must be kept in sync with touch.h */
	/** Finger pad (or finger with the FS classifier) */
	PAD,
	/** Fingertip
	 */
	TIP,
	/** Fingernail */
	NAIL,
	/** Knuckle (or alternate tap) */
	KNUCKLE,
	/** @deprecated */
	ALT_HAND_1, // e.g. fist
	/** @deprecated */
	ALT_HAND_2, // e.g. palm
	/** @deprecated */
	BRUSH_1, // e.g. long brush
	/** @deprecated */
	BRUSH_2, // e.g. short brush
	/** Metallic stylus */
	STYLUS_1, // e.g. hard stylus

	STYLUS_2, // e.g. soft stylus
	/** Rubber eraser */
	ERASER,
	/** Unknown touch kind */
	UNKNOWN,
	/** Bezel */
	BEZEL;
	
	public boolean matches(TouchKind o)
	{
		if(!(o instanceof TouchKind)) return false;
		if(o == TouchKind.TIP && this == TouchKind.PAD
				|| this == TouchKind.TIP && o == TouchKind.PAD) return true;
		return o == this;
	}
	
	@Override
	public String toString() {
		return super.toString().toLowerCase();
	}
	
	public String toDisplayName() {
		if(this == TIP) {
			return "fingertip";
		}
		return this.toString().toLowerCase().replace('_', ' ');
	}
	
	public int toInteger() {
		return touchKindMap.get(this);
	}
	
	static final TouchKind[] touchKinds = TouchKind.class.getEnumConstants();
	static final Map<TouchKind, Integer> touchKindMap = new HashMap<TouchKind, Integer>();
	
	public static TouchKind fromInteger(int touch_class) {
		if(touch_class < 0 || touch_class >= touchKinds.length)
			return UNKNOWN;
		return touchKinds[touch_class];
	}
	
	public static int touchKindSize() {
		return touchKinds.length;
	}

	static {
		for(int i=0; i<touchKinds.length; i++) {
			touchKindMap.put(touchKinds[i], i);
		}
	}
}
