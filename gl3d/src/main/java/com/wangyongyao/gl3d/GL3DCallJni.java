package com.wangyongyao.gl3d;

import android.util.Log;

public class GL3DCallJni {

    private static final String TAG = GL3DCallJni.class.getSimpleName();

    static {
        System.loadLibrary("gl3d");
    }


    public void setGL3DSLPath(String fragPath, String vertexPath) {
        native_3d_set_glsl_path(fragPath, vertexPath);
    }

    public void gl3DRenderFrame() {
        native_3d_render_frame();
    }

    public void init3D(int width, int height) {
        native_3d_init_opengl(width, height);
    }

    private native void native_3d_set_glsl_path(String fragPath, String vertexPath);

    private native boolean native_3d_init_opengl(int width, int height);

    private native void native_3d_render_frame();


    private void CppEventCallback(int msgType, float msgValue) {
        Log.e(TAG, "msgType:" + msgType + "====msgValue:" + msgValue);

    }

    private void CppPlayStatusCallback(String status) {
        Log.e(TAG, "status:" + status);

    }

}
