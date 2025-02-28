package com.wangyongyao.glsl.view.designgeneration;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.wangyongyao.glsl.GLSLADCallJni;
import com.wangyongyao.glsl.GLSLDGCallJni;
import com.wangyongyao.glsl.util.GLSLShowUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Descibe : AndroidLearnOpenGL com.wangyongyao.glsl.view
 * 着色器图案
 */
public class GLSLRandomFunctionsView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GLSLRandomFunctionsView.class.getSimpleName();
    private GLSLDGCallJni mJniCall;
    private Context mContext;
    private int TYPE_MODE = 4;

    public GLSLRandomFunctionsView(Context context, GLSLDGCallJni jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GLSLRandomFunctionsView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String vertexPath = GLSLShowUtil.getModelFilePath(mContext, "shaping_function_vert.glsl");
        String fragPath1 = GLSLShowUtil.getModelFilePath(mContext, "patterns_function_fragment1.glsl");
        String fragPath2 = GLSLShowUtil.getModelFilePath(mContext, "patterns_function_fragment2.glsl");
        String fragPath3 = GLSLShowUtil.getModelFilePath(mContext, "patterns_function_fragment3.glsl");
        String fragPath4 = GLSLShowUtil.getModelFilePath(mContext, "patterns_function_fragment4.glsl");

        if (mJniCall != null)
            mJniCall.setRandomPath(vertexPath
                    , fragPath1
                    , fragPath2
                    , fragPath3
                    , fragPath4
            );

        setRenderer(this);
    }


    public void onDrawFrame(GL10 gl) {
//        Log.e(TAG, "onDrawFrame: ");
        if (mJniCall != null)
            mJniCall.onRandomRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.e(TAG, "onSurfaceChanged: ");
        if (mJniCall != null)
            mJniCall.initRandom(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }

    public void setType(int typeSF) {
        int typeVaule = typeSF % TYPE_MODE;
        if (mJniCall != null) {
            mJniCall.setTypeRandom(typeVaule);
        }
    }

    public int getType() {
        if (mJniCall != null) {
            return mJniCall.getTypeRandom();
        } else {
            return 0;
        }
    }
}