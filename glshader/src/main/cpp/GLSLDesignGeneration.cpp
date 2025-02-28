//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/28.
//

#include <jni.h>
#include <string>
#include <android/log.h>
#include "GLSLLogUtils.h"
#include "GLSLRandomFunction.h"

GLSLRandomFunction *randomFunction;

//包名+类名字符串定义：
const char *design_generation_class_name = "com/wangyongyao/glsl/GLSLDGCallJni";


/*********************  着色器 图案 Patterns *****************/

extern "C"
JNIEXPORT void JNICALL
cpp_random_glsl_path(JNIEnv *env, jobject thiz, jstring vertex, jstring frag1,
                     jstring frag2,
                     jstring frag3,
                     jstring frag4


) {
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragPath1 = env->GetStringUTFChars(frag1, nullptr);
    const char *fragPath2 = env->GetStringUTFChars(frag2, nullptr);
    const char *fragPath3 = env->GetStringUTFChars(frag3, nullptr);
    const char *fragPath4 = env->GetStringUTFChars(frag4, nullptr);


    if (randomFunction == nullptr) {
        randomFunction = new GLSLRandomFunction();
    }
    string sFragPath1(fragPath1);
    string sFragPath2(fragPath2);
    string sFragPath3(fragPath3);
    string sFragPath4(fragPath4);

    vector<string> sFragPathes;
    sFragPathes.push_back(sFragPath1);
    sFragPathes.push_back(sFragPath2);
    sFragPathes.push_back(sFragPath3);
    sFragPathes.push_back(sFragPath4);

    randomFunction->setSharderStringPathes(vertexPath, sFragPathes);

    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(frag1, fragPath1);
    env->ReleaseStringUTFChars(frag2, fragPath2);
    env->ReleaseStringUTFChars(frag3, fragPath3);
    env->ReleaseStringUTFChars(frag4, fragPath4);

}

extern "C"
JNIEXPORT void JNICALL
cpp_random_render_frame(JNIEnv *env, jobject thiz) {
    if (randomFunction == nullptr) {
        LOGE("GLrandomFunction is nullptr");
        return;
    }
    randomFunction->renderFrame();
}

extern "C"
JNIEXPORT void JNICALL
cpp_random_init(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (randomFunction == nullptr) {
        LOGE("GLrandomFunction is nullptr");
        return;
    }
    randomFunction->setupGraphics(width, height);
}
extern "C"
JNIEXPORT void JNICALL
cpp_random_set_type(JNIEnv *env, jobject thiz, jint type) {
    if (randomFunction == nullptr) {
        LOGE("GLrandomFunction is nullptr");
        return;
    }
    randomFunction->setParameters(type);

}

extern "C"
JNIEXPORT jint JNICALL
cpp_random_get_type(JNIEnv *env, jobject thiz) {
    if (randomFunction == nullptr) {
        LOGE("GLrandomFunction is nullptr");
        return 0;
    }
    return randomFunction->getParameters();
}


// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod DGMethods[] = {

        /*********************  着色器 图案 Patterns *****************/
        {"native_random_set_glsl_path", "(Ljava/lang/String;"
                                        "Ljava/lang/String;"
                                        "Ljava/lang/String;"
                                        "Ljava/lang/String;"
                                        "Ljava/lang/String;)V", (void *) cpp_random_glsl_path},
        {"native_random_init",          "(II)V",                (void *) cpp_random_init},
        {"native_random_render_frame",  "()V",                  (void *) cpp_random_render_frame},
        {"native_random_set_type",      "(I)V",                 (void *) cpp_random_set_type},
        {"native_random_get_type",      "()I",                  (void *) cpp_random_get_type},


};

void registerClassDesignGeneration(JNIEnv *env) {
    jclass clazz = env->FindClass(design_generation_class_name);
    if (clazz) {
        int methodCount = sizeof(DGMethods) / sizeof(JNINativeMethod);
        env->RegisterNatives(clazz, DGMethods, methodCount);
        env->DeleteLocalRef(clazz);
    }
}