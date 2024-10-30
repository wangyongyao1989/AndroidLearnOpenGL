package com.wangyongyao.gl3d.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;

import com.wangyongyao.gl3d.GL3DCallJni;
import com.wangyongyao.gl3d.utils.GL3DShowUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLDrawTextView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GLDrawTextView.class.getSimpleName();
    private GL3DCallJni mJniCall;
    private Context mContext;

    public GLDrawTextView(Context context, GL3DCallJni jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GLDrawTextView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String fragPath = GL3DShowUtil.getModelFilePath(mContext
                , "gl_draw_text_fragment.glsl");
        String vertexPath = GL3DShowUtil.getModelFilePath(mContext
                , "gl_draw_text_vertex.glsl");

        if (mJniCall != null) {
            mJniCall.setGLDrawTextSLPath(fragPath, vertexPath);
        }
        setRenderer(this);
    }


    public void onDrawFrame(GL10 gl) {
//        Log.e(TAG, "onDrawFrame: ");
        if (mJniCall != null)
            mJniCall.glDrawTextRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.e(TAG, "onSurfaceChanged: ");
        if (mJniCall != null)
            mJniCall.initGLDrawText(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        String modelPath = GL3DShowUtil.getModelFilePath(mContext
                , "jianti.ttf");
        if (mJniCall != null)
            mJniCall.setGLDrawTextTypePath(modelPath);
    }


}
