package com.wangyongyao.glfoundation.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;


import com.wangyongyao.glfoundation.GLFounationJniCall;
import com.wangyongyao.glfoundation.utils.OpenGLFoundationUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GL3FoundationView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GL3FoundationView.class.getSimpleName();
    private GLFounationJniCall mJniCall;
    private Context mContext;

    public GL3FoundationView(Context context, GLFounationJniCall jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GL3FoundationView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        //1、顶点及片段着色器的出入使用
//        String fragPath = OpenGLFoundationUtil.getModelFilePath(mContext, "triangle_shape_fragment.glsl");
//        String vertexPath = OpenGLFoundationUtil.getModelFilePath(mContext, "triangle_shape_vertex.glsl");
        //2、in及out属性的使用
//        String fragPath = OpenGLFoundationUtil.getModelFilePath(mContext, "rectangle_shape_rad_fragment.glsl");
//        String vertexPath = OpenGLFoundationUtil.getModelFilePath(mContext, "rectangle_shape_rad_vertex.glsl");
        //3、uniform的使用
        String fragPath = OpenGLFoundationUtil.getModelFilePath(mContext, "rectangle_uniform_fragment.glsl");
        String vertexPath = OpenGLFoundationUtil.getModelFilePath(mContext, "rectangle_uniform_vertex.glsl");
        if (mJniCall != null)
            mJniCall.setFoundationGLSLPath(fragPath, vertexPath);
        setRenderer(this);
    }


    public void onDrawFrame(GL10 gl) {
        Log.e(TAG, "onDrawFrame: ");
        if (mJniCall != null)
            mJniCall.openFoundationGlRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.e(TAG, "onSurfaceChanged: ");
        if (mJniCall != null)
            mJniCall.initFoundationOpenGl(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }


}
