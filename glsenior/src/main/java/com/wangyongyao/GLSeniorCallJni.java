package com.wangyongyao;

import android.util.Log;

import com.wangyongyao.utils.GLSeniorUtil;

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

    /*********************** GL 3D模型显示********************/
    public void setGLAsteroidSLPath(String fragPath, String vertexPath) {
        native_asteroid_set_glsl_path(fragPath, vertexPath);
    }

    public void setGLAsteroidModelPath(String modelPath1, String modelPath2) {
        native_asteroid_set_model_path(modelPath1, modelPath2);
    }

    public void glAsteroidRenderFrame() {
        native_asteroid_render_frame();
    }

    public void initAsteroid(int width, int height) {
        native_asteroid_init_opengl(width, height);
    }

    public void glAsteroidShowMoveXY(float dx, float dy, int action) {
        native_asteroid_move_xy(dx, dy, action);
    }

    public void glAsteroidShowOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_asteroid_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_asteroid_set_glsl_path(String fragPath, String vertexPath);

    private native void native_asteroid_set_model_path(String modelPath, String modelPath2);

    private native boolean native_asteroid_init_opengl(int width, int height);

    private native void native_asteroid_render_frame();

    private native void native_asteroid_move_xy(float dx, float dy, int action);

    private native void native_asteroid_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 实例化
     */
    public void setSeniorInstanceGLSLPath(String vertexString
            , String fragPath) {
        native_instance_set_glsl_path(vertexString
                , fragPath
        );
    }

    public boolean initSeniorInstanceOpenGl(int w, int h) {
        return native_instance_init_opengl(w, h);
    }

    public void seniorInstanceOpenGLRenderFrame() {
        native_instance_render_frame();
    }

    public void seniorInstanceMoveXY(float dx, float dy, int action) {
        native_instance_move_xy(dx, dy, action);
    }

    public void seniorInstanceOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_instance_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_instance_set_glsl_path(String vertexString
            , String fragPath);


    private native boolean native_instance_init_opengl(int width, int height);

    private native void native_instance_render_frame();

    private native void native_instance_move_xy(float dx, float dy, int action);

    private native void native_instance_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 几何着色器
     */
    public void setSeniorGeometryGLSLPath(String vertexString
            , String fragPath, String geometryPath
    ) {
        native_geometry_set_glsl_path(vertexString
                , fragPath, geometryPath
        );
    }

    public boolean initSeniorGeometryOpenGl(int w, int h) {
        return native_geometry_init_opengl(w, h);
    }

    public void seniorGeometryOpenGLRenderFrame() {
        native_geometry_render_frame();
    }

    public void seniorGeometryMoveXY(float dx, float dy, int action) {
        native_geometry_move_xy(dx, dy, action);
    }

    public void seniorGeometryOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_geometry_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_geometry_set_glsl_path(String vertexString
            , String fragPath, String geometryPath
    );


    private native boolean native_geometry_init_opengl(int width, int height);

    private native void native_geometry_render_frame();

    private native void native_geometry_move_xy(float dx, float dy, int action);

    private native void native_geometry_on_scale(float scaleFactor, float focusX, float focusY, int action);


    /**
     * 立方体贴图——反射
     */
    public void setSeniorUniformGLSLPath(String vertexString
            , String fragRedPath, String fragBluePath
            , String fragGreenPath, String fragYellowPath
    ) {
        native_uniform_set_glsl_path(vertexString
                , fragRedPath, fragBluePath
                , fragGreenPath, fragYellowPath
        );
    }

    public boolean initSeniorUniformOpenGl(int w, int h) {
        return native_uniform_init_opengl(w, h);
    }

    public void seniorUniformOpenGLRenderFrame() {
        native_uniform_render_frame();
    }

    public void seniorUniformMoveXY(float dx, float dy, int action) {
        native_uniform_move_xy(dx, dy, action);
    }

    public void seniorUniformOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_uniform_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_uniform_set_glsl_path(String vertexString
            , String fragRedPath, String fragBluePath
            , String fragGreenPath, String fragYellowPath
    );


    private native boolean native_uniform_init_opengl(int width, int height);

    private native void native_uniform_render_frame();

    private native void native_uniform_move_xy(float dx, float dy, int action);

    private native void native_uniform_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 立方体贴图——反射
     */
    public void setReflectionGLSLPath(String fragString, String vertexString
            , String fragScreenString, String vertexScreenString
            , String picSrc1, String picSrc2
            , String picSrc3, String picSrc4
            , String picSrc5, String picSrc6
            , String picSrc7
    ) {
        native_reflection_set_glsl_path(fragString, vertexString
                , fragScreenString, vertexScreenString
                , picSrc1, picSrc2
                , picSrc3, picSrc4
                , picSrc5, picSrc6
                , picSrc7
        );
    }

    public boolean initReflectionOpenGl(int w, int h) {
        return native_reflection_init_opengl(w, h);
    }

    public void reflectionOpenGLRenderFrame() {
        native_reflection_render_frame();
    }

    public void reflectionMoveXY(float dx, float dy, int action) {
        native_reflection_move_xy(dx, dy, action);
    }

    public void reflectionOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_reflection_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_reflection_set_glsl_path(String fragPath, String vertexPath
            , String fragScreenString, String vertexScreenString
            , String picSrc1, String picSrc2
            , String picSrc3, String picSrc4
            , String picSrc5, String picSrc6
            , String picSrc7
    );


    private native boolean native_reflection_init_opengl(int width, int height);

    private native void native_reflection_render_frame();

    private native void native_reflection_move_xy(float dx, float dy, int action);

    private native void native_reflection_on_scale(float scaleFactor, float focusX, float focusY, int action);


    /**
     * 立方体贴图 CubeMap
     */
    public void setCubeMapGLSLPath(String fragString, String vertexString
            , String fragScreenString, String vertexScreenString
            , String picSrc1, String picSrc2
            , String picSrc3, String picSrc4
            , String picSrc5, String picSrc6
            , String picSrc7
    ) {
        native_cube_map_set_glsl_path(fragString, vertexString
                , fragScreenString, vertexScreenString
                , picSrc1, picSrc2
                , picSrc3, picSrc4
                , picSrc5, picSrc6
                , picSrc7
        );
    }

    public boolean initCubeMapOpenGl(int w, int h) {
        return native_cube_map_init_opengl(w, h);
    }

    public void cubeMapOpenGLRenderFrame() {
        native_cube_map_render_frame();
    }

    public void cubeMapMoveXY(float dx, float dy, int action) {
        native_cube_map_move_xy(dx, dy, action);
    }

    public void cubeMapOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_cube_map_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_cube_map_set_glsl_path(String fragPath, String vertexPath
            , String fragScreenString, String vertexScreenString
            , String picSrc1, String picSrc2
            , String picSrc3, String picSrc4
            , String picSrc5, String picSrc6
            , String picSrc7
    );


    private native boolean native_cube_map_init_opengl(int width, int height);

    private native void native_cube_map_render_frame();

    private native void native_cube_map_move_xy(float dx, float dy, int action);

    private native void native_cube_map_on_scale(float scaleFactor, float focusX, float focusY, int action);


    /**
     * 帧缓冲FBO——后期处理
     */
    public void setFBOPostProcessingGLSLPath(String fragString, String vertexString
            , String fragScreenString, String vertexScreenString
            , String picSrc1, String picSrc2
            , String fragGrayScalePath
            , String fragWeightedGrayPath
            , String fragNuclearEffectPath
    ) {
        native_fbo_post_processing_set_glsl_path(fragString, vertexString
                , fragScreenString, vertexScreenString
                , picSrc1, picSrc2
                , fragGrayScalePath
                , fragWeightedGrayPath
                , fragNuclearEffectPath
        );
    }

    public boolean initFBOPostProcessing(int w, int h) {
        return native_fbo_post_processing_init_opengl(w, h);
    }

    public void glFBOPostProcessingRenderFrame() {
        native_fbo_post_processing_render_frame();
    }

    public void glFBOPostProcessingMoveXY(float dx, float dy, int action) {
        native_fbo_post_processing_move_xy(dx, dy, action);
    }

    public void glFBOPostProcessingOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_fbo_post_processing_on_scale(scaleFactor, focusX, focusY, action);
    }

    public void glFBOPostProcessingSetParameters(int params) {
        native_fbo_post_processing_set_parameters(params);
    }

    public int glFBOPostProcessingGetParameters() {
        return native_fbo_post_processing_get_parameters();
    }

    private native void native_fbo_post_processing_set_glsl_path(String fragPath, String vertexPath
            , String fragScreenString, String vertexScreenString
            , String picSrc1, String picSrc2
            , String fragGrayScalePath
            , String fragWeightedGrayPath
            , String fragNuclearEffectPath

    );

    private native boolean native_fbo_post_processing_init_opengl(int width, int height);

    private native void native_fbo_post_processing_render_frame();

    private native void native_fbo_post_processing_move_xy(float dx, float dy, int action);

    private native void native_fbo_post_processing_on_scale(float scaleFactor, float focusX, float focusY, int action);

    private native void native_fbo_post_processing_set_parameters(int params);

    private native int native_fbo_post_processing_get_parameters();

    /**
     * 帧缓冲FBO
     */
    public void setFBOGLSLPath(String fragString, String vertexString
            , String fragScreenString, String vertexScreenString
            , String picSrc1, String picSrc2) {
        native_fbo_set_glsl_path(fragString, vertexString
                , fragScreenString, vertexScreenString
                , picSrc1, picSrc2);
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
            , String fragScreenString, String vertexScreenString
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
