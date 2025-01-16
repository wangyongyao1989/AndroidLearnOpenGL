package com.wangyongyao.views;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

import com.wangyongyao.GLSeniorCallJni;
import com.wangyongyao.utils.GLSeniorUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2025/1/16
 * Descibe : AndroidLearnOpenGL com.wangyongyao.views
 */
public class GLFBOPostProcessingView extends GLSurfaceView implements GLSurfaceView.Renderer {
    private static String TAG = GLFBOPostProcessingView.class.getSimpleName();

    private GestureDetector gestureDetector;
    private ScaleGestureDetector scaleGestureDetector;
    
    private GLSeniorCallJni mJniCall;
    private Context mContext;
    private boolean isScaleGesture;

    private float downX;
    private float downY;
    private int mWidth;
    private int mHeight;

    public GLFBOPostProcessingView(Context context, GLSeniorCallJni jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GLFBOPostProcessingView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String fragPath = GLSeniorUtil.getModelFilePath(mContext, "fbo_fragment.glsl");
        String vertexPath = GLSeniorUtil.getModelFilePath(mContext, "fbo_vertex.glsl");


        String picSrc1 = GLSeniorUtil.getModelFilePath(mContext, "diffuse_map_container2.png");
        String picSrc2 = GLSeniorUtil.getModelFilePath(mContext, "metal.png");

        String fragScreenPath = GLSeniorUtil.getModelFilePath(mContext, "fbo_screen_fragment.glsl");
        String vertexScreenPath = GLSeniorUtil.getModelFilePath(mContext, "fbo_screen_vertex.glsl");

        mJniCall.glFBOPostProcessingCreate(0
                , vertexPath, fragPath
                , picSrc1, picSrc2
                , vertexScreenPath, fragScreenPath
        );

        setRenderer(this);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);

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
                mJniCall.glFBOPostOnScale(scaleFactor, detector.getFocusX()
                        , detector.getFocusY(), 2);
                return true;
            }

            @Override
            public boolean onScaleBegin(ScaleGestureDetector detector) {
                // 开始缩放事件
//                Log.e(TAG, "onScaleBegin: " + detector);
                mJniCall.glFBOPostOnScale(detector.getScaleFactor(), detector.getFocusX()
                        , detector.getFocusY(), 1);
                return true;
            }

            @Override
            public void onScaleEnd(ScaleGestureDetector detector) {
                // 结束缩放事件
//                Log.e(TAG, "onScaleEnd: " + detector);
                mJniCall.glFBOPostOnScale(detector.getScaleFactor(), detector.getFocusX()
                        , detector.getFocusY(), 3);
                isScaleGesture = false;
            }
        });
    }

    public void setFBOPostProcessingType(int type) {
        int typeVaule = type % 13;
        if (mJniCall != null) {
            mJniCall.glFBOPostProcessingSetParameters(typeVaule);
        }
    }

    public int getFBOPostProcessingType() {
        int type = 0;
        if (mJniCall != null) {
            type = mJniCall.glFBOPostProcessingGetParameters();
        }
        return type;
    }


    public void onDrawFrame(GL10 gl) {
        if (mJniCall != null) {
            mJniCall.glFBOPostProcessingRender();
        }

    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.e(TAG, "onSurfaceChanged width:" + width + ",height" + height);
        if (mJniCall != null) {
            mJniCall.glFBOPostProcessingInit(null, null, width, height);
        }
        mWidth = width;
        mHeight = height;
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        Log.e(TAG, "onSurfaceCreated:");


    }

    public void destroyRender() {
        mJniCall.glFBOPostProcessingDestroy();

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
                mJniCall.glFBOPostMoveXY(0, 0, 1);
            }
            break;
            case MotionEvent.ACTION_MOVE: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                float dx = event.getX() - downX;
                float dy = event.getY() - downY;
//                Log.e(TAG, "ACTION_MOVE:dx= "
//                        + dx + "==dy:" + dy);
                mJniCall.glFBOPostMoveXY(dx, dy, 2);
            }
            break;
            case MotionEvent.ACTION_UP: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                downX = 0;
                downY = 0;
                mJniCall.glFBOPostMoveXY(0, 0, 3);
            }
            break;
        }


        return true;
    }

}
