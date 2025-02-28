//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/28.
//

#include <jni.h>
#include <string>
#include <android/log.h>
#include "GLSLLogUtils.h"
#include "GLSLRandomFunction.h"
#include "GLNoiseFunction.h"

GLSLRandomFunction *randomFunction;
GLNoiseFunction *noiseFunction;

//包名+类名字符串定义：
const char *design_generation_class_name = "com/wangyongyao/glsl/GLSLDGCallJni";


/*********************** GL Shader 生成设计：噪音********************/
extern "C"
JNIEXPORT void JNICALL
cpp_noise_functions_glsl_path(JNIEnv *env, jobject thiz, jstring vertex, jstring frag1,
                                jstring frag2,
                                jstring frag3,
                                jstring frag4,
                                jstring frag5,
                                jstring frag6,
                                jstring frag7,
                                jstring frag8,
                                jstring frag9,
                                jstring frag10,
                                jstring frag11,
                                jstring frag12,
                                jstring frag13


) {
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragPath1 = env->GetStringUTFChars(frag1, nullptr);
    const char *fragPath2 = env->GetStringUTFChars(frag2, nullptr);
    const char *fragPath3 = env->GetStringUTFChars(frag3, nullptr);
    const char *fragPath4 = env->GetStringUTFChars(frag4, nullptr);
    const char *fragPath5 = env->GetStringUTFChars(frag5, nullptr);
    const char *fragPath6 = env->GetStringUTFChars(frag6, nullptr);
    const char *fragPath7 = env->GetStringUTFChars(frag7, nullptr);
    const char *fragPath8 = env->GetStringUTFChars(frag8, nullptr);
    const char *fragPath9 = env->GetStringUTFChars(frag9, nullptr);
    const char *fragPath10 = env->GetStringUTFChars(frag10, nullptr);
    const char *fragPath11 = env->GetStringUTFChars(frag11, nullptr);
    const char *fragPath12 = env->GetStringUTFChars(frag12, nullptr);
    const char *fragPath13 = env->GetStringUTFChars(frag13, nullptr);


    if (noiseFunction == nullptr) {
        noiseFunction = new GLNoiseFunction();
    }
    string sFragPath1(fragPath1);
    string sFragPath2(fragPath2);
    string sFragPath3(fragPath3);
    string sFragPath4(fragPath4);
    string sFragPath5(fragPath5);
    string sFragPath6(fragPath6);
    string sFragPath7(fragPath7);
    string sFragPath8(fragPath8);
    string sFragPath9(fragPath9);
    string sFragPath10(fragPath10);
    string sFragPath11(fragPath11);
    string sFragPath12(fragPath12);
    string sFragPath13(fragPath13);

    vector<string> sFragPathes;
    sFragPathes.push_back(sFragPath1);
    sFragPathes.push_back(sFragPath2);
    sFragPathes.push_back(sFragPath3);
    sFragPathes.push_back(sFragPath4);
    sFragPathes.push_back(sFragPath5);
    sFragPathes.push_back(sFragPath6);
    sFragPathes.push_back(sFragPath7);
    sFragPathes.push_back(sFragPath8);
    sFragPathes.push_back(sFragPath9);
    sFragPathes.push_back(sFragPath10);
    sFragPathes.push_back(sFragPath11);
    sFragPathes.push_back(sFragPath12);
    sFragPathes.push_back(sFragPath13);


    noiseFunction->setSharderStringPathes(vertexPath, sFragPathes);

    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(frag1, fragPath1);
    env->ReleaseStringUTFChars(frag2, fragPath2);
    env->ReleaseStringUTFChars(frag3, fragPath3);
    env->ReleaseStringUTFChars(frag4, fragPath4);
    env->ReleaseStringUTFChars(frag5, fragPath5);
    env->ReleaseStringUTFChars(frag6, fragPath6);
    env->ReleaseStringUTFChars(frag7, fragPath7);
    env->ReleaseStringUTFChars(frag8, fragPath8);
    env->ReleaseStringUTFChars(frag9, fragPath9);
    env->ReleaseStringUTFChars(frag10, fragPath10);
    env->ReleaseStringUTFChars(frag11, fragPath11);
    env->ReleaseStringUTFChars(frag12, fragPath12);
    env->ReleaseStringUTFChars(frag13, fragPath13);

}

extern "C"
JNIEXPORT void JNICALL
cpp_noise_functions_render_frame(JNIEnv *env, jobject thiz) {
    if (noiseFunction == nullptr) {
        LOGE("GLnoiseFunction is nullptr");
        return;
    }
    noiseFunction->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_noise_functions_init(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (noiseFunction == nullptr) {
        LOGE("GLnoiseFunction is nullptr");
        return;
    }
    noiseFunction->setupGraphics(width, height);

}
extern "C"
JNIEXPORT void JNICALL
cpp_noise_functions_set_type(JNIEnv *env, jobject thiz, jint type) {
    if (noiseFunction == nullptr) {
        LOGE("GLnoiseFunction is nullptr");
        return;
    }
    noiseFunction->setParameters(type);

}

extern "C"
JNIEXPORT jint JNICALL
cpp_noise_functions_get_type(JNIEnv *env, jobject thiz) {
    if (noiseFunction == nullptr) {
        LOGE("GLnoiseFunction is nullptr");
        return 0;
    }
    return noiseFunction->getParameters();
}

/*********************  着色器 随机 *****************/
extern "C"
JNIEXPORT void JNICALL
cpp_random_glsl_path(JNIEnv *env, jobject thiz, jstring vertex, jstring frag1,
                     jstring frag2,
                     jstring frag3


) {
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragPath1 = env->GetStringUTFChars(frag1, nullptr);
    const char *fragPath2 = env->GetStringUTFChars(frag2, nullptr);
    const char *fragPath3 = env->GetStringUTFChars(frag3, nullptr);


    if (randomFunction == nullptr) {
        randomFunction = new GLSLRandomFunction();
    }
    string sFragPath1(fragPath1);
    string sFragPath2(fragPath2);
    string sFragPath3(fragPath3);

    vector<string> sFragPathes;
    sFragPathes.push_back(sFragPath1);
    sFragPathes.push_back(sFragPath2);
    sFragPathes.push_back(sFragPath3);

    randomFunction->setSharderStringPathes(vertexPath, sFragPathes);

    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(frag1, fragPath1);
    env->ReleaseStringUTFChars(frag2, fragPath2);
    env->ReleaseStringUTFChars(frag3, fragPath3);

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

        /*********************** GL Shader 生成设计：噪音********************/
        {"native_noise_functions_set_glsl_path",  "(Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"
                                                    "Ljava/lang/String;"

                                                    "Ljava/lang/String;)V", (void *) cpp_noise_functions_glsl_path},
        {"native_noise_functions_init",           "(II)V",                (void *) cpp_noise_functions_init},
        {"native_noise_functions_render_frame",   "()V",                  (void *) cpp_noise_functions_render_frame},
        {"native_noise_functions_set_type",       "(I)V",                 (void *) cpp_noise_functions_set_type},
        {"native_noise_functions_get_type",       "()I",                  (void *) cpp_noise_functions_get_type},
        

        /*********************  着色器 随机 *****************/
        {"native_random_set_glsl_path", "(Ljava/lang/String;"
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