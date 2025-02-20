#include <jni.h>
#include <string>
#include <android/log.h>
#include "GLSLLogUtils.h"
#include "GLShapingFunction.h"

//包名+类名字符串定义：
const char *gl3d_class_name = "com/wangyongyao/glsl/GLSLCallJni";


GLShapingFunction *shapingFunction;

/*********************** GL Shader 造型函数（Shaping Function）********************/
extern "C"
JNIEXPORT void JNICALL
cpp_shaping_funceions_glsl_path(JNIEnv *env, jobject thiz, jstring vertex, jstring frag) {
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    if (shapingFunction == nullptr) {
        shapingFunction = new GLShapingFunction();
    }
    shapingFunction->setSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(frag, fragPath);

}

extern "C"
JNIEXPORT void JNICALL
cpp_shaping_funceions_render_frame(JNIEnv *env, jobject thiz) {
    if (shapingFunction == nullptr) {
        LOGE("GLShapingFunction is nullptr");
        return;
    }
    shapingFunction->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_shaping_funceions_init(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (shapingFunction == nullptr) {
        LOGE("GLShapingFunction is nullptr");
        return;
    }
    shapingFunction->setupGraphics(width, height);

}


// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod methods[] = {

        /*********************** GL Shader 造型函数（Shaping Function）********************/
        {"native_shaping_funceions_set_glsl_path", "(Ljava/lang/String"
                                                   ";Ljava/lang/String;)V", (void *) cpp_shaping_funceions_glsl_path},
        {"native_shaping_funceions_init",          "(II)V",                 (void *) cpp_shaping_funceions_init},
        {"native_shaping_funceions_render_frame",  "()V",                   (void *) cpp_shaping_funceions_render_frame},



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

