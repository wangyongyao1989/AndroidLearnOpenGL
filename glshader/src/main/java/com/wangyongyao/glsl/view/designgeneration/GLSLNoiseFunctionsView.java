package com.wangyongyao.glsl.view.designgeneration;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;

import com.wangyongyao.glsl.GLSLADCallJni;
import com.wangyongyao.glsl.GLSLDGCallJni;
import com.wangyongyao.glsl.util.GLSLShowUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2025/2/20
 * Descibe : AndroidLearnOpenGL com.wangyongyao.glsl.view
 * 着色器——生成设计：噪音
 */
public class GLSLNoiseFunctionsView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GLSLNoiseFunctionsView.class.getSimpleName();
    private GLSLDGCallJni mJniCall;
    private Context mContext;
    private int TYPE_MODE = 13;


    private float downX;
    private float downY;

    public GLSLNoiseFunctionsView(Context context, GLSLDGCallJni jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GLSLNoiseFunctionsView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String vertexPath = GLSLShowUtil.getModelFilePath(mContext, "shaping_function_vert.glsl");
        String fragPath1 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment1.glsl");
        String fragPath2 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment2.glsl");
        String fragPath3 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment3.glsl");
        String fragPath4 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment4.glsl");
        String fragPath5 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment5.glsl");
        String fragPath6 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment6.glsl");
        String fragPath7 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment7.glsl");

        String fragPath8 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment8.glsl");
        String fragPath9 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment9.glsl");
        String fragPath10 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment10.glsl");
        String fragPath11 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment11.glsl");
        String fragPath12 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment12.glsl");
        String fragPath13 = GLSLShowUtil.getModelFilePath(mContext, "noise_function_fragment13.glsl");

        if (mJniCall != null)
            mJniCall.setNoiseFunctionsPath(vertexPath
                    , fragPath1
                    , fragPath2
                    , fragPath3
                    , fragPath4
                    , fragPath5
                    , fragPath6
                    , fragPath7
                    , fragPath8
                    , fragPath9
                    , fragPath10
                    , fragPath11
                    , fragPath12
                    , fragPath13

            );

        setRenderer(this);
    }


    public void onDrawFrame(GL10 gl) {
//        Log.e(TAG, "onDrawFrame: ");
        if (mJniCall != null)
            mJniCall.onNoiseFunctionsRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.e(TAG, "onSurfaceChanged: ");
        if (mJniCall != null)
            mJniCall.initNoiseFunctions(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }

    public void setType(int typeSF) {
        int typeVaule = typeSF % TYPE_MODE;
        if (mJniCall != null) {
            mJniCall.setTypeNoiseFunctions(typeVaule);
        }
    }

    public int getType() {
        if (mJniCall != null) {
            return mJniCall.getTypeNoiseFunctions();
        } else {
            return 0;
        }
    }


    @Override
    public boolean onTouchEvent(MotionEvent event) {

        switch (event.getAction()) {

            case MotionEvent.ACTION_DOWN: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                downX = event.getX();
                downY = event.getY();
                mJniCall.MoveXYNoiseFunctions(0, 0, 1);
            }
            break;
            case MotionEvent.ACTION_MOVE: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                float dx = event.getX();
                float dy = event.getY();
//                Log.e(TAG, "ACTION_MOVE:dx= "
//                        + dx + "==dy:" + dy);
                mJniCall.MoveXYNoiseFunctions(dx, dy, 2);
            }
            break;
            case MotionEvent.ACTION_UP: {
//                Log.e(TAG, "onTouchEvent: " + event.getAction());
                downX = 0;
                downY = 0;
                mJniCall.MoveXYNoiseFunctions(0, 0, 3);
            }
            break;
        }


        return true;
    }

}