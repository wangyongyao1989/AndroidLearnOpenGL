package com.wangyongyao.glsl;

public class GLSLADCallJni {

    private static final String TAG = GLSLADCallJni.class.getSimpleName();

    static {
        System.loadLibrary("glsl");
    }

    /*********************  着色器 图案 Patterns *****************/
    public void setPatternsFunctionsPath(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4

    ) {
        native_patterns_functions_set_glsl_path(vertexPath
                , fragPath1
                , fragPath2
                , fragPath3
                , fragPath4

        );
    }

    public void onPatternsFunctionsRenderFrame() {
        native_patterns_functions_render_frame();
    }

    public void initPatternsFunctions(int width, int height) {
        native_patterns_functions_init(width, height);
    }

    public void setTypePatternsFunctions(int typeVaule) {
        native_patterns_functions_set_type(typeVaule);
    }

    public int getTypePatternsFunctions() {
        return native_patterns_functions_get_type();
    }

    private native void native_patterns_functions_set_glsl_path(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4

    );

    private native void native_patterns_functions_render_frame();

    private native void native_patterns_functions_init(int width, int height);

    private native void native_patterns_functions_set_type(int typeVaule);

    private native int native_patterns_functions_get_type();

    /*********************  着色器矩阵 Matrices *****************/
    public void setMatricesFunctionsPath(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4

    ) {
        native_matrices_functions_set_glsl_path(vertexPath
                , fragPath1
                , fragPath2
                , fragPath3
                , fragPath4

        );
    }

    public void onMatricesFunctionsRenderFrame() {
        native_matrices_functions_render_frame();
    }

    public void initMatricesFunctions(int width, int height) {
        native_matrices_functions_init(width, height);
    }

    public void setTypeMatricesFunctions(int typeVaule) {
        native_matrices_functions_set_type(typeVaule);
    }

    public int getTypeMatricesFunctions() {
        return native_matrices_functions_get_type();
    }

    private native void native_matrices_functions_set_glsl_path(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4

    );

    private native void native_matrices_functions_render_frame();

    private native void native_matrices_functions_init(int width, int height);

    private native void native_matrices_functions_set_type(int typeVaule);

    private native int native_matrices_functions_get_type();

    /*********************  着色器形状 *****************/
    public void setShapeFunctionsPath(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4
            , String fragPath5

    ) {
        native_shape_functions_set_glsl_path(vertexPath
                , fragPath1
                , fragPath2
                , fragPath3
                , fragPath4
                , fragPath5

        );
    }

    public void onShapeFunctionsRenderFrame() {
        native_shape_functions_render_frame();
    }

    public void initShapeFunctions(int width, int height) {
        native_shape_functions_init(width, height);
    }

    public void setTypeShapeFunctions(int typeVaule) {
        native_shape_functions_set_type(typeVaule);
    }

    public int getTypeShapeFunctions() {
        return native_shape_functions_get_type();
    }

    private native void native_shape_functions_set_glsl_path(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4
            , String fragPath5

    );

    private native void native_shape_functions_render_frame();

    private native void native_shape_functions_init(int width, int height);

    private native void native_shape_functions_set_type(int typeVaule);

    private native int native_shape_functions_get_type();

    /*********************  GL Shader 颜色   *****************/
    public void setColorFunctionsPath(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4
            , String fragPath5


    ) {
        native_color_functions_set_glsl_path(vertexPath
                , fragPath1
                , fragPath2
                , fragPath3
                , fragPath4
                , fragPath5

        );
    }

    public void onColorFunctionsRenderFrame() {
        native_color_functions_render_frame();
    }

    public void initColorFunctions(int width, int height) {
        native_color_functions_init(width, height);
    }

    public void setTypeColorFunctions(int typeVaule) {
        native_color_functions_set_type(typeVaule);
    }

    public int getTypeColorFunctions() {
        return native_color_functions_get_type();
    }

    private native void native_color_functions_set_glsl_path(String vertexPath
            , String fragPath1
            , String fragPath2
            , String fragPath3
            , String fragPath4
            , String fragPath5

    );

    private native void native_color_functions_render_frame();

    private native void native_color_functions_init(int width, int height);

    private native void native_color_functions_set_type(int typeVaule);

    private native int native_color_functions_get_type();


    /*********************  着色器造型函数  *****************/
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
        native_shaping_functions_set_glsl_path(vertexPath
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
        native_shaping_functions_render_frame();
    }

    public void initShapingFunctions(int width, int height) {
        native_shaping_functions_init(width, height);
    }

    public void setTypeShapingFunctions(int typeVaule) {
        native_shaping_functions_set_type(typeVaule);
    }

    public int getTypeShapingFunctions() {
        return native_shaping_functions_get_type();
    }

    private native void native_shaping_functions_set_glsl_path(String vertexPath
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

    private native void native_shaping_functions_render_frame();

    private native void native_shaping_functions_init(int width, int height);

    private native void native_shaping_functions_set_type(int typeVaule);

    private native int native_shaping_functions_get_type();


}
