package com.wangyongyao.glsl;

public class GLSLDGCallJni {

    private static final String TAG = GLSLDGCallJni.class.getSimpleName();

    /*********************  着色器——生成设计：噪音  *****************/
    public void setNoiseFunctionsPath(String vertexPath
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
        native_noise_functions_set_glsl_path(vertexPath
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

    public void onNoiseFunctionsRenderFrame() {
        native_noise_functions_render_frame();
    }

    public void initNoiseFunctions(int width, int height) {
        native_noise_functions_init(width, height);
    }

    public void setTypeNoiseFunctions(int typeVaule) {
        native_noise_functions_set_type(typeVaule);
    }

    public int getTypeNoiseFunctions() {
        return native_noise_functions_get_type();
    }

    private native void native_noise_functions_set_glsl_path(String vertexPath
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

    private native void native_noise_functions_render_frame();

    private native void native_noise_functions_init(int width, int height);

    private native void native_noise_functions_set_type(int typeVaule);

    private native int native_noise_functions_get_type();


    /*********************  着色器 生成设计——随机 *****************/
    public void setRandomPath(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3

    ) {
        native_random_set_glsl_path(vertexPath
                , fragPath1
                , fragPath2
                , fragPath3

        );
    }

    public void onRandomRenderFrame() {
        native_random_render_frame();
    }

    public void initRandom(int width, int height) {
        native_random_init(width, height);
    }

    public void setTypeRandom(int typeVaule) {
        native_random_set_type(typeVaule);
    }

    public int getTypeRandom() {
        return native_random_get_type();
    }

    private native void native_random_set_glsl_path(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3

    );

    private native void native_random_render_frame();

    private native void native_random_init(int width, int height);

    private native void native_random_set_type(int typeVaule);

    private native int native_random_get_type();



}
