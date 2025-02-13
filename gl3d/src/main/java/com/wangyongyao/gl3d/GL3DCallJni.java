package com.wangyongyao.gl3d;

import android.util.Log;

public class GL3DCallJni {

    private static final String TAG = GL3DCallJni.class.getSimpleName();

    static {
        System.loadLibrary("gl3dshow");
    }

    /*********************** GL 3D动画显示********************/
    public void setGL3DAnimationSLPath(String fragPath, String vertexPath) {
        native_3d_animation_set_glsl_path(fragPath, vertexPath);
    }

    public void setGL3DAnimationModelPath(String modelPath) {
        native_3d_animation_set_model_path(modelPath);
    }

    public void gl3DAnimationRenderFrame() {
        native_3d_animation_render_frame();
    }

    public void init3DAnimation(int width, int height) {
        native_3d_animation_init_opengl(width, height);
    }

    public void gl3DAnimationShowMoveXY(float dx, float dy, int action) {
        native_3d_animation_move_xy(dx, dy, action);
    }

    public void gl3DAnimationShowOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_3d_animation_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_3d_animation_set_glsl_path(String fragPath, String vertexPath);

    private native void native_3d_animation_set_model_path(String modelPath);

    private native boolean native_3d_animation_init_opengl(int width, int height);

    private native void native_3d_animation_render_frame();

    private native void native_3d_animation_move_xy(float dx, float dy, int action);

    private native void native_3d_animation_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /*********************** GL 3D模型显示********************/
    public void setGL3DSLPath(String fragPath, String vertexPath) {
        native_3d_set_glsl_path(fragPath, vertexPath);
    }

    public void setGL3DModelPath(String modelPath) {
        native_3d_set_model_path(modelPath);
    }

    public void gl3DRenderFrame() {
        native_3d_render_frame();
    }

    public void init3D(int width, int height) {
        native_3d_init_opengl(width, height);
    }

    public void gl3DShowMoveXY(float dx, float dy, int action) {
        native_3d_move_xy(dx, dy, action);
    }

    public void gl3DShowOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_3d_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_3d_set_glsl_path(String fragPath, String vertexPath);

    private native void native_3d_set_model_path(String modelPath);

    private native boolean native_3d_init_opengl(int width, int height);

    private native void native_3d_render_frame();

    private native void native_3d_move_xy(float dx, float dy, int action);

    private native void native_3d_on_scale(float scaleFactor, float focusX, float focusY, int action);


    /*********************** GL 绘制文本文字********************/
    public void setGLDrawTextSLPath(String fragPath, String vertexPath) {
        native_draw_text_set_glsl_path(fragPath, vertexPath);
    }

    public void glDrawTextRenderFrame() {
        native_draw_text_render_frame();
    }

    public void initGLDrawText(int width, int height, String modelPath) {
        native_draw_text_init_opengl(width, height, modelPath);
    }

    private native void native_draw_text_set_glsl_path(String fragPath, String vertexPath);

    private native boolean native_draw_text_init_opengl(int width, int height, String modelPath);

    private native void native_draw_text_render_frame();


    private void CppEventCallback(int msgType, float msgValue) {
        Log.e(TAG, "msgType:" + msgType + "====msgValue:" + msgValue);

    }

    private void CppPlayStatusCallback(String status) {
        Log.e(TAG, "status:" + status);

    }


    /**
     * 聚光手电筒
     */
    public void setFlashLightGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_flash_light_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }

    public void setFlashLightColorGLSLPath(String fragString, String vertexString) {
        native_flash_light_color_set_glsl_path(fragString, vertexString);
    }

    public boolean initFlashLightOpenGl(int w, int h) {
        return native_flash_light_init_opengl(w, h);
    }

    public void flashLightOpenGLRenderFrame() {
        native_flash_light_render_frame();
    }

    public void flashLightMoveXY(float dx, float dy, int action) {
        native_flash_light_move_xy(dx, dy, action);
    }

    public void flashLightOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_flash_light_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_flash_light_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);

    private native void native_flash_light_color_set_glsl_path(String fragPath, String vertexPath);

    private native boolean native_flash_light_init_opengl(int width, int height);

    private native void native_flash_light_render_frame();

    private native void native_flash_light_move_xy(float dx, float dy, int action);

    private native void native_flash_light_on_scale(float scaleFactor, float focusX, float focusY, int action);

}
