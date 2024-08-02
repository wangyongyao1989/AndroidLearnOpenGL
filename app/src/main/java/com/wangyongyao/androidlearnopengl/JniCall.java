package com.wangyongyao.androidlearnopengl;

import android.graphics.Bitmap;

public class JniCall {

    // Used to load the 'androidlearnopengl' library on application startup.
    static {
        System.loadLibrary("androidlearnopengl");
    }

    public void setFoundationGLSLPath(String fragString, String vertexString) {
        native_foundation_set_glsl_path(fragString, vertexString);
    }

    public boolean initFoundationOpenGl(int w, int h) {
        return native_foundation_init_opengl(w, h);
    }

    public void openFoundationGlRenderFrame() {
        native_foundation_render_frame();
    }


    public native String stringFromJNI();

    private native void native_callback();


    private native void native_foundation_set_glsl_path(String fragPath, String vertexPath);

    private native boolean native_foundation_init_opengl(int width, int height);

    private native void native_foundation_render_frame();

    /**
     * Texture
     */
    public void setTextureGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_texture_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }

    public boolean initTextureOpenGl(int w, int h) {
        return native_texture_init_opengl(w, h);
    }

    public void openTextureGlRenderFrame() {
        native_texture_render_frame();
    }

    private native void native_texture_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);

    private native boolean native_texture_init_opengl(int width, int height);

    private native void native_texture_render_frame();

    /**
     * 3D基础
     */
    public void set3DGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_3d_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }

    public boolean init3DOpenGl(int w, int h) {
        return native_3d_init_opengl(w, h);
    }

    public void open3DGlRenderFrame() {
        native_3d_render_frame();
    }

    private native void native_3d_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);

    private native boolean native_3d_init_opengl(int width, int height);

    private native void native_3d_render_frame();

    /**
     * 立方体3D
     */
    public void setCube3DGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_cube_3d_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }

    public boolean initCube3DOpenGl(int w, int h) {
        return native_cube_3d_init_opengl(w, h);
    }

    public void openCube3DGlRenderFrame() {
        native_cube_3d_render_frame();
    }

    private native void native_cube_3d_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);

    private native boolean native_cube_3d_init_opengl(int width, int height);

    private native void native_cube_3d_render_frame();
}
