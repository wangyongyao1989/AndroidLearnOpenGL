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
cpp_shaping_funceions_glsl_path(JNIEnv *env, jobject thiz, jstring vertex, jstring frag1,
                                jstring frag2,
                                jstring frag3

) {
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragPath1 = env->GetStringUTFChars(frag1, nullptr);
    const char *fragPath2 = env->GetStringUTFChars(frag2, nullptr);
    const char *fragPath3 = env->GetStringUTFChars(frag3, nullptr);


    if (shapingFunction == nullptr) {
        shapingFunction = new GLShapingFunction();
    }
    string sFragPath1(fragPath1);
    string sFragPath2(fragPath2);
    string sFragPath3(fragPath3);

    vector<string> sFragPathes;
    sFragPathes.push_back(sFragPath1);
    sFragPathes.push_back(sFragPath2);
    sFragPathes.push_back(sFragPath3);


    shapingFunction->setSharderStringPathes(vertexPath, sFragPathes);

    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(frag1, fragPath1);
    env->ReleaseStringUTFChars(frag2, fragPath2);
    env->ReleaseStringUTFChars(frag3, fragPath3);

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
extern "C"
JNIEXPORT void JNICALL
cpp_shaping_funceions_set_type(JNIEnv *env, jobject thiz, jint type) {
    if (shapingFunction == nullptr) {
        LOGE("GLShapingFunction is nullptr");
        return;
    }
    shapingFunction->setParameters(type);

}

extern "C"
JNIEXPORT jint JNICALL
cpp_shaping_funceions_get_type(JNIEnv *env, jobject thiz) {
    if (shapingFunction == nullptr) {
        LOGE("GLShapingFunction is nullptr");
        return 0;
    }
    return shapingFunction->getParameters();
}

// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod methods[] = {

        /*********************** GL Shader 造型函数（Shaping Function）********************/
        {"native_shaping_funceions_set_glsl_path", "(Ljava/lang/String;"
                                                   "Ljava/lang/String;"
                                                   "Ljava/lang/String;"
                                                   "Ljava/lang/String;)V", (void *) cpp_shaping_funceions_glsl_path},
        {"native_shaping_funceions_init",          "(II)V",                (void *) cpp_shaping_funceions_init},
        {"native_shaping_funceions_render_frame",  "()V",                  (void *) cpp_shaping_funceions_render_frame},
        {"native_shaping_funceions_set_type",      "(I)V",                 (void *) cpp_shaping_funceions_set_type},
        {"native_shaping_funceions_get_type",      "()I",                  (void *) cpp_shaping_funceions_get_type},

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

