package com.wangyongyao;

import android.util.Log;

public class GLSeniorCallJni {

    private static final String TAG = GLSeniorCallJni.class.getSimpleName();

    static {
        System.loadLibrary("glsenior");
    }


    private void CppEventCallback(int msgType, float msgValue) {
        Log.e(TAG, "msgType:" + msgType + "====msgValue:" + msgValue);

    }

    private void CppPlayStatusCallback(String status) {
        Log.e(TAG, "status:" + status);

    }



    /**
     * 帧缓冲FBO
     */
    public void setFBOGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_fbo_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }

    public boolean initFBOOpenGl(int w, int h) {
        return native_fbo_init_opengl(w, h);
    }

    public void fBOOpenGLRenderFrame() {
        native_fbo_render_frame();
    }

    public void fBOMoveXY(float dx, float dy, int action) {
        native_fbo_move_xy(dx, dy, action);
    }

    public void fBOOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_fbo_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_fbo_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);


    private native boolean native_fbo_init_opengl(int width, int height);

    private native void native_fbo_render_frame();

    private native void native_fbo_move_xy(float dx, float dy, int action);

    private native void native_fbo_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 混合--排序
     */
    public void setBlendingSortGLSLPath(String fragString, String vertexString
            , String picSrc1, String picSrc2, String picSrc3) {
        native_blending_sort_set_glsl_path(fragString, vertexString
                , picSrc1, picSrc2, picSrc3);
    }

    public boolean initBlendingSortOpenGl(int w, int h) {
        return native_blending_sort_init_opengl(w, h);
    }

    public void blendingSortOpenGLRenderFrame() {
        native_blending_sort_render_frame();
    }

    public void blendingSortMoveXY(float dx, float dy, int action) {
        native_blending_sort_move_xy(dx, dy, action);
    }

    public void blendingSortOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_blending_sort_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_blending_sort_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2, String picSrc3);


    private native boolean native_blending_sort_init_opengl(int width, int height);

    private native void native_blending_sort_render_frame();

    private native void native_blending_sort_move_xy(float dx, float dy, int action);

    private native void native_blending_sort_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 混合--丢弃
     */
    public void setBlendingDiscardGLSLPath(String fragString, String vertexString
            , String picSrc1, String picSrc2, String picSrc3) {
        native_blending_discard_set_glsl_path(fragString, vertexString
                , picSrc1, picSrc2, picSrc3);
    }

    public boolean initBlendingDiscardOpenGl(int w, int h) {
        return native_blending_discard_init_opengl(w, h);
    }

    public void blendingDiscardOpenGLRenderFrame() {
        native_blending_discard_render_frame();
    }

    public void blendingDiscardMoveXY(float dx, float dy, int action) {
        native_blending_discard_move_xy(dx, dy, action);
    }

    public void blendingDiscardOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_blending_discard_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_blending_discard_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2, String picSrc3);


    private native boolean native_blending_discard_init_opengl(int width, int height);

    private native void native_blending_discard_render_frame();

    private native void native_blending_discard_move_xy(float dx, float dy, int action);

    private native void native_blending_discard_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 模版测试
     */
    public void setStencilTestGLSLPath(String fragString, String vertexString
            , String picSrc1, String picSrc2, String singleColorfragPath) {
        native_stencil_test_set_glsl_path(fragString, vertexString
                , picSrc1, picSrc2, singleColorfragPath);
    }

    public boolean initStencilTestOpenGl(int w, int h) {
        return native_stencil_test_init_opengl(w, h);
    }

    public void stencilTestOpenGLRenderFrame() {
        native_stencil_test_render_frame();
    }

    public void stencilTestMoveXY(float dx, float dy, int action) {
        native_stencil_test_move_xy(dx, dy, action);
    }

    public void stencilTestOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_stencil_test_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_stencil_test_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2, String singleColorfragPath);


    private native boolean native_stencil_test_init_opengl(int width, int height);

    private native void native_stencil_test_render_frame();

    private native void native_stencil_test_move_xy(float dx, float dy, int action);

    private native void native_stencil_test_on_scale(float scaleFactor, float focusX, float focusY, int action);


    /**
     * 深度测试
     */
    public void setDepthTestGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_depth_test_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }

    public boolean initDepthTestOpenGl(int w, int h) {
        return native_depth_test_init_opengl(w, h);
    }

    public void depthTestOpenGLRenderFrame() {
        native_depth_test_render_frame();
    }

    public void dpthTestMoveXY(float dx, float dy, int action) {
        native_depth_test_move_xy(dx, dy, action);
    }

    public void depthTestOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_depth_test_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_depth_test_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);


    private native boolean native_depth_test_init_opengl(int width, int height);

    private native void native_depth_test_render_frame();

    private native void native_depth_test_move_xy(float dx, float dy, int action);

    private native void native_depth_test_on_scale(float scaleFactor, float focusX, float focusY, int action);



}
