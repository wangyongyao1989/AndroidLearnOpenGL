#include <jni.h>
#include <string>
#include <android/log.h>
#include "includes/GLSeniorLogUtils.h"
#include "GLSeniorDepthTest.h"
#include "GLSeniorStencilTest.h"
#include "GLSeniorBlendingDiscard.h"
#include "GLSeniorBlendingSort.h"
#include "GLSeniorFBO.h"
#include "GLFBOPostProcessing.h"
#include <android/native_window_jni.h>
#include <android/asset_manager_jni.h>
#include "GLSeniorCubeMap.h"
#include "GLSeniorReflection.h"
#include "GLSeniorUniform.h"
#include "GLSeniorGeometry.h"
#include "GLSeniorInstance.h"
#include "GLSenior3DShow.h"

//包名+类名字符串定义：
const char *glshader_class_name = "com/wangyongyao/GLSeniorCallJni";

GLSeniorDepthTest *depthTest;
GLSeniorStencilTest *stencilTest;
GLSeniorBlendingDiscard *blendingDiscard;
GLSeniorBlendingSort *blendingSort;
GLSeniorFBO *fbo;
GLFBOPostProcessing *postProcessing;
GLSeniorCubeMap *cubeMap;
GLSeniorReflection *reflection;
GLSeniorUniform *uniform;
GLSeniorGeometry *geometry;
GLSeniorInstance *instance;
GLSenior3DShow *gl3DShow;


