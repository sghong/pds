package com.qeexo.fingersensedemo;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.RectF;
import android.util.AttributeSet;
import android.util.DisplayMetrics;
import android.view.MotionEvent;
import android.view.View;

@SuppressLint("UseSparseArrays")
public class FingerSenseView extends View {
	public FingerSenseView(Context context) {
		super(context);
	}

	public FingerSenseView(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	public FingerSenseView(Context context, AttributeSet attrs, int defStyle) {
		super(context, attrs, defStyle);
	}

	// DPI scaling. Sizes are specified as if on the S3 (xhdpi, 320 DPI)
	private float dpiScale = getResources().getDisplayMetrics().density * DisplayMetrics.DENSITY_DEFAULT / DisplayMetrics.DENSITY_XHIGH;

	static final float SPOT_RADIUS = 120;

	private final Map<Integer, MotionEvent> touchMap = new HashMap<Integer, MotionEvent>();
	private final Map<Integer, MotionEvent> deferredPaintMap = new HashMap<Integer, MotionEvent>();
	private static final Map<TouchKind, String> touchNames = new HashMap<TouchKind, String>();
	private static final Map<TouchKind, Paint> paintBrushes = new HashMap<TouchKind, Paint>();
	private static final Paint defaultPaintBrush;
	private final Object touchMapLock = new Object();
	private final RectF touchDrawRect = new RectF();
	
	private static final Paint textPaint;
	
	static {
		textPaint = new Paint();
		textPaint.setColor(Color.BLACK);
		textPaint.setTextSize(80);
		textPaint.setStyle(Style.FILL_AND_STROKE);

		Paint paint;
		
		paint = new Paint();
		paint.setColor(Color.RED);
		paintBrushes.put(TouchKind.PAD, paint);
		touchNames.put(TouchKind.PAD, "finger");

		paint = new Paint();
		paint.setColor(Color.GREEN);
		paintBrushes.put(TouchKind.NAIL, paint);
		touchNames.put(TouchKind.NAIL, "nail");

		paint = new Paint();
		paint.setColor(Color.BLUE);
		paintBrushes.put(TouchKind.KNUCKLE, paint);
		touchNames.put(TouchKind.KNUCKLE, "knuckle");

		paint = new Paint();
		paint.setColor(Color.YELLOW);
		paintBrushes.put(TouchKind.STYLUS_1, paint);
		touchNames.put(TouchKind.STYLUS_1, "stylus");

		paint = new Paint();
		paint.setColor(Color.MAGENTA);
		paintBrushes.put(TouchKind.BEZEL, paint);
		touchNames.put(TouchKind.BEZEL, "bezel");

		paint = new Paint();
		paint.setColor(Color.GRAY);
		paint.setStyle(Style.STROKE);
		paintBrushes.put(TouchKind.UNKNOWN, paint);
		touchNames.put(TouchKind.UNKNOWN, "unknown");

		defaultPaintBrush = new Paint();
		defaultPaintBrush.setColor(Color.GRAY);
	}

	private void drawMotionEvent(Canvas canvas, Integer id, MotionEvent event) {
		int pointerIndex = event.findPointerIndex(id);
		float x = event.getX(pointerIndex);
		float y = event.getY(pointerIndex);
		float axisTouchKind = event.getAxisValue(FingerSenseActivity.AXIS_TOUCH_KIND, pointerIndex);
		TouchKind touchKind = TouchKind.fromInteger((int) axisTouchKind);
		
		Paint paint;

		canvas.save();
		canvas.translate(x, y);
		canvas.scale(dpiScale, dpiScale);
		
		touchDrawRect.set(-SPOT_RADIUS, -SPOT_RADIUS, SPOT_RADIUS, SPOT_RADIUS);
		paint = paintBrushes.get(touchKind);
		if(paint == null) paint = defaultPaintBrush;
		canvas.drawOval(touchDrawRect, paint);
		if(touchKind != TouchKind.UNKNOWN) {
			String touchStr = touchNames.get(touchKind);
			if(touchStr == null) touchStr = touchKind.toDisplayName();
			float width = textPaint.measureText(touchStr);
			canvas.drawText(touchStr, -width/2, -SPOT_RADIUS-30, textPaint);
		}
		canvas.restore();
	}

	@Override
	protected void onDraw(Canvas canvas) {
		canvas.drawRGB(255, 255, 255);

		synchronized(touchMapLock) {
			for(Entry<Integer, MotionEvent> im : deferredPaintMap.entrySet()) {
				drawMotionEvent(canvas, im.getKey(), im.getValue());
			}
			for(Entry<Integer, MotionEvent> im : deferredPaintMap.entrySet()) {
				if(touchMap.containsKey(im.getKey()))
					continue;
				drawMotionEvent(canvas, im.getKey(), im.getValue());
				invalidate();
			}
		}
		canvas.save();
		canvas.scale(dpiScale, dpiScale);
		canvas.restore();
	}

    public void onTouchDown(int id, MotionEvent event) {
    	synchronized(touchMapLock) {
    		if(event.findPointerIndex(id) < 0) {
    			return;
    		}
			touchMap.put(id, event);
			deferredPaintMap.put(id, event);
    	}
		postInvalidate();
    }

    public void onTouchMove(int id, MotionEvent event) {
    	onTouchDown(id, event);
    }

    public void onTouchUp(int id) {
    	synchronized(touchMapLock) {
    		touchMap.remove(id);
    		deferredPaintMap.remove(id);
    	}
		postInvalidate();
    }

	public void clearTouchMap() {
		synchronized(touchMapLock) {
			touchMap.clear();
			deferredPaintMap.clear();
		}
		postInvalidate();
	}
	
}
