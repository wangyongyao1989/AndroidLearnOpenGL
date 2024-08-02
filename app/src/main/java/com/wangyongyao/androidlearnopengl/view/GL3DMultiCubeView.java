package com.wangyongyao.androidlearnopengl.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.wangyongyao.androidlearnopengl.JniCall;
import com.wangyongyao.androidlearnopengl.utils.OpenGLUtil;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GL3DMultiCubeView extends GLSurfaceView implements GLSurfaceView.Renderer {

    private static String TAG = GL3DMultiCubeView.class.getSimpleName();
    private JniCall mJniCall;
    private Context mContext;

    public GL3DMultiCubeView(Context context, JniCall jniCall) {
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
        String fragPath = OpenGLUtil.getModelFilePath(mContext, "cube_3d_fragment.glsl");
        String vertexPath = OpenGLUtil.getModelFilePath(mContext, "cube_3d_vertex.glsl");
        String picSrc1 = OpenGLUtil.getModelFilePath(mContext, "wall.jpg");
        String picSrc2 = OpenGLUtil.getModelFilePath(mContext, "awesomeface.png");

        if (mJniCall != null) {
            mJniCall.setMultiCube3DGLSLPath(fragPath, vertexPath, picSrc1, picSrc2);
        }

        setRenderer(this);
    }


    public void onDrawFrame(GL10 gl) {
        if (mJniCall != null)
            mJniCall.openMultiCube3DGlRenderFrame();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        if (mJniCall != null)
            mJniCall.initMultiCube3DOpenGl(width, height);
    }


    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {

    }


}
