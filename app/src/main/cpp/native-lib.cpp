#include <jni.h>
#include <string>
#include <android/log.h>
#include "OpenglesFoundation.h"
#include "OpenglesTexture.h"


#define LOG_TAG "wy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

const char *mainactivity_class_name = "com/wangyongyao/androidlearnopengl/JniCall";
OpenglesFoundation *openglesFoundation;
OpenglesTexture *openglTexture;

extern "C" JNIEXPORT jstring JNICALL
cpp_stringFromJNI(
        JNIEnv *env, jobject) {
    std::string hello = "Hello from C++";
    LOGD("cpp_stringFromJNI  hello = %c", hello.c_str());
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
cpp_init_callback(JNIEnv *env, jobject thiz) {


}

/*********************** Foundation *********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_foundation_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (openglesFoundation == nullptr)
        openglesFoundation = new OpenglesFoundation();
    openglesFoundation->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_foundation_render_frame(JNIEnv *env, jobject thiz) {
    if (openglesFoundation == nullptr) return;
    openglesFoundation->renderFrame();


}

extern "C"
JNIEXPORT void JNICALL
cpp_foundation_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, 0);
    const char *vertexPath = env->GetStringUTFChars(vertex, 0);
    if (openglesFoundation == nullptr) {
        openglesFoundation = new OpenglesFoundation();
    }
    openglesFoundation->setSharderPath(vertexPath, fragPath);
    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}

/*********************** Texture *********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_texture_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (openglTexture == nullptr)
        openglTexture = new OpenglesTexture();
    openglTexture->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_texture_render_frame(JNIEnv *env, jobject thiz) {
    if (openglTexture == nullptr) return;
    openglTexture->renderFrame();


}

extern "C"
JNIEXPORT void JNICALL
cpp_texture_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                             jstring picsrc) {
    const char *fragPath = env->GetStringUTFChars(frag, 0);
    const char *vertexPath = env->GetStringUTFChars(vertex, 0);
    const char *picsrcPath = env->GetStringUTFChars(picsrc, 0);

    if (openglTexture == nullptr) {
        openglTexture = new OpenglesTexture();
    }
    openglTexture->setSharderPath(vertexPath, fragPath);
    openglTexture->setPicPath(picsrcPath);
    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc, picsrcPath);


}

// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod methods[] = {
        {"stringFromJNI",                   "()Ljava/lang/String;",                                      (std::string *) cpp_stringFromJNI},
        {"native_callback",                 "()V",                                                       (void *) cpp_init_callback},
        //Foundation
        {"native_foundation_init_opengl",   "(II)Z",                                                     (void *) cpp_foundation_init_opengl},
        {"native_foundation_render_frame",  "()V",                                                       (void *) cpp_foundation_render_frame},
        {"native_foundation_set_glsl_path", "(Ljava/lang/String;Ljava/lang/String;)V",                   (void *) cpp_foundation_frag_vertex_path},
        //Texture
        {"native_texture_init_opengl",      "(II)Z",                                                     (void *) cpp_texture_init_opengl},
        {"native_texture_render_frame",     "()V",                                                       (void *) cpp_texture_render_frame},
        {"native_texture_set_glsl_path",    "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V", (void *) cpp_texture_frag_vertex_path},
};


// 定义注册方法
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    LOGD("动态注册");
    JNIEnv *env;
    if ((vm)->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGD("动态注册GetEnv  fail");
        return JNI_ERR;
    }

    // 获取类引用
    jclass clazz = env->FindClass(mainactivity_class_name);

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
