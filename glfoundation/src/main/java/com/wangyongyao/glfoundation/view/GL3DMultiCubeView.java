package com.wangyongyao.glfoundation.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.wangyongyao.glfoundation.GLFounationJniCall;
import com.wangyongyao.glfoundation.utils.OpenGLFoundationUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GL3DMultiCubeView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GL3DMultiCubeView.class.getSimpleName();
    private GLFounationJniCall mJniCall;
    private Context mContext;

    public GL3DMultiCubeView(Context context, GLFounationJniCall jniCall) {
        super(context);
        mContext = context;
        mJniCall = jniCall;
        init();
    }

    public GL3DMultiCubeView(Context context, AttributeSet attrs) {
        super(context, attrs);
        mContext = context;
        init();
    }

    private void init() {
        getHolder().addCallback(this);
        setEGLContextClientVersion(3);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        String fragPath = OpenGLFoundationUtil.getModelFilePath(mContext, "multi_cube_3d_fragment.glsl");
        String vertexPath = OpenGLFoundationUtil.getModelFilePath(mContext, "multi_cube_3d_vertex.glsl");
        String picSrc1 = OpenGLFoundationUtil.getModelFilePath(mContext, "yao.jpg");
        String picSrc2 = OpenGLFoundationUtil.getModelFilePath(mContext, "awesomeface.png");

        if (mJniCall != null) {
            mJniCall.setMultiCube3DGLSLPath(fragPath, vertexPath, picSrc1, picSrc2);
        }

        setRenderer(this);
    }


    public void onDrawFrame(GL10 gl) {
        if (mJniCall != null)
            mJniCall.MultiCube3DOpenGLRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        if (mJniCall != null)
            mJniCall.initMultiCube3DOpenGl(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }


}
