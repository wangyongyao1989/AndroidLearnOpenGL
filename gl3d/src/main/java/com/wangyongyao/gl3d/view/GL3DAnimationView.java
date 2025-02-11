package com.wangyongyao.gl3d.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

import com.wangyongyao.gl3d.GL3DCallJni;
import com.wangyongyao.gl3d.utils.GL3DShowUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2025/2/10 
 * Descibe : AndroidLearnOpenGL com.wangyongyao.gl3d.view
 */
public class GL3DAnimationView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GL3DShowView.class.getSimpleName();
    private GL3DCallJni mJniCall;
    private Context mContext;
    private boolean isScaleGesture;
    private GestureDetector gestureDetector;
    private ScaleGestureDetector scaleGestureDetector;
    private float downX;
    private float downY;

    public GL3DAnimationView(Context context, GL3DCallJni jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GL3DAnimationView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String fragPath = GL3DShowUtil.getModelFilePath(mContext
                , "gl_3d_animation_fragment.glsl");
        String vertexPath = GL3DShowUtil.getModelFilePath(mContext
                , "gl_3d_animation_vertex.glsl");

        if (mJniCall != null) {
            mJniCall.setGL3DAnimationSLPath(fragPath, vertexPath);
        }

        setRenderer(this);

        gestureDetector = new GestureDetector(getContext(), new GestureDetector.SimpleOnGestureListener());
        scaleGestureDetector = new ScaleGestureDetector(getContext()
                , new ScaleGestureDetector.OnScaleGestureListener() {
            @Override
            public boolean onScale(ScaleGestureDetector detector) {
                // 处理缩放事件
                float scaleFactor = detector.getScaleFactor();
//                Log.e(TAG, "onScale scaleFactor: " + scaleFactor
//                        + "==getFocusX:" + detector.getFocusX()
//                        + "===getFocusY" + detector.getFocusY());
                mJniCall.gl3DAnimationShowOnScale(scaleFactor, detector.getFocusX()
                        , detector.getFocusY(), 2);
                return true;
            }

            @Override
            public boolean onScaleBegin(ScaleGestureDetector detector) {
                // 开始缩放事件
//                Log.e(TAG, "onScaleBegin: " + detector);
                mJniCall.gl3DAnimationShowOnScale(detector.getScaleFactor(), detector.getFocusX()
                        , detector.getFocusY(), 1);
                return true;
            }

            @Override
            public void onScaleEnd(ScaleGestureDetector detector) {
                // 结束缩放事件
//                Log.e(TAG, "onScaleEnd: " + detector);
                mJniCall.gl3DAnimationShowOnScale(detector.getScaleFactor(), detector.getFocusX()
                        , detector.getFocusY(), 3);
                isScaleGesture = false;
            }
        });
    }


    public void onDrawFrame(GL10 gl) {
//        Log.e(TAG, "onDrawFrame: ");
        if (mJniCall != null)
            mJniCall.gl3DAnimationRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.e(TAG, "onSurfaceChanged: ");
        if (mJniCall != null)
            mJniCall.init3DAnimation(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        String modelPath = GL3DShowUtil.getModelFilePath(mContext
                , "dancing_vampire.dae");
        if (mJniCall != null)
            mJniCall.setGL3DAnimationModelPath(modelPath);

    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {
        if (isScaleGesture) {
            gestureDetector.onTouchEvent(event);
            scaleGestureDetector.onTouchEvent(event);
            return true;
        }
        switch (event.getAction()) {
            case MotionEvent.ACTION_POINTER_2_DOWN: {
                isScaleGesture = true;
            }
            break;
            case MotionEvent.ACTION_POINTER_2_UP: {
                isScaleGesture = false;
            }
            break;
            case MotionEvent.ACTION_DOWN: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                downX = event.getX();
                downY = event.getY();
                mJniCall.gl3DAnimationShowMoveXY(0, 0, 1);
            }
            break;
            case MotionEvent.ACTION_MOVE: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                float dx = event.getX() - downX;
                float dy = event.getY() - downY;
                Log.e(TAG, "ACTION_MOVE:dx= "
                        + dx + "==dy:" + dy);
                mJniCall.gl3DAnimationShowMoveXY(dx, dy, 2);
            }
            break;
            case MotionEvent.ACTION_UP: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                downX = 0;
                downY = 0;
                mJniCall.gl3DAnimationShowMoveXY(0, 0, 3);
            }
            break;
        }
        return true;
    }

}