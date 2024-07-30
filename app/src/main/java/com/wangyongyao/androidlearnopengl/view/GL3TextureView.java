package com.wangyongyao.androidlearnopengl.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.wangyongyao.androidlearnopengl.JniCall;
import com.wangyongyao.androidlearnopengl.utils.OpenGLUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GL3TextureView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GL3TextureView.class.getSimpleName();
    private JniCall mJniCall;
    private Context mContext;

    public GL3TextureView(Context context, JniCall jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GL3TextureView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String fragPath = OpenGLUtil.getModelFilePath(mContext, "triangle_shape_fragment.glsl");
        String vertexPath = OpenGLUtil.getModelFilePath(mContext, "triangle_shape_vertex.glsl");
        if (mJniCall != null)
            mJniCall.setGLSLPath(fragPath, vertexPath);
        setRenderer(this);
    }


    public void onDrawFrame(GL10 gl) {
        if (mJniCall != null)
            mJniCall.openGlRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        if (mJniCall != null)
            mJniCall.initOpenGl(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }


}