/*********************** GL 3d模型显示********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_asteroid_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (gl3DShow == nullptr)
        gl3DShow = new GLSenior3DShow();
    gl3DShow->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_asteroid_render_frame(JNIEnv *env, jobject thiz) {
    if (gl3DShow == nullptr) return;
    gl3DShow->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_asteroid_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    if (gl3DShow == nullptr) {
        gl3DShow = new GLSenior3DShow();
    }

    gl3DShow->setSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}

extern "C"
JNIEXPORT void JNICALL
cpp_asteroid_model_path(JNIEnv *env, jobject thiz, jstring model1, jstring model2) {
    const char *modelPath1 = env->GetStringUTFChars(model1, nullptr);
    const char *modelPath2 = env->GetStringUTFChars(model2, nullptr);

    if (gl3DShow == nullptr) {
        gl3DShow = new GLSenior3DShow();
    }

    gl3DShow->setModelPath(modelPath1, modelPath2);

    env->ReleaseStringUTFChars(model1, modelPath1);
    env->ReleaseStringUTFChars(model2, modelPath2);

}


extern "C"
JNIEXPORT void JNICALL
cpp_asteroid_show_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (gl3DShow == nullptr) return;
    gl3DShow->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_asteroid_show_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                           jfloat focusY,
                           jint actionMode) {
    if (gl3DShow == nullptr) return;
    gl3DShow->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL 高级实例化********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_instance_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (instance == nullptr)
        instance = new GLSeniorInstance();
    instance->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_instance_render_frame(JNIEnv *env, jobject thiz) {
    if (instance == nullptr) return;
    instance->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_instance_frag_vertex_path(JNIEnv *env, jobject thiz, jstring vertex,
                              jstring frag

) {
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);


    if (instance == nullptr) {
        instance = new GLSeniorInstance();
    }

    instance->setSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(frag, fragPath);

}


extern "C"
JNIEXPORT void JNICALL
cpp_instance_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (instance == nullptr) return;
    instance->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_instance_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                      jfloat focusY,
                      jint actionMode) {
    if (instance == nullptr) return;
    instance->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL 高级Uniform********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_geometry_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (geometry == nullptr)
        geometry = new GLSeniorGeometry();
    geometry->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_geometry_render_frame(JNIEnv *env, jobject thiz) {
    if (geometry == nullptr) return;
    geometry->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_geometry_frag_vertex_path(JNIEnv *env, jobject thiz, jstring vertex,
                              jstring frag, jstring geometryS

) {
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *geometryPath = env->GetStringUTFChars(geometryS, nullptr);


    if (geometry == nullptr) {
        geometry = new GLSeniorGeometry();
    }

    geometry->setSharderPath(vertexPath, fragPath, geometryPath);

    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(geometryS, geometryPath);

}


extern "C"
JNIEXPORT void JNICALL
cpp_geometry_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (geometry == nullptr) return;
    geometry->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_geometry_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                      jfloat focusY,
                      jint actionMode) {
    if (geometry == nullptr) return;
    geometry->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL 高级Uniform********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_uniform_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (uniform == nullptr)
        uniform = new GLSeniorUniform();
    uniform->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_uniform_render_frame(JNIEnv *env, jobject thiz) {
    if (uniform == nullptr) return;
    uniform->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_uniform_frag_vertex_path(JNIEnv *env, jobject thiz, jstring vertex, jstring fragRed,
                             jstring fragBlue, jstring fragGreen, jstring fragYellow

) {
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragRedPath = env->GetStringUTFChars(fragRed, nullptr);
    const char *fragBluePath = env->GetStringUTFChars(fragBlue, nullptr);
    const char *fragGreenPath = env->GetStringUTFChars(fragGreen, nullptr);
    const char *fragYellowPath = env->GetStringUTFChars(fragYellow, nullptr);


    if (uniform == nullptr) {
        uniform = new GLSeniorUniform();
    }

    uniform->setSharderPath(vertexPath, fragRedPath, fragBluePath, fragGreenPath, fragYellowPath);

    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(fragRed, fragRedPath);
    env->ReleaseStringUTFChars(fragBlue, fragBluePath);
    env->ReleaseStringUTFChars(fragGreen, fragGreenPath);
    env->ReleaseStringUTFChars(fragYellow, fragYellowPath);

}


extern "C"
JNIEXPORT void JNICALL
cpp_uniform_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (uniform == nullptr) return;
    uniform->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_uniform_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                     jfloat focusY,
                     jint actionMode) {
    if (uniform == nullptr) return;
    uniform->setOnScale(scaleFactor, focusX, focusY, actionMode);
}



/*********************** GL 立方体贴图——反射********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_reflection_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (reflection == nullptr)
        reflection = new GLSeniorReflection();
    reflection->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_reflection_render_frame(JNIEnv *env, jobject thiz) {
    if (reflection == nullptr) return;
    reflection->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_reflection_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                                jstring fragScreen, jstring vertexScreen, jstring picsrc1,
                                jstring picsrc2, jstring picsrc3, jstring picsrc4,
                                jstring picsrc5, jstring picsrc6, jstring picsrc7

) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragScreenPath = env->GetStringUTFChars(fragScreen, nullptr);
    const char *vertexScreenPath = env->GetStringUTFChars(vertexScreen, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);
    const char *picsrc3Path = env->GetStringUTFChars(picsrc3, nullptr);
    const char *picsrc4Path = env->GetStringUTFChars(picsrc4, nullptr);
    const char *picsrc5Path = env->GetStringUTFChars(picsrc5, nullptr);
    const char *picsrc6Path = env->GetStringUTFChars(picsrc6, nullptr);
    const char *picsrc7Path = env->GetStringUTFChars(picsrc7, nullptr);

    if (reflection == nullptr) {
        reflection = new GLSeniorReflection();
    }
    reflection->setSharderPath(vertexPath, fragPath);
    reflection->setSharderScreenPath(vertexScreenPath, fragScreenPath);

    reflection->setPicPath(picsrc1Path);

    reflection->setSkyBoxPicPath(picsrc2Path, picsrc3Path, picsrc4Path, picsrc5Path, picsrc6Path,
                                 picsrc7Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(fragScreen, fragScreenPath);
    env->ReleaseStringUTFChars(vertexScreen, vertexScreenPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);
    env->ReleaseStringUTFChars(picsrc3, picsrc3Path);
    env->ReleaseStringUTFChars(picsrc4, picsrc4Path);
    env->ReleaseStringUTFChars(picsrc5, picsrc5Path);
    env->ReleaseStringUTFChars(picsrc6, picsrc6Path);
    env->ReleaseStringUTFChars(picsrc7, picsrc7Path);

}


extern "C"
JNIEXPORT void JNICALL
cpp_reflection_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (reflection == nullptr) return;
    reflection->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_reflection_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                        jfloat focusY,
                        jint actionMode) {
    if (reflection == nullptr) return;
    reflection->setOnScale(scaleFactor, focusX, focusY, actionMode);
}


/*********************** GL 立方体贴图********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_cube_map_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (cubeMap == nullptr)
        cubeMap = new GLSeniorCubeMap();
    cubeMap->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_cube_map_render_frame(JNIEnv *env, jobject thiz) {
    if (cubeMap == nullptr) return;
    cubeMap->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_cube_map_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                              jstring fragScreen, jstring vertexScreen, jstring picsrc1,
                              jstring picsrc2, jstring picsrc3, jstring picsrc4,
                              jstring picsrc5, jstring picsrc6, jstring picsrc7

) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragScreenPath = env->GetStringUTFChars(fragScreen, nullptr);
    const char *vertexScreenPath = env->GetStringUTFChars(vertexScreen, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);
    const char *picsrc3Path = env->GetStringUTFChars(picsrc3, nullptr);
    const char *picsrc4Path = env->GetStringUTFChars(picsrc4, nullptr);
    const char *picsrc5Path = env->GetStringUTFChars(picsrc5, nullptr);
    const char *picsrc6Path = env->GetStringUTFChars(picsrc6, nullptr);
    const char *picsrc7Path = env->GetStringUTFChars(picsrc7, nullptr);

    if (cubeMap == nullptr) {
        cubeMap = new GLSeniorCubeMap();
    }
    cubeMap->setSharderPath(vertexPath, fragPath);
    cubeMap->setSharderScreenPath(vertexScreenPath, fragScreenPath);

    cubeMap->setPicPath(picsrc1Path);

    cubeMap->setSkyBoxPicPath(picsrc2Path, picsrc3Path, picsrc4Path, picsrc5Path, picsrc6Path,
                              picsrc7Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(fragScreen, fragScreenPath);
    env->ReleaseStringUTFChars(vertexScreen, vertexScreenPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);
    env->ReleaseStringUTFChars(picsrc3, picsrc3Path);
    env->ReleaseStringUTFChars(picsrc4, picsrc4Path);
    env->ReleaseStringUTFChars(picsrc5, picsrc5Path);
    env->ReleaseStringUTFChars(picsrc6, picsrc6Path);
    env->ReleaseStringUTFChars(picsrc7, picsrc7Path);

}


extern "C"
JNIEXPORT void JNICALL
cpp_cube_map_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (cubeMap == nullptr) return;
    cubeMap->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_cube_map_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                      jfloat focusY,
                      jint actionMode) {
    if (cubeMap == nullptr) return;
    cubeMap->setOnScale(scaleFactor, focusX, focusY, actionMode);
}


/*********************** GL 帧缓冲FBO——后期处理********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_fbo_post_processing_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (postProcessing == nullptr)
        postProcessing = new GLFBOPostProcessing();
    postProcessing->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_fbo_post_processing_render_frame(JNIEnv *env, jobject thiz) {
    if (postProcessing == nullptr) return;
    postProcessing->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_fbo_post_processing_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                                         jstring fragScreen, jstring vertexScreen, jstring picsrc1,
                                         jstring picsrc2, jstring fragGrayScale,
                                         jstring fragWeightedGray, jstring fragNuclearEffect
) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragScreenPath = env->GetStringUTFChars(fragScreen, nullptr);
    const char *vertexScreenPath = env->GetStringUTFChars(vertexScreen, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    const char *fragGrayScalePath = env->GetStringUTFChars(fragGrayScale, nullptr);
    const char *fragWeightedGrayPath = env->GetStringUTFChars(fragWeightedGray, nullptr);
    const char *fragNuclearEffectPath = env->GetStringUTFChars(fragNuclearEffect, nullptr);

    if (postProcessing == nullptr) {
        postProcessing = new GLFBOPostProcessing();
    }
    postProcessing->setSharderPath(vertexPath, fragPath);

    string sVertexScreenPath(vertexScreenPath);
    string sFragScreenPath(fragScreenPath);
    string sFragGrayScalePath(fragGrayScalePath);
    string sFragWeightedGrayPath(fragWeightedGrayPath);
    string sFragNuclearEffectPath(fragNuclearEffectPath);

    vector<string> sFragPathes;

    sFragPathes.push_back(sFragScreenPath);
    sFragPathes.push_back(sFragGrayScalePath);
    sFragPathes.push_back(sFragWeightedGrayPath);
    sFragPathes.push_back(sFragNuclearEffectPath);

    postProcessing->setSharderScreenPathes(sVertexScreenPath, sFragPathes);

    postProcessing->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(fragScreen, fragScreenPath);
    env->ReleaseStringUTFChars(vertexScreen, vertexScreenPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}


extern "C"
JNIEXPORT void JNICALL
cpp_fbo_post_processing_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (postProcessing == nullptr) return;
    postProcessing->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_fbo_post_processing_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                                 jfloat focusY,
                                 jint actionMode) {
    if (postProcessing == nullptr) return;
    postProcessing->setOnScale(scaleFactor, focusX, focusY, actionMode);

}

extern "C"
JNIEXPORT void JNICALL
cpp_fbo_post_processing_setParameters(JNIEnv *env, jobject thiz, jint p) {
    if (postProcessing != nullptr) {
        postProcessing->setParameters((uint32_t) p);
    }

}

extern "C"
JNIEXPORT jint JNICALL
cpp_fbo_post_processing_getParameters(JNIEnv *env, jobject thiz) {
    if (postProcessing != nullptr) {
        return postProcessing->getParameters();
    }
    return 0;

}

/*********************** GL 帧缓冲FBO********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_fbo_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (fbo == nullptr)
        fbo = new GLSeniorFBO();
    fbo->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_fbo_render_frame(JNIEnv *env, jobject thiz) {
    if (fbo == nullptr) return;
    fbo->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_fbo_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                         jstring fragScreen, jstring vertexScreen, jstring picsrc1,
                         jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragScreenPath = env->GetStringUTFChars(fragScreen, nullptr);
    const char *vertexScreenPath = env->GetStringUTFChars(vertexScreen, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    if (fbo == nullptr) {
        fbo = new GLSeniorFBO();
    }
    fbo->setSharderPath(vertexPath, fragPath);
    fbo->setSharderScreenPath(vertexScreenPath, fragScreenPath);

    fbo->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(fragScreen, fragScreenPath);
    env->ReleaseStringUTFChars(vertexScreen, vertexScreenPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}


extern "C"
JNIEXPORT void JNICALL
cpp_fbo_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (fbo == nullptr) return;
    fbo->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_fbo_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                 jfloat focusY,
                 jint actionMode) {
    if (fbo == nullptr) return;
    fbo->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL 混合--排序********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_blending_sort_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (blendingSort == nullptr)
        blendingSort = new GLSeniorBlendingSort();
    blendingSort->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_blending_sort_render_frame(JNIEnv *env, jobject thiz) {
    if (blendingSort == nullptr) return;
    blendingSort->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_blending_sort_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                                   jstring picsrc1, jstring picsrc2, jstring picsrc3) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);
    const char *picsrc3Path = env->GetStringUTFChars(picsrc3, nullptr);

    if (blendingSort == nullptr) {
        blendingSort = new GLSeniorBlendingSort();
    }
    blendingSort->setSharderPath(vertexPath, fragPath);

    blendingSort->setPicPath(picsrc1Path, picsrc2Path, picsrc3Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);
    env->ReleaseStringUTFChars(picsrc3, picsrc3Path);

}


extern "C"
JNIEXPORT void JNICALL
cpp_blending_sort_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (blendingSort == nullptr) return;
    blendingSort->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_blending_sort_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                           jfloat focusY,
                           jint actionMode) {
    if (blendingSort == nullptr) return;
    blendingSort->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL 混合--丢弃********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_blending_discard_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (blendingDiscard == nullptr)
        blendingDiscard = new GLSeniorBlendingDiscard();
    blendingDiscard->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_blending_discard_render_frame(JNIEnv *env, jobject thiz) {
    if (blendingDiscard == nullptr) return;
    blendingDiscard->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_blending_discard_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                                      jstring picsrc1, jstring picsrc2, jstring picsrc3) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);
    const char *picsrc3Path = env->GetStringUTFChars(picsrc3, nullptr);

    if (blendingDiscard == nullptr) {
        blendingDiscard = new GLSeniorBlendingDiscard();
    }
    blendingDiscard->setSharderPath(vertexPath, fragPath);

    blendingDiscard->setPicPath(picsrc1Path, picsrc2Path, picsrc3Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);
    env->ReleaseStringUTFChars(picsrc3, picsrc3Path);

}


extern "C"
JNIEXPORT void JNICALL
cpp_blending_discard_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (blendingDiscard == nullptr) return;
    blendingDiscard->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_blending_discard_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                              jfloat focusY,
                              jint actionMode) {
    if (blendingDiscard == nullptr) return;
    blendingDiscard->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL 模版测试********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_stencil_test_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (stencilTest == nullptr)
        stencilTest = new GLSeniorStencilTest();
    stencilTest->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_stencil_test_render_frame(JNIEnv *env, jobject thiz) {
    if (stencilTest == nullptr) return;
    stencilTest->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_stencil_test_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                                  jstring picsrc1, jstring picsrc2, jstring singleColorfrag) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);
    const char *singleColorfragPath = env->GetStringUTFChars(singleColorfrag, nullptr);

    if (stencilTest == nullptr) {
        stencilTest = new GLSeniorStencilTest();
    }
    stencilTest->setSharderPath(vertexPath, fragPath);
    stencilTest->setSingleColorSharderPath(vertexPath, singleColorfragPath);

    stencilTest->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);
    env->ReleaseStringUTFChars(singleColorfrag, singleColorfragPath);

}


extern "C"
JNIEXPORT void JNICALL
cpp_stencil_test_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (stencilTest == nullptr) return;
    stencilTest->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_stencil_test_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                          jfloat focusY,
                          jint actionMode) {
    if (stencilTest == nullptr) return;
    stencilTest->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL 深度测试********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_depth_test_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (depthTest == nullptr)
        depthTest = new GLSeniorDepthTest();
    depthTest->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_depth_test_render_frame(JNIEnv *env, jobject thiz) {
    if (depthTest == nullptr) return;
    depthTest->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_depth_test_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                                jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    if (depthTest == nullptr) {
        depthTest = new GLSeniorDepthTest();
    }
    depthTest->setSharderPath(vertexPath, fragPath);

    depthTest->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}


extern "C"
JNIEXPORT void JNICALL
cpp_depth_test_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (depthTest == nullptr) return;
    depthTest->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_depth_test_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                        jfloat focusY,
                        jint actionMode) {
    if (depthTest == nullptr) return;
    depthTest->setOnScale(scaleFactor, focusX, focusY, actionMode);
}


// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod methods[] = {

        /*********************** GL 3d模型显示********************/
        {"native_asteroid_init_opengl",               "(II)Z",                 (void *) cpp_asteroid_init_opengl},
        {"native_asteroid_render_frame",              "()V",                   (void *) cpp_asteroid_render_frame},
        {"native_asteroid_set_glsl_path",             "(Ljava/lang/String;"
                                                      "Ljava/lang/String;"
                                                      ")V",
                                                                               (void *) cpp_asteroid_frag_vertex_path},
        {"native_asteroid_set_model_path",            "(Ljava/lang/String;"
                                                      "Ljava/lang/String;"
                                                      ")V",
                                                                               (void *) cpp_asteroid_model_path},
        {"native_asteroid_move_xy",                   "(FFI)V",                (void *) cpp_asteroid_show_move_xy},
        {"native_asteroid_on_scale",                  "(FFFI)V",               (void *) cpp_asteroid_show_on_scale},

        /*********************** GL 实例化*******************/
        {"native_instance_init_opengl",               "(II)Z",                 (void *) cpp_instance_init_opengl},
        {"native_instance_render_frame",              "()V",                   (void *) cpp_instance_render_frame},
        {"native_instance_set_glsl_path",             "(Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_instance_frag_vertex_path},
        {"native_instance_move_xy",                   "(FFI)V",                (void *) cpp_instance_move_xy},
        {"native_instance_on_scale",                  "(FFFI)V",               (void *) cpp_instance_on_scale},

        /*********************** GL 几何着色器********************/
        {"native_geometry_init_opengl",               "(II)Z",                 (void *) cpp_geometry_init_opengl},
        {"native_geometry_render_frame",              "()V",                   (void *) cpp_geometry_render_frame},
        {"native_geometry_set_glsl_path",             "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_geometry_frag_vertex_path},
        {"native_geometry_move_xy",                   "(FFI)V",                (void *) cpp_geometry_move_xy},
        {"native_geometry_on_scale",                  "(FFFI)V",               (void *) cpp_geometry_on_scale},

        /*********************** GL 高级Uniform********************/
        {"native_uniform_init_opengl",                "(II)Z",                 (void *) cpp_uniform_init_opengl},
        {"native_uniform_render_frame",               "()V",                   (void *) cpp_uniform_render_frame},
        {"native_uniform_set_glsl_path",              "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_uniform_frag_vertex_path},
        {"native_uniform_move_xy",                    "(FFI)V",                (void *) cpp_uniform_move_xy},
        {"native_uniform_on_scale",                   "(FFFI)V",               (void *) cpp_uniform_on_scale},

        /*********************** GL 立方体贴图——反射********************/
        {"native_reflection_init_opengl",             "(II)Z",                 (void *) cpp_reflection_init_opengl},
        {"native_reflection_render_frame",            "()V",                   (void *) cpp_reflection_render_frame},
        {"native_reflection_set_glsl_path",           "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_reflection_frag_vertex_path},
        {"native_reflection_move_xy",                 "(FFI)V",                (void *) cpp_reflection_move_xy},
        {"native_reflection_on_scale",                "(FFFI)V",               (void *) cpp_reflection_on_scale},

        /*********************** GL 立方体贴图********************/
        {"native_cube_map_init_opengl",               "(II)Z",                 (void *) cpp_cube_map_init_opengl},
        {"native_cube_map_render_frame",              "()V",                   (void *) cpp_cube_map_render_frame},
        {"native_cube_map_set_glsl_path",             "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_cube_map_frag_vertex_path},
        {"native_cube_map_move_xy",                   "(FFI)V",                (void *) cpp_cube_map_move_xy},
        {"native_cube_map_on_scale",                  "(FFFI)V",               (void *) cpp_cube_map_on_scale},


        /*********************** GL 帧缓冲FBO——后期处理********************/
        {"native_fbo_post_processing_init_opengl",    "(II)Z",                 (void *) cpp_fbo_post_processing_init_opengl},
        {"native_fbo_post_processing_render_frame",   "()V",                   (void *) cpp_fbo_post_processing_render_frame},
        {"native_fbo_post_processing_set_glsl_path",  "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_fbo_post_processing_frag_vertex_path},
        {"native_fbo_post_processing_move_xy",        "(FFI)V",                (void *) cpp_fbo_post_processing_move_xy},
        {"native_fbo_post_processing_on_scale",       "(FFFI)V",               (void *) cpp_fbo_post_processing_on_scale},
        {"native_fbo_post_processing_set_parameters", "(I)V",                  (void *) cpp_fbo_post_processing_setParameters},
        {"native_fbo_post_processing_get_parameters", "()I",                   (void *) cpp_fbo_post_processing_getParameters},

        /*********************** GL 帧缓冲FBO********************/
        {"native_fbo_init_opengl",                    "(II)Z",                 (void *) cpp_fbo_init_opengl},
        {"native_fbo_render_frame",                   "()V",                   (void *) cpp_fbo_render_frame},
        {"native_fbo_set_glsl_path",                  "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_fbo_frag_vertex_path},
        {"native_fbo_move_xy",                        "(FFI)V",                (void *) cpp_fbo_move_xy},
        {"native_fbo_on_scale",                       "(FFFI)V",               (void *) cpp_fbo_on_scale},

        /*********************** GL 混合--排序********************/
        {"native_blending_sort_init_opengl",          "(II)Z",                 (void *) cpp_blending_sort_init_opengl},
        {"native_blending_sort_render_frame",         "()V",                   (void *) cpp_blending_sort_render_frame},
        {"native_blending_sort_set_glsl_path",        "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_blending_sort_frag_vertex_path},
        {"native_blending_sort_move_xy",              "(FFI)V",                (void *) cpp_blending_sort_move_xy},
        {"native_blending_sort_on_scale",             "(FFFI)V",               (void *) cpp_blending_sort_on_scale},

        /*********************** GL 混合--丢弃********************/
        {"native_blending_discard_init_opengl",       "(II)Z",                 (void *) cpp_blending_discard_init_opengl},
        {"native_blending_discard_render_frame",      "()V",                   (void *) cpp_blending_discard_render_frame},
        {"native_blending_discard_set_glsl_path",     "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_blending_discard_frag_vertex_path},
        {"native_blending_discard_move_xy",           "(FFI)V",                (void *) cpp_blending_discard_move_xy},
        {"native_blending_discard_on_scale",          "(FFFI)V",               (void *) cpp_blending_discard_on_scale},

        /*********************** GL 模版测试********************/
        {"native_stencil_test_init_opengl",           "(II)Z",                 (void *) cpp_stencil_test_init_opengl},
        {"native_stencil_test_render_frame",          "()V",                   (void *) cpp_stencil_test_render_frame},
        {"native_stencil_test_set_glsl_path",         "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_stencil_test_frag_vertex_path},
        {"native_stencil_test_move_xy",               "(FFI)V",                (void *) cpp_stencil_test_move_xy},
        {"native_stencil_test_on_scale",              "(FFFI)V",               (void *) cpp_stencil_test_on_scale},

        /*********************** GL 深度测试********************/
        {"native_depth_test_init_opengl",             "(II)Z",                 (void *) cpp_depth_test_init_opengl},
        {"native_depth_test_render_frame",            "()V",                   (void *) cpp_depth_test_render_frame},
        {"native_depth_test_set_glsl_path",           "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_depth_test_frag_vertex_path},
        {"native_depth_test_move_xy",                 "(FFI)V",                (void *) cpp_depth_test_move_xy},
        {"native_depth_test_on_scale",                "(FFFI)V",               (void *) cpp_depth_test_on_scale},


};





/**
 * 定义注册方法
 * @param vm
 * @param reserved
 * @return
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("动态注册");
    JNIEnv *env;
    if ((vm)->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGD("动态注册GetEnv  fail");
        return JNI_ERR;
    }
    // 获取类引用
    jclass clazz = env->FindClass(glshader_class_name);
    // 注册native方法
    jint regist_result = env->RegisterNatives(clazz, methods,
                                              sizeof(methods) / sizeof(methods[0]));
    if (regist_result) { // 非零true 进if
        LOGE("动态注册 fail regist_result = %d", regist_result);
    } else {
        LOGI("动态注册 success result = %d", regist_result);
    }
    return JNI_VERSION_1_6;
}

