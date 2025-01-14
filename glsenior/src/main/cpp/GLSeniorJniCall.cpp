#include <jni.h>
#include <string>
#include <android/log.h>
#include "includes/GLSeniorLogUtils.h"
#include "GLSeniorFlashLight.h"
#include "GLSeniorDepthTest.h"
#include "GLSeniorStencilTest.h"

//包名+类名字符串定义：
const char *gl3d_class_name = "com/wangyongyao/GLSeniorCallJni";

GLSeniorFlashLight *flashLight;
GLSeniorDepthTest *depthTest;
GLSeniorStencilTest *stencilTest;



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

/*********************** GL 聚光手电筒********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_flash_light_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (flashLight == nullptr)
        flashLight = new GLSeniorFlashLight();
    flashLight->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_flash_light_render_frame(JNIEnv *env, jobject thiz) {
    if (flashLight == nullptr) return;
    flashLight->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_flash_light_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                                 jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    if (flashLight == nullptr) {
        flashLight = new GLSeniorFlashLight();
    }
    flashLight->setSharderPath(vertexPath, fragPath);

    flashLight->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}

extern "C"
JNIEXPORT void JNICALL
cpp_flash_light_color_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag,
                                       jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);

    if (flashLight == nullptr) {
        flashLight = new GLSeniorFlashLight();
    }
    flashLight->setColorSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}

extern "C"
JNIEXPORT void JNICALL
cpp_flash_light_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (flashLight == nullptr) return;
    flashLight->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_flash_light_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                         jfloat focusY,
                         jint actionMode) {
    if (flashLight == nullptr) return;
    flashLight->setOnScale(scaleFactor, focusX, focusY, actionMode);
}


// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod methods[] = {

        /*********************** GL 模版测试********************/
        {"native_stencil_test_init_opengl",        "(II)Z",                 (void *) cpp_stencil_test_init_opengl},
        {"native_stencil_test_render_frame",       "()V",                   (void *) cpp_stencil_test_render_frame},
        {"native_stencil_test_set_glsl_path",      "(Ljava/lang/String"
                                                   ";Ljava/lang/String"
                                                   ";Ljava/lang/String"
                                                   ";Ljava/lang/String"
                                                   ";Ljava/lang/String;)V", (void *) cpp_stencil_test_frag_vertex_path},
        {"native_stencil_test_move_xy",            "(FFI)V",                (void *) cpp_stencil_test_move_xy},
        {"native_stencil_test_on_scale",           "(FFFI)V",               (void *) cpp_stencil_test_on_scale},

        /*********************** GL 深度测试********************/
        {"native_depth_test_init_opengl",          "(II)Z",                 (void *) cpp_depth_test_init_opengl},
        {"native_depth_test_render_frame",         "()V",                   (void *) cpp_depth_test_render_frame},
        {"native_depth_test_set_glsl_path",        "(Ljava/lang/String"
                                                   ";Ljava/lang/String"
                                                   ";Ljava/lang/String"
                                                   ";Ljava/lang/String;)V", (void *) cpp_depth_test_frag_vertex_path},
        {"native_depth_test_move_xy",              "(FFI)V",                (void *) cpp_depth_test_move_xy},
        {"native_depth_test_on_scale",             "(FFFI)V",               (void *) cpp_depth_test_on_scale},


        /*********************** GL 聚光手电筒********************/
        {"native_flash_light_init_opengl",         "(II)Z",                 (void *) cpp_flash_light_init_opengl},
        {"native_flash_light_render_frame",        "()V",                   (void *) cpp_flash_light_render_frame},
        {"native_flash_light_color_set_glsl_path", "(Ljava/lang/String"
                                                   ";Ljava/lang/String;)V", (void *) cpp_flash_light_color_frag_vertex_path},
        {"native_flash_light_set_glsl_path",       "(Ljava/lang/String"
                                                   ";Ljava/lang/String"
                                                   ";Ljava/lang/String"
                                                   ";Ljava/lang/String;)V", (void *) cpp_flash_light_frag_vertex_path},
        {"native_flash_light_move_xy",             "(FFI)V",                (void *) cpp_flash_light_move_xy},
        {"native_flash_light_on_scale",            "(FFFI)V",               (void *) cpp_flash_light_on_scale},

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

