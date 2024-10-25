package com.wangyongyao.gl3d.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;

import com.wangyongyao.gl3d.GL3DCallJni;
import com.wangyongyao.gl3d.utils.GL3DShowUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GL3DShowView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GL3DShowView.class.getSimpleName();
    private GL3DCallJni mJniCall;
    private Context mContext;

    public GL3DShowView(Context context, GL3DCallJni jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GL3DShowView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String fragPath = GL3DShowUtil.getModelFilePath(mContext, "rectangle_uniform_fragment.glsl");
        String vertexPath = GL3DShowUtil.getModelFilePath(mContext, "rectangle_uniform_vertex.glsl");
        if (mJniCall != null)
            mJniCall.setGL3DSLPath(fragPath, vertexPath);
        setRenderer(this);
    }


    public void onDrawFrame(GL10 gl) {
        Log.e(TAG, "onDrawFrame: ");
        if (mJniCall != null)
            mJniCall.gl3DRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.e(TAG, "onSurfaceChanged: ");
        if (mJniCall != null)
            mJniCall.init3D(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }


}
