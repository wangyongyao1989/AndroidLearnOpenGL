package com.wangyongyao.glsl;

public class GLSLDGCallJni {

    private static final String TAG = GLSLDGCallJni.class.getSimpleName();


    /*********************  着色器 生成设计——随机 *****************/
    public void setRandomPath(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4

    ) {
        native_random_set_glsl_path(vertexPath
                , fragPath1
                , fragPath2
                , fragPath3
                , fragPath4

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
            , String fragPath4

    );

    private native void native_random_render_frame();

    private native void native_random_init(int width, int height);

    private native void native_random_set_type(int typeVaule);

    private native int native_random_get_type();



}
