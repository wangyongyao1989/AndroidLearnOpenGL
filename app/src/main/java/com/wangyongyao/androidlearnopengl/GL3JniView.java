package com.wangyongyao.androidlearnopengl;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GL3JniView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GL3JniView.class.getSimpleName();
    private JniCall mJniCall;

    public GL3JniView(Context context) {
        super(context);
        init();
    }

    public GL3JniView(Context context, AttributeSet attrs) {
        super(context, attrs);
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        mJniCall = new JniCall();
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
