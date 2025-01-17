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

//包名+类名字符串定义：
const char *gl3d_class_name = "com/wangyongyao/GLSeniorCallJni";

GLSeniorDepthTest *depthTest;
GLSeniorStencilTest *stencilTest;
GLSeniorBlendingDiscard *blendingDiscard;
GLSeniorBlendingSort *blendingSort;
GLSeniorFBO *fbo;
GLFBOPostProcessing *postProcessing;
GLSeniorCubeMap *cubeMap;


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
                         jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragScreenPath = env->GetStringUTFChars(fragScreen, nullptr);
    const char *vertexScreenPath = env->GetStringUTFChars(vertexScreen, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    if (cubeMap == nullptr) {
        cubeMap = new GLSeniorCubeMap();
    }
    cubeMap->setSharderPath(vertexPath, fragPath);
    cubeMap->setSharderScreenPath(vertexScreenPath, fragScreenPath);

    cubeMap->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(fragScreen, fragScreenPath);
    env->ReleaseStringUTFChars(vertexScreen, vertexScreenPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

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


        /*********************** GL 立方体贴图********************/
        {"native_cube_map_init_opengl",                    "(II)Z",                 (void *) cpp_cube_map_init_opengl},
        {"native_cube_map_render_frame",                   "()V",                   (void *) cpp_cube_map_render_frame},
        {"native_cube_map_set_glsl_path",                  "(Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String"
                                                      ";Ljava/lang/String;)V", (void *) cpp_cube_map_frag_vertex_path},
        {"native_cube_map_move_xy",                        "(FFI)V",                (void *) cpp_cube_map_move_xy},
        {"native_cube_map_on_scale",                       "(FFFI)V",               (void *) cpp_cube_map_on_scale},


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
    jclass clazz = env->FindClass(gl3d_class_name);
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

