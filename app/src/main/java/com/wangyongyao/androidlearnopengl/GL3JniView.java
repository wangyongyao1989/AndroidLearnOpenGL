package com.wangyongyao.androidlearnopengl;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.wangyongyao.androidlearnopengl.utils.OpenGLUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GL3JniView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GL3JniView.class.getSimpleName();
    private JniCall mJniCall;
    private Context mContext;

    public GL3JniView(Context context) {
        super(context);
        mContext = context;
        init();
    }

    public GL3JniView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        mJniCall = new JniCall();
        //1、顶点及片段着色器的出入使用
//        String fragPath = OpenGLUtil.getModelFilePath(mContext, "triangle_shape_fragment.glsl");
//        String vertexPath = OpenGLUtil.getModelFilePath(mContext, "triangle_shape_vertex.glsl");
        //2、in及out属性的使用
//        String fragPath = OpenGLUtil.getModelFilePath(mContext, "rectangle_shape_rad_fragment.glsl");
//        String vertexPath = OpenGLUtil.getModelFilePath(mContext, "rectangle_shape_rad_vertex.glsl");
        //3、uniform的使用
        String fragPath = OpenGLUtil.getModelFilePath(mContext, "rectangle_uniform_fragment.glsl");
        String vertexPath = OpenGLUtil.getModelFilePath(mContext, "rectangle_uniform_vertex.glsl");
        mJniCall.setGLSLPath(fragPath, vertexPath);
        setRenderer(this);
    }


    public void onDrawFrame(GL10 gl) {
//            Log.e(TAG, "onDrawFrame: ");
        mJniCall.openGlRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.e(TAG, "onSurfaceChanged: ");
        mJniCall.initOpenGl(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }


}
