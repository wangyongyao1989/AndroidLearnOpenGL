package com.wangyongyao.androidlearnopengl.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

import com.wangyongyao.androidlearnopengl.JniCall;
import com.wangyongyao.androidlearnopengl.utils.OpenGLUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLDiffuseMapView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private GestureDetector gestureDetector;
    private ScaleGestureDetector scaleGestureDetector;

    private static String TAG = GLDiffuseMapView.class.getSimpleName();
    private JniCall mJniCall;
    private Context mContext;
    private boolean isScaleGesture;

    private float downX;
    private float downY;


    public GLDiffuseMapView(Context context, JniCall jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GLDiffuseMapView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String fragPath = OpenGLUtil.getModelFilePath(mContext, "diffuse_map_cube_fragment.glsl");
        String vertexPath = OpenGLUtil.getModelFilePath(mContext, "diffuse_map_cube_vertex.glsl");
        String colorFragPath = OpenGLUtil.getModelFilePath(mContext, "diffuse_map_color_fragment.glsl");
        String colorVertexPath = OpenGLUtil.getModelFilePath(mContext, "diffuse_map_color_vertex.glsl");
        String picSrc1 = OpenGLUtil.getModelFilePath(mContext, "diffuse_map_container2.png");
        String picSrc2 = OpenGLUtil.getModelFilePath(mContext, "awesomeface.png");

        if (mJniCall != null) {
            mJniCall.setDiffuseMapGLSLPath(colorFragPath, colorVertexPath, picSrc1, picSrc2);
            mJniCall.setDiffuseMapColorGLSLPath(fragPath, vertexPath);
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
                mJniCall.diffuseMapOnScale(scaleFactor, detector.getFocusX()
                        , detector.getFocusY(), 2);
                return true;
            }

            @Override
            public boolean onScaleBegin(ScaleGestureDetector detector) {
                // 开始缩放事件
//                Log.e(TAG, "onScaleBegin: " + detector);
                mJniCall.diffuseMapOnScale(detector.getScaleFactor(), detector.getFocusX()
                        , detector.getFocusY(), 1);
                return true;
            }

            @Override
            public void onScaleEnd(ScaleGestureDetector detector) {
                // 结束缩放事件
//                Log.e(TAG, "onScaleEnd: " + detector);
                mJniCall.diffuseMapOnScale(detector.getScaleFactor(), detector.getFocusX()
                        , detector.getFocusY(), 3);
                isScaleGesture = false;
            }
        });
    }


    public void onDrawFrame(GL10 gl) {
        if (mJniCall != null)
            mJniCall.diffuseMapOpenGLRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        if (mJniCall != null)
            mJniCall.initDiffuseMapOpenGl(width, height);
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
                mJniCall.diffuseMapMoveXY(0, 0, 1);
            }
            break;
            case MotionEvent.ACTION_MOVE: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                float dx = event.getX() - downX;
                float dy = event.getY() - downY;
//                Log.e(TAG, "ACTION_MOVE:dx= "
//                        + dx + "==dy:" + dy);
                mJniCall.diffuseMapMoveXY(dx, dy, 2);
            }
            break;
            case MotionEvent.ACTION_UP: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                downX = 0;
                downY = 0;
                mJniCall.diffuseMapMoveXY(0, 0, 3);
            }
            break;
        }


        return true;
    }


}
