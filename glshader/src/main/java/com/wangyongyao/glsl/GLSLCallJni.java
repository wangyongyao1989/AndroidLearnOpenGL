package com.wangyongyao.glsl;

public class GLSLCallJni {

    private static final String TAG = GLSLCallJni.class.getSimpleName();

    static {
        System.loadLibrary("glsl");
    }


    public void setShapingFunctionsPath(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4
            , String fragPath5
            , String fragPath6
            , String fragPath7
            , String fragPath8
            , String fragPath9
            , String fragPath10
            , String fragPath11
            , String fragPath12
            , String fragPath13

    ) {
        native_shaping_funceions_set_glsl_path(vertexPath
                , fragPath1
                , fragPath2
                , fragPath3
                , fragPath4
                , fragPath5
                , fragPath6
                , fragPath7
                , fragPath8
                , fragPath9
                , fragPath10
                , fragPath11
                , fragPath12
                , fragPath13

        );
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

    private native void native_shaping_funceions_set_glsl_path(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4
            , String fragPath5
            , String fragPath6
            , String fragPath7
            , String fragPath8
            , String fragPath9
            , String fragPath10
            , String fragPath11
            , String fragPath12
            , String fragPath13

    );

    private native void native_shaping_funceions_render_frame();

    private native void native_shaping_funceions_init(int width, int height);

    private native void native_shaping_funceions_set_type(int typeVaule);

    private native int native_shaping_funceions_get_type();


}
