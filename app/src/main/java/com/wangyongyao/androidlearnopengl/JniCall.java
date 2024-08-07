package com.wangyongyao.androidlearnopengl;

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

    /**
     * 多立方体3D
     */
    public void setMultiCube3DGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_multi_cube_3d_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }

    public boolean initMultiCube3DOpenGl(int w, int h) {
        return native_multi_cube_3d_init_opengl(w, h);
    }

    public void MultiCube3DOpenGLRenderFrame() {
        native_multi_cube_3d_render_frame();
    }

    private native void native_multi_cube_3d_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);

    private native boolean native_multi_cube_3d_init_opengl(int width, int height);

    private native void native_multi_cube_3d_render_frame();

    /**
     * 摄像头旋转
     */
    public void setCameraGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_camera_3d_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }

    public boolean initCamera3DOpenGl(int w, int h) {
        return native_camera_3d_init_opengl(w, h);
    }

    public void CameraOpenGLRenderFrame() {
        native_camera_3d_render_frame();
    }

    public void CameraMoveXY(float dx, float dy, int action) {
        native_camera_move_xy(dx, dy, action);
    }

    public void CameraOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_camera_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_camera_3d_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);

    private native boolean native_camera_3d_init_opengl(int width, int height);

    private native void native_camera_3d_render_frame();

    private native void native_camera_move_xy(float dx, float dy, int action);

    private native void native_camera_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 灯光立方体
     */
    public void setLigtCubeGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_light_cube_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }

    public boolean initLigtCubeOpenGl(int w, int h) {
        return native_light_cube_init_opengl(w, h);
    }

    public void ligtCubeOpenGLRenderFrame() {
        native_light_cube_render_frame();
    }

    public void ligtCubeMoveXY(float dx, float dy, int action) {
        native_light_cube_move_xy(dx, dy, action);
    }

    public void ligtCubeOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_light_cube_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_light_cube_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);

    private native boolean native_light_cube_init_opengl(int width, int height);

    private native void native_light_cube_render_frame();

    private native void native_light_cube_move_xy(float dx, float dy, int action);

    private native void native_light_cube_on_scale(float scaleFactor, float focusX, float focusY, int action);

}
