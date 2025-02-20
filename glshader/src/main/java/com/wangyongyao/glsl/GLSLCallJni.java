package com.wangyongyao.glsl;

public class GLSLCallJni {

    private static final String TAG = GLSLCallJni.class.getSimpleName();

    static {
        System.loadLibrary("glsl");
    }


    public void setShapingFunctionsPath(String vertexPath, String fragPath) {
        native_shaping_funceions_set_glsl_path(vertexPath, fragPath);
    }

    public void onShapingFunctionsRenderFrame() {
        native_shaping_funceions_render_frame();
    }

    public void initShapingFunctions(int width, int height) {
        native_shaping_funceions_init(width, height);
    }

    public void setTypeShapingFunctions(int typeVaule) {
        native_shaping_funceions_set_type(typeVaule);
    }

    public int getTypeShapingFunctions() {
        return native_shaping_funceions_get_type();
    }

    private native void native_shaping_funceions_set_glsl_path(String vertexPath, String fragPath);

    private native void native_shaping_funceions_render_frame();

    private native void native_shaping_funceions_init(int width, int height);

    private native void native_shaping_funceions_set_type(int typeVaule);

    private native int native_shaping_funceions_get_type();


}
