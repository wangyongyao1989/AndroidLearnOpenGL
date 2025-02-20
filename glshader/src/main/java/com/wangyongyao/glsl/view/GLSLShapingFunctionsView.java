package com.wangyongyao.glsl.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.wangyongyao.glsl.GLSLCallJni;
import com.wangyongyao.glsl.util.GLSLShowUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * author : wangyongyao https://github.com/wangyongyao1989
 * Create Time : 2025/2/20
 * Descibe : AndroidLearnOpenGL com.wangyongyao.glsl.view
 * 着色器造型函数
 */
public class GLSLShapingFunctionsView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GLSLShapingFunctionsView.class.getSimpleName();
    private GLSLCallJni mJniCall;
    private Context mContext;

    public GLSLShapingFunctionsView(Context context, GLSLCallJni jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GLSLShapingFunctionsView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String vertexPath = GLSLShowUtil.getModelFilePath(mContext, "rectangle_uniform_vertex.glsl");
        String fragPath = GLSLShowUtil.getModelFilePath(mContext, "rectangle_uniform_fragment.glsl");
        if (mJniCall != null)
            mJniCall.setShapingFunctionsPath(vertexPath, fragPath);
        setRenderer(this);
    }


    public void onDrawFrame(GL10 gl) {
        Log.e(TAG, "onDrawFrame: ");
        if (mJniCall != null)
            mJniCall.onShapingFunctionsRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.e(TAG, "onSurfaceChanged: ");
        if (mJniCall != null)
            mJniCall.initShapingFunctions(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }


}