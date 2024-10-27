package com.wangyongyao.gl3d.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;


import com.wangyongyao.gl3d.GL3DCallJni;
import com.wangyongyao.gl3d.utils.GL3DShowUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GL3DFlashLightView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private GestureDetector gestureDetector;
    private ScaleGestureDetector scaleGestureDetector;

    private static String TAG = GL3DFlashLightView.class.getSimpleName();
    private GL3DCallJni mGL3DCallJni;
    private Context mContext;
    private boolean isScaleGesture;

    private float downX;
    private float downY;


    public GL3DFlashLightView(Context context, GL3DCallJni jniCall) {
        super(context);
        mContext = context;
        mGL3DCallJni = jniCall;
        init();
    }

    public GL3DFlashLightView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String fragPath = GL3DShowUtil.getModelFilePath(mContext, "flash_light_cube_fragment.glsl");
        String vertexPath = GL3DShowUtil.getModelFilePath(mContext, "flash_light_cube_vertex.glsl");
        String colorFragPath = GL3DShowUtil.getModelFilePath(mContext, "flash_light_color_fragment.glsl");
        String colorVertexPath = GL3DShowUtil.getModelFilePath(mContext, "flash_light_color_vertex.glsl");
        String picSrc1 = GL3DShowUtil.getModelFilePath(mContext, "diffuse_map_container2.png");
        String picSrc2 = GL3DShowUtil.getModelFilePath(mContext, "specular_container2.png");

        if (mGL3DCallJni != null) {
            mGL3DCallJni.setFlashLightGLSLPath(colorFragPath, colorVertexPath, picSrc1, picSrc2);
            mGL3DCallJni.setFlashLightColorGLSLPath(fragPath, vertexPath);
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
                mGL3DCallJni.flashLightOnScale(scaleFactor, detector.getFocusX()
                        , detector.getFocusY(), 2);
                return true;
            }

            @Override
            public boolean onScaleBegin(ScaleGestureDetector detector) {
                // 开始缩放事件
//                Log.e(TAG, "onScaleBegin: " + detector);
                mGL3DCallJni.flashLightOnScale(detector.getScaleFactor(), detector.getFocusX()
                        , detector.getFocusY(), 1);
                return true;
            }

            @Override
            public void onScaleEnd(ScaleGestureDetector detector) {
                // 结束缩放事件
//                Log.e(TAG, "onScaleEnd: " + detector);
                mGL3DCallJni.flashLightOnScale(detector.getScaleFactor(), detector.getFocusX()
                        , detector.getFocusY(), 3);
                isScaleGesture = false;
            }
        });
    }


    public void onDrawFrame(GL10 gl) {
        if (mGL3DCallJni != null)
            mGL3DCallJni.flashLightOpenGLRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        if (mGL3DCallJni != null)
            mGL3DCallJni.initFlashLightOpenGl(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

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
                mGL3DCallJni.flashLightMoveXY(0, 0, 1);
            }
            break;
            case MotionEvent.ACTION_MOVE: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                float dx = event.getX() - downX;
                float dy = event.getY() - downY;
//                Log.e(TAG, "ACTION_MOVE:dx= "
//                        + dx + "==dy:" + dy);
                mGL3DCallJni.flashLightMoveXY(dx, dy, 2);
            }
            break;
            case MotionEvent.ACTION_UP: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                downX = 0;
                downY = 0;
                mGL3DCallJni.flashLightMoveXY(0, 0, 3);
            }
            break;
        }


        return true;
    }


}
