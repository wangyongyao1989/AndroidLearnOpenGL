package com.wangyongyao.views;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

import com.wangyongyao.GLSeniorCallJni;
import com.wangyongyao.utils.GLSeniorUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLCubeMapReflectionView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private GestureDetector gestureDetector;
    private ScaleGestureDetector scaleGestureDetector;

    private static String TAG = GLCubeMapReflectionView.class.getSimpleName();
    private GLSeniorCallJni mGLSeniorCallJni;
    private Context mContext;
    private boolean isScaleGesture;

    private float downX;
    private float downY;


    public GLCubeMapReflectionView(Context context, GLSeniorCallJni jniCall) {
        super(context);
        mContext = context;
        mGLSeniorCallJni = jniCall;
        init();
    }

    public GLCubeMapReflectionView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String fragPath = GLSeniorUtil.getModelFilePath(mContext, "reflection_fragment.glsl");
        String vertexPath = GLSeniorUtil.getModelFilePath(mContext, "reflection_vertex.glsl");
        String picSrc1 = GLSeniorUtil.getModelFilePath(mContext, "diffuse_map_container2.png");
        String picSrc2 = GLSeniorUtil.getModelFilePath(mContext, "skybox_right.jpg");
        String picSrc3 = GLSeniorUtil.getModelFilePath(mContext, "skybox_left.jpg");
        String picSrc4 = GLSeniorUtil.getModelFilePath(mContext, "skybox_top.jpg");
        String picSrc5 = GLSeniorUtil.getModelFilePath(mContext, "skybox_bottom.jpg");
        String picSrc6 = GLSeniorUtil.getModelFilePath(mContext, "skybox_front.jpg");
        String picSrc7 = GLSeniorUtil.getModelFilePath(mContext, "skybox_back.jpg");

        String fragScreenPath = GLSeniorUtil.getModelFilePath(mContext, "reflection_skybox_fragment.glsl");
        String vertexScreenPath = GLSeniorUtil.getModelFilePath(mContext, "reflection_skybox_vertex.glsl");

        if (mGLSeniorCallJni != null) {
            mGLSeniorCallJni.setReflectionGLSLPath(fragPath, vertexPath, fragScreenPath,
                    vertexScreenPath, picSrc1, picSrc2
                    , picSrc3, picSrc4
                    , picSrc5, picSrc6
                    , picSrc7
            );
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
                mGLSeniorCallJni.reflectionOnScale(scaleFactor, detector.getFocusX()
                        , detector.getFocusY(), 2);
                return true;
            }

            @Override
            public boolean onScaleBegin(ScaleGestureDetector detector) {
                // 开始缩放事件
//                Log.e(TAG, "onScaleBegin: " + detector);
                mGLSeniorCallJni.reflectionOnScale(detector.getScaleFactor(), detector.getFocusX()
                        , detector.getFocusY(), 1);
                return true;
            }

            @Override
            public void onScaleEnd(ScaleGestureDetector detector) {
                // 结束缩放事件
//                Log.e(TAG, "onScaleEnd: " + detector);
                mGLSeniorCallJni.reflectionOnScale(detector.getScaleFactor(), detector.getFocusX()
                        , detector.getFocusY(), 3);
                isScaleGesture = false;
            }
        });
    }


    public void onDrawFrame(GL10 gl) {
        if (mGLSeniorCallJni != null)
            mGLSeniorCallJni.reflectionOpenGLRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        if (mGLSeniorCallJni != null)
            mGLSeniorCallJni.initReflectionOpenGl(width, height);
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
                mGLSeniorCallJni.reflectionMoveXY(0, 0, 1);
            }
            break;
            case MotionEvent.ACTION_MOVE: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                float dx = event.getX() - downX;
                float dy = event.getY() - downY;
//                Log.e(TAG, "ACTION_MOVE:dx= "
//                        + dx + "==dy:" + dy);
                mGLSeniorCallJni.reflectionMoveXY(dx, dy, 2);
            }
            break;
            case MotionEvent.ACTION_UP: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                downX = 0;
                downY = 0;
                mGLSeniorCallJni.reflectionMoveXY(0, 0, 3);
            }
            break;
        }


        return true;
    }


}
