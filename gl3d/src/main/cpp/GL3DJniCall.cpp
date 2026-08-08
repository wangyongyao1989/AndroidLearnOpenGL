#include <jni.h>
#include <string>
#include <android/log.h>
#include "GL3DLogUtils.h"
#include "GL3DFlashLight.h"
#include "GL3DShow.h"
#include "GLDrawText.h"
#include "GL3DAnimationShow.h"

//包名+类名字符串定义：
const char *algoritm_draw_class_name = "com/wangyongyao/gl3d/GL3DCallJni";

GL3DFlashLight *flashLight;
GL3DShow *gl3DShow;
GLDrawText *glDrawText;
GL3DAnimationShow *gl3DAnimation;

/*********************** GL 聚光手电筒********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_flash_light_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (flashLight == nullptr)
        flashLight = new GL3DFlashLight();
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
        flashLight = new GL3DFlashLight();
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
        flashLight = new GL3DFlashLight();
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

/*********************** GL 3d模型显示********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_3d_animation_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (gl3DAnimation == nullptr)
        gl3DAnimation = new GL3DAnimationShow();
    gl3DAnimation->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_3d_animation_render_frame(JNIEnv *env, jobject thiz) {
    if (gl3DAnimation == nullptr) return;
    gl3DAnimation->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_3d_animation_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    if (gl3DAnimation == nullptr) {
        gl3DAnimation = new GL3DAnimationShow();
    }

    gl3DAnimation->setSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}

extern "C"
JNIEXPORT void JNICALL
cpp_3d_animation_model_path(JNIEnv *env, jobject thiz, jstring model) {
    const char *modelPath = env->GetStringUTFChars(model, nullptr);
    if (gl3DAnimation == nullptr) {
        gl3DAnimation = new GL3DAnimationShow();
    }

    gl3DAnimation->setModelPath(modelPath);

    env->ReleaseStringUTFChars(model, modelPath);

}


extern "C"
JNIEXPORT void JNICALL
cpp_3d_animation_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (gl3DAnimation == nullptr) return;
    gl3DAnimation->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_3d_animation_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                     jfloat focusY,
                     jint actionMode) {
    if (gl3DAnimation == nullptr) return;
    gl3DAnimation->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL 3d模型显示********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_3dshow_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (gl3DShow == nullptr)
        gl3DShow = new GL3DShow();
    gl3DShow->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_3dshow_render_frame(JNIEnv *env, jobject thiz) {
    if (gl3DShow == nullptr) return;
    gl3DShow->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_3dshow_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    if (gl3DShow == nullptr) {
        gl3DShow = new GL3DShow();
    }

    gl3DShow->setSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}

extern "C"
JNIEXPORT void JNICALL
cpp_3dshow_model_path(JNIEnv *env, jobject thiz, jstring model) {
    const char *modelPath = env->GetStringUTFChars(model, nullptr);
    if (gl3DShow == nullptr) {
        gl3DShow = new GL3DShow();
    }

    gl3DShow->setModelPath(modelPath);

    env->ReleaseStringUTFChars(model, modelPath);

}


extern "C"
JNIEXPORT void JNICALL
cpp_3d_show_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (gl3DShow == nullptr) return;
    gl3DShow->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_3d_show_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                     jfloat focusY,
                     jint actionMode) {
    if (gl3DShow == nullptr) return;
    gl3DShow->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL 文本绘制********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_draw_text_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height, jstring path) {
    if (glDrawText == nullptr)
        glDrawText = new GLDrawText();
    const char *typePath = env->GetStringUTFChars(path, nullptr);

    glDrawText->setupGraphics(width, height, typePath);

    env->ReleaseStringUTFChars(path, typePath);

    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_draw_text_render_frame(JNIEnv *env, jobject thiz) {
    if (glDrawText == nullptr) return;
    glDrawText->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_draw_text_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    if (glDrawText == nullptr) {
        glDrawText = new GLDrawText();
    }

    glDrawText->setSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}


// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod methods[] = {

        /*********************** GL 3d骨骼动画********************/
        {"native_3d_animation_init_opengl",                  "(II)Z",                   (void *) cpp_3d_animation_init_opengl},
        {"native_3d_animation_render_frame",                 "()V",                     (void *) cpp_3d_animation_render_frame},
        {"native_3d_animation_set_glsl_path",                "(Ljava/lang/String;"
                                                   "Ljava/lang/String;"
                                                   ")V",
                                                                              (void *) cpp_3d_animation_frag_vertex_path},
        {"native_3d_animation_set_model_path",               "(Ljava/lang/String;)V",
                                                                              (void *) cpp_3d_animation_model_path},
        {"native_3d_animation_move_xy",                      "(FFI)V",                  (void *) cpp_3d_animation_move_xy},
        {"native_3d_animation_on_scale",                     "(FFFI)V",                 (void *) cpp_3d_animation_on_scale},

        /*********************** GL 文本绘制********************/
        {"native_draw_text_init_opengl",           "(IILjava/lang/String;)Z", (void *) cpp_draw_text_init_opengl},
        {"native_draw_text_render_frame",          "()V",                     (void *) cpp_draw_text_render_frame},
        {"native_draw_text_set_glsl_path",         "(Ljava/lang/String;"
                                                   "Ljava/lang/String;"
                                                   ")V",
                                                                              (void *) cpp_draw_text_frag_vertex_path},


        /*********************** GL 3d模型显示********************/
        {"native_3d_init_opengl",                  "(II)Z",                   (void *) cpp_3dshow_init_opengl},
        {"native_3d_render_frame",                 "()V",                     (void *) cpp_3dshow_render_frame},
        {"native_3d_set_glsl_path",                "(Ljava/lang/String;"
                                                   "Ljava/lang/String;"
                                                   ")V",
                                                                              (void *) cpp_3dshow_frag_vertex_path},
        {"native_3d_set_model_path",               "(Ljava/lang/String;)V",
                                                                              (void *) cpp_3dshow_model_path},
        {"native_3d_move_xy",                      "(FFI)V",                  (void *) cpp_3d_show_move_xy},
        {"native_3d_on_scale",                     "(FFFI)V",                 (void *) cpp_3d_show_on_scale},


        /*********************** GL 聚光手电筒********************/
        {"native_flash_light_init_opengl",         "(II)Z",                   (void *) cpp_flash_light_init_opengl},
        {"native_flash_light_render_frame",        "()V",                     (void *) cpp_flash_light_render_frame},
        {"native_flash_light_color_set_glsl_path", "(Ljava/lang/String"
                                                   ";Ljava/lang/String;)V",   (void *) cpp_flash_light_color_frag_vertex_path},
        {"native_flash_light_set_glsl_path",       "(Ljava/lang/String"
                                                   ";Ljava/lang/String"
                                                   ";Ljava/lang/String"
                                                   ";Ljava/lang/String;)V",   (void *) cpp_flash_light_frag_vertex_path},
        {"native_flash_light_move_xy",             "(FFI)V",                  (void *) cpp_flash_light_move_xy},
        {"native_flash_light_on_scale",            "(FFFI)V",                 (void *) cpp_flash_light_on_scale},

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
    jclass clazz = env->FindClass(algoritm_draw_class_name);
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

