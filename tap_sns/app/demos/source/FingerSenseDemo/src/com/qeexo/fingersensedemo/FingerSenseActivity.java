package com.qeexo.fingersensedemo;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.Window;
import android.view.WindowManager;

public class FingerSenseActivity extends Activity {
	public static final String APPNAME = "FingerSenseDemo";
	
	// NOTE: In order to avoid breaking the Android API, we are using the existing AMOTION_EVENT_AXIS_GAS
	// constant as a temporary axis value to provide the touch kind to Java applications.
	// In the future, once we know we can modify the API, we can use the tool type to represent
	// this information.
	public static final int AXIS_TOUCH_KIND = MotionEvent.AXIS_GAS;
	
	private FingerSenseView touchView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
		setContentView(R.layout.activity_finger_sense_demo);
		
        touchView = new FingerSenseView(this);
        setContentView(touchView);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.finger_sense_demo, menu);
		return true;
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		final int action = event.getAction();
		
	    switch (action & MotionEvent.ACTION_MASK) {
		    case MotionEvent.ACTION_DOWN: {
		    	touchView.onTouchDown(0, event);
		    	break;
		    }
		    case MotionEvent.ACTION_MOVE: {
		    	for(int i = 0; i < event.getPointerCount(); ++i) {
		    		touchView.onTouchMove(event.getPointerId(i), event);
		    	}
		    	break;
		    }
		    case MotionEvent.ACTION_UP: {
		    	touchView.clearTouchMap();
		    	break;
		    }
		    case MotionEvent.ACTION_POINTER_DOWN: {
		    	// Extract the index of the pointer that touched the screen
		    	int index = (action & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
		    	touchView.onTouchDown(event.getPointerId(index), event);
		    	break;
		    }
		    case MotionEvent.ACTION_POINTER_UP: {
		    	// Extract the index of the pointer that left the touch sensor
		    	int index = (action & MotionEvent.ACTION_POINTER_INDEX_MASK) >> MotionEvent.ACTION_POINTER_INDEX_SHIFT;
		    	touchView.onTouchUp(event.getPointerId(index));
		    	break;
		    }
	    }

		return super.onTouchEvent(event);
	}
	
}
