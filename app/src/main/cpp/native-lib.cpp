#include <jni.h>
#include <string>
#include <android/log.h>
#include "OpenglesFoundation.h"
#include "OpenglesTexture.h"
#include "Opengles3D.h"
#include "OpenglesCube3D.h"
#include "OpenglesMultiCube3D.h"


#define LOG_TAG "wy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

const char *mainactivity_class_name = "com/wangyongyao/androidlearnopengl/JniCall";
OpenglesFoundation *openglesFoundation;
OpenglesTexture *openglTexture;
Opengles3D *opengl3D;
OpenglesCube3D *openglCube3D;
OpenglesMultiCube3D *openglMultiCube3D;

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
                             jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, 0);
    const char *vertexPath = env->GetStringUTFChars(vertex, 0);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, 0);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, 0);

    if (openglTexture == nullptr) {
        openglTexture = new OpenglesTexture();
    }
    openglTexture->setSharderPath(vertexPath, fragPath);

    openglTexture->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}

/*********************** 3D基础 *********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_3d_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (opengl3D == nullptr)
        opengl3D = new Opengles3D();
    opengl3D->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_3d_render_frame(JNIEnv *env, jobject thiz) {
    if (opengl3D == nullptr) return;
    opengl3D->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_3d_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                        jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, 0);
    const char *vertexPath = env->GetStringUTFChars(vertex, 0);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, 0);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, 0);

    if (opengl3D == nullptr) {
        opengl3D = new Opengles3D();
    }
    opengl3D->setSharderPath(vertexPath, fragPath);

    opengl3D->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}

/*********************** 立方体3D *********************/
extern "C"
JNIEXPORT jboolean JNICALL
cpp_cube_3d_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (openglCube3D == nullptr)
        openglCube3D = new OpenglesCube3D();
    openglCube3D->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_cube_3d_render_frame(JNIEnv *env, jobject thiz) {
    if (openglCube3D == nullptr) return;
    openglCube3D->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_cube_3d_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                             jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, 0);
    const char *vertexPath = env->GetStringUTFChars(vertex, 0);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, 0);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, 0);

    if (openglCube3D == nullptr) {
        openglCube3D = new OpenglesCube3D();
    }
    openglCube3D->setSharderPath(vertexPath, fragPath);

    openglCube3D->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}

/*********************** 多立方体3D *********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_multi_cube_3d_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (openglMultiCube3D == nullptr)
        openglMultiCube3D = new OpenglesMultiCube3D();
    openglMultiCube3D->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_multi_cube_3d_render_frame(JNIEnv *env, jobject thiz) {
    if (openglMultiCube3D == nullptr) return;
    openglMultiCube3D->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_multi_cube_3d_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                             jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, 0);
    const char *vertexPath = env->GetStringUTFChars(vertex, 0);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, 0);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, 0);

    if (openglMultiCube3D == nullptr) {
        openglMultiCube3D = new OpenglesMultiCube3D();
    }
    openglMultiCube3D->setSharderPath(vertexPath, fragPath);

    openglMultiCube3D->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}


// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod methods[] = {
        {"stringFromJNI",                   "()Ljava/lang/String;",  (std::string *) cpp_stringFromJNI},
        {"native_callback",                 "()V",                   (void *) cpp_init_callback},
        //Foundation
        {"native_foundation_init_opengl",   "(II)Z",                 (void *) cpp_foundation_init_opengl},
        {"native_foundation_render_frame",  "()V",                   (void *) cpp_foundation_render_frame},
        {"native_foundation_set_glsl_path", "(Ljava/lang/String;"
                                            "Ljava/lang/String;)V",  (void *) cpp_foundation_frag_vertex_path},
        //Texture
        {"native_texture_init_opengl",      "(II)Z",                 (void *) cpp_texture_init_opengl},
        {"native_texture_render_frame",     "()V",                   (void *) cpp_texture_render_frame},

        {"native_texture_set_glsl_path",    "(Ljava/lang/String"
                                            ";Ljava/lang/String"
                                            ";Ljava/lang/String"
                                            ";Ljava/lang/String;)V", (void *) cpp_texture_frag_vertex_path},
        //3D基础
        {"native_3d_init_opengl",           "(II)Z",                 (void *) cpp_3d_init_opengl},
        {"native_3d_render_frame",          "()V",                   (void *) cpp_3d_render_frame},

        {"native_3d_set_glsl_path",         "(Ljava/lang/String"
                                            ";Ljava/lang/String"
                                            ";Ljava/lang/String"
                                            ";Ljava/lang/String;)V", (void *) cpp_3d_frag_vertex_path},
        //立方体3D
        {"native_cube_3d_init_opengl",      "(II)Z",                 (void *) cpp_cube_3d_init_opengl},
        {"native_cube_3d_render_frame",     "()V",                   (void *) cpp_cube_3d_render_frame},

        {"native_cube_3d_set_glsl_path",    "(Ljava/lang/String"
                                            ";Ljava/lang/String"
                                            ";Ljava/lang/String"
                                            ";Ljava/lang/String;)V", (void *) cpp_cube_3d_frag_vertex_path},
        //立方体3D
        {"native_multi_cube_3d_init_opengl",      "(II)Z",                 (void *) cpp_multi_cube_3d_init_opengl},
        {"native_multi_cube_3d_render_frame",     "()V",                   (void *) cpp_multi_cube_3d_render_frame},

        {"native_multi_cube_3d_set_glsl_path",    "(Ljava/lang/String"
                                            ";Ljava/lang/String"
                                            ";Ljava/lang/String"
                                            ";Ljava/lang/String;)V", (void *) cpp_multi_cube_3d_frag_vertex_path},
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
