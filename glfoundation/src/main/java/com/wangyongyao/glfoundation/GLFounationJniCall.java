package com.wangyongyao.glfoundation;

public class GLFounationJniCall {

    // Used to load the 'androidlearnopengl' library on application startup.
    static {
        System.loadLibrary("glfoundation");
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
    public void setColorGLSLPath(String fragString, String vertexString) {
        native_color_set_glsl_path(fragString, vertexString);
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
    private native void native_color_set_glsl_path(String fragPath, String vertexPath);
    private native boolean native_light_cube_init_opengl(int width, int height);
    private native void native_light_cube_render_frame();
    private native void native_light_cube_move_xy(float dx, float dy, int action);
    private native void native_light_cube_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 漫反射光照
     */
    public void setDiffuseReflectionGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_diffuse_reflection_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }
    public void setDiffuseReflectionColorGLSLPath(String fragString, String vertexString) {
        native_diffuse_reflection_color_set_glsl_path(fragString, vertexString);
    }
    public boolean initDiffuseReflectionOpenGl(int w, int h) {
        return native_diffuse_reflection_init_opengl(w, h);
    }
    public void diffuseReflectionOpenGLRenderFrame() {
        native_diffuse_reflection_render_frame();
    }
    public void diffuseReflectionMoveXY(float dx, float dy, int action) {
        native_diffuse_reflection_move_xy(dx, dy, action);
    }
    public void diffuseReflectionOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_diffuse_reflection_on_scale(scaleFactor, focusX, focusY, action);
    }
    private native void native_diffuse_reflection_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);
    private native void native_diffuse_reflection_color_set_glsl_path(String fragPath, String vertexPath);
    private native boolean native_diffuse_reflection_init_opengl(int width, int height);
    private native void native_diffuse_reflection_render_frame();
    private native void native_diffuse_reflection_move_xy(float dx, float dy, int action);
    private native void native_diffuse_reflection_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 镜面光照
     */
    public void setSpecularGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_specular_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }
    public void setSpecularColorGLSLPath(String fragString, String vertexString) {
        native_specular_color_set_glsl_path(fragString, vertexString);
    }
    public boolean initSpecularOpenGl(int w, int h) {
        return native_specular_init_opengl(w, h);
    }
    public void specularOpenGLRenderFrame() {
        native_specular_render_frame();
    }
    public void specularMoveXY(float dx, float dy, int action) {
        native_specular_move_xy(dx, dy, action);
    }
    public void specularOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_specular_on_scale(scaleFactor, focusX, focusY, action);
    }
    private native void native_specular_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);
    private native void native_specular_color_set_glsl_path(String fragPath, String vertexPath);
    private native boolean native_specular_init_opengl(int width, int height);
    private native void native_specular_render_frame();
    private native void native_specular_move_xy(float dx, float dy, int action);
    private native void native_specular_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 镜面光照
     */
    public void setMaterialGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_material_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }
    public void setMaterialColorGLSLPath(String fragString, String vertexString) {
        native_material_color_set_glsl_path(fragString, vertexString);
    }
    public boolean initMaterialOpenGl(int w, int h) {
        return native_material_init_opengl(w, h);
    }
    public void materialOpenGLRenderFrame() {
        native_material_render_frame();
    }
    public void materialMoveXY(float dx, float dy, int action) {
        native_material_move_xy(dx, dy, action);
    }
    public void materialOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_material_on_scale(scaleFactor, focusX, focusY, action);
    }
    private native void native_material_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);
    private native void native_material_color_set_glsl_path(String fragPath, String vertexPath);
    private native boolean native_material_init_opengl(int width, int height);
    private native void native_material_render_frame();
    private native void native_material_move_xy(float dx, float dy, int action);
    private native void native_material_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 漫反射贴图
     */
    public void setDiffuseMapGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_diffuse_map_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }
    public void setDiffuseMapColorGLSLPath(String fragString, String vertexString) {
        native_diffuse_map_color_set_glsl_path(fragString, vertexString);
    }
    public boolean initDiffuseMapOpenGl(int w, int h) {
        return native_diffuse_map_init_opengl(w, h);
    }
    public void diffuseMapOpenGLRenderFrame() {
        native_diffuse_map_render_frame();
    }
    public void diffuseMapMoveXY(float dx, float dy, int action) {
        native_diffuse_map_move_xy(dx, dy, action);
    }
    public void diffuseMapOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_diffuse_map_on_scale(scaleFactor, focusX, focusY, action);
    }
    private native void native_diffuse_map_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);
    private native void native_diffuse_map_color_set_glsl_path(String fragPath, String vertexPath);
    private native boolean native_diffuse_map_init_opengl(int width, int height);
    private native void native_diffuse_map_render_frame();
    private native void native_diffuse_map_move_xy(float dx, float dy, int action);
    private native void native_diffuse_map_on_scale(float scaleFactor, float focusX, float focusY, int action);


    /**
     * 漫反射贴图
     */
    public void setSpecularMapGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_specular_map_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }
    public void setSpecularMapColorGLSLPath(String fragString, String vertexString) {
        native_specular_map_color_set_glsl_path(fragString, vertexString);
    }
    public boolean initSpecularMapOpenGl(int w, int h) {
        return native_specular_map_init_opengl(w, h);
    }
    public void specularMapOpenGLRenderFrame() {
        native_specular_map_render_frame();
    }
    public void specularMapMoveXY(float dx, float dy, int action) {
        native_specular_map_move_xy(dx, dy, action);
    }
    public void specularMapOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_specular_map_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_specular_map_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);
    private native void native_specular_map_color_set_glsl_path(String fragPath, String vertexPath);
    private native boolean native_specular_map_init_opengl(int width, int height);
    private native void native_specular_map_render_frame();
    private native void native_specular_map_move_xy(float dx, float dy, int action);
    private native void native_specular_map_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 平行光
     */
    public void setDirectionLightGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_direction_light_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }
    public void setDirectionLightColorGLSLPath(String fragString, String vertexString) {
        native_direction_light_color_set_glsl_path(fragString, vertexString);
    }
    public boolean initDirectionLightOpenGl(int w, int h) {
        return native_direction_light_init_opengl(w, h);
    }
    public void directionLightOpenGLRenderFrame() {
        native_direction_light_render_frame();
    }
    public void directionLightMoveXY(float dx, float dy, int action) {
        native_direction_light_move_xy(dx, dy, action);
    }
    public void directionLightOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_direction_light_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_direction_light_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);
    private native void native_direction_light_color_set_glsl_path(String fragPath, String vertexPath);
    private native boolean native_direction_light_init_opengl(int width, int height);
    private native void native_direction_light_render_frame();
    private native void native_direction_light_move_xy(float dx, float dy, int action);
    private native void native_direction_light_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 点光源衰减
     */
    public void setAttenuationLightGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_attenuation_light_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }
    public void setAttenuationLightColorGLSLPath(String fragString, String vertexString) {
        native_attenuation_light_color_set_glsl_path(fragString, vertexString);
    }
    public boolean initAttenuationLightOpenGl(int w, int h) {
        return native_attenuation_light_init_opengl(w, h);
    }
    public void attenuationLightOpenGLRenderFrame() {
        native_attenuation_light_render_frame();
    }
    public void attenuationLightMoveXY(float dx, float dy, int action) {
        native_attenuation_light_move_xy(dx, dy, action);
    }
    public void attenuationLightOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_attenuation_light_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_attenuation_light_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);
    private native void native_attenuation_light_color_set_glsl_path(String fragPath, String vertexPath);
    private native boolean native_attenuation_light_init_opengl(int width, int height);
    private native void native_attenuation_light_render_frame();
    private native void native_attenuation_light_move_xy(float dx, float dy, int action);
    private native void native_attenuation_light_on_scale(float scaleFactor, float focusX, float focusY, int action);


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

    /**
     * 聚光平滑/软化边缘
     */
    public void setSpotLightGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_spot_light_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }
    public void setSpotLightColorGLSLPath(String fragString, String vertexString) {
        native_spot_light_color_set_glsl_path(fragString, vertexString);
    }
    public boolean initSpotLightOpenGl(int w, int h) {
        return native_spot_light_init_opengl(w, h);
    }
    public void spotLightOpenGLRenderFrame() {
        native_spot_light_render_frame();
    }
    public void spotLightMoveXY(float dx, float dy, int action) {
        native_spot_light_move_xy(dx, dy, action);
    }
    public void spotLightOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_spot_light_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_spot_light_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);
    private native void native_spot_light_color_set_glsl_path(String fragPath, String vertexPath);
    private native boolean native_spot_light_init_opengl(int width, int height);
    private native void native_spot_light_render_frame();
    private native void native_spot_light_move_xy(float dx, float dy, int action);
    private native void native_spot_light_on_scale(float scaleFactor, float focusX, float focusY, int action);

    /**
     * 多光源
     */
    public void setMultiLightGLSLPath(String fragString, String vertexString, String picSrc1, String picSrc2) {
        native_multi_light_set_glsl_path(fragString, vertexString, picSrc1, picSrc2);
    }
    public void setMultiLightColorGLSLPath(String fragString, String vertexString) {
        native_multi_light_color_set_glsl_path(fragString, vertexString);
    }
    public boolean initMultiLightOpenGl(int w, int h) {
        return native_multi_light_init_opengl(w, h);
    }
    public void multiLightOpenGLRenderFrame() {
        native_multi_light_render_frame();
    }
    public void multiLightMoveXY(float dx, float dy, int action) {
        native_multi_light_move_xy(dx, dy, action);
    }
    public void multiLightOnScale(float scaleFactor, float focusX, float focusY, int action) {
        native_multi_light_on_scale(scaleFactor, focusX, focusY, action);
    }

    private native void native_multi_light_set_glsl_path(String fragPath, String vertexPath
            , String picSrc1, String picSrc2);
    private native void native_multi_light_color_set_glsl_path(String fragPath, String vertexPath);
    private native boolean native_multi_light_init_opengl(int width, int height);
    private native void native_multi_light_render_frame();
    private native void native_multi_light_move_xy(float dx, float dy, int action);
    private native void native_multi_light_on_scale(float scaleFactor, float focusX, float focusY, int action);

}
