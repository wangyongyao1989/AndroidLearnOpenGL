#include <jni.h>
#include <string>
#include <android/log.h>
#include "GLSLLogUtils.h"
#include "GLShapingFunction.h"
#include "GLColorFunction.h"

//包名+类名字符串定义：
const char *gl3d_class_name = "com/wangyongyao/glsl/GLSLCallJni";


GLShapingFunction *shapingFunction;
GLColorFunction *colorFunction;

/*********************** GL Shader 造型函数（Shaping Function）********************/
extern "C"
JNIEXPORT void JNICALL
cpp_color_functions_glsl_path(JNIEnv *env, jobject thiz, jstring vertex, jstring frag1,
                                jstring frag2,
                                jstring frag3,
                                jstring frag4,
                                jstring frag5


) {
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *fragPath1 = env->GetStringUTFChars(frag1, nullptr);
    const char *fragPath2 = env->GetStringUTFChars(frag2, nullptr);
    const char *fragPath3 = env->GetStringUTFChars(frag3, nullptr);
    const char *fragPath4 = env->GetStringUTFChars(frag4, nullptr);
    const char *fragPath5 = env->GetStringUTFChars(frag5, nullptr);


    if (colorFunction == nullptr) {
        colorFunction = new GLColorFunction();
    }
    string sFragPath1(fragPath1);
    string sFragPath2(fragPath2);
    string sFragPath3(fragPath3);
    string sFragPath4(fragPath4);
    string sFragPath5(fragPath5);

    vector<string> sFragPathes;
    sFragPathes.push_back(sFragPath1);
    sFragPathes.push_back(sFragPath2);
    sFragPathes.push_back(sFragPath3);
    sFragPathes.push_back(sFragPath4);
    sFragPathes.push_back(sFragPath5);


    colorFunction->setSharderStringPathes(vertexPath, sFragPathes);

    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(frag1, fragPath1);
    env->ReleaseStringUTFChars(frag2, fragPath2);
    env->ReleaseStringUTFChars(frag3, fragPath3);
    env->ReleaseStringUTFChars(frag4, fragPath4);
    env->ReleaseStringUTFChars(frag5, fragPath5);

}

extern "C"
JNIEXPORT void JNICALL
cpp_color_functions_render_frame(JNIEnv *env, jobject thiz) {
    if (colorFunction == nullptr) {
        LOGE("GLcolorFunction is nullptr");
        return;
    }
    colorFunction->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_color_functions_init(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (colorFunction == nullptr) {
        LOGE("GLcolorFunction is nullptr");
        return;
    }
    colorFunction->setupGraphics(width, height);

}
extern "C"
JNIEXPORT void JNICALL
cpp_color_functions_set_type(JNIEnv *env, jobject thiz, jint type) {
    if (colorFunction == nullptr) {
        LOGE("GLcolorFunction is nullptr");
        return;
    }
    colorFunction->setParameters(type);

}

extern "C"
JNIEXPORT jint JNICALL
cpp_color_functions_get_type(JNIEnv *env, jobject thiz) {
    if (colorFunction == nullptr) {
        LOGE("GLcolorFunction is nullptr");
        return 0;
    }
    return colorFunction->getParameters();
}



/*********************** GL Shader 造型函数（Shaping Function）********************/
extern "C"
JNIEXPORT void JNICALL
cpp_shaping_functions_glsl_path(JNIEnv *env, jobject thiz, jstring vertex, jstring frag1,
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


    if (shapingFunction == nullptr) {
        shapingFunction = new GLShapingFunction();
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


    shapingFunction->setSharderStringPathes(vertexPath, sFragPathes);

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
cpp_shaping_functions_render_frame(JNIEnv *env, jobject thiz) {
    if (shapingFunction == nullptr) {
        LOGE("GLShapingFunction is nullptr");
        return;
    }
    shapingFunction->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_shaping_functions_init(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (shapingFunction == nullptr) {
        LOGE("GLShapingFunction is nullptr");
        return;
    }
    shapingFunction->setupGraphics(width, height);

}
extern "C"
JNIEXPORT void JNICALL
cpp_shaping_functions_set_type(JNIEnv *env, jobject thiz, jint type) {
    if (shapingFunction == nullptr) {
        LOGE("GLShapingFunction is nullptr");
        return;
    }
    shapingFunction->setParameters(type);

}

extern "C"
JNIEXPORT jint JNICALL
cpp_shaping_functions_get_type(JNIEnv *env, jobject thiz) {
    if (shapingFunction == nullptr) {
        LOGE("GLShapingFunction is nullptr");
        return 0;
    }
    return shapingFunction->getParameters();
}

// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod methods[] = {

        /*********************** GL Shader 造型函数（Shaping Function）********************/
        {"native_color_functions_set_glsl_path", "(Ljava/lang/String;"
                                                   "Ljava/lang/String;"
                                                   "Ljava/lang/String;"
                                                   "Ljava/lang/String;"
                                                   "Ljava/lang/String;"
                                                   "Ljava/lang/String;)V", (void *) cpp_color_functions_glsl_path},
        {"native_color_functions_init",          "(II)V",                (void *) cpp_color_functions_init},
        {"native_color_functions_render_frame",  "()V",                  (void *) cpp_color_functions_render_frame},
        {"native_color_functions_set_type",      "(I)V",                 (void *) cpp_color_functions_set_type},
        {"native_color_functions_get_type",      "()I",                  (void *) cpp_color_functions_get_type},


        /*********************** GL Shader 造型函数（Shaping Function）********************/
        {"native_shaping_functions_set_glsl_path", "(Ljava/lang/String;"
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

                                                   "Ljava/lang/String;)V", (void *) cpp_shaping_functions_glsl_path},
        {"native_shaping_functions_init",          "(II)V",                (void *) cpp_shaping_functions_init},
        {"native_shaping_functions_render_frame",  "()V",                  (void *) cpp_shaping_functions_render_frame},
        {"native_shaping_functions_set_type",      "(I)V",                 (void *) cpp_shaping_functions_set_type},
        {"native_shaping_functions_get_type",      "()I",                  (void *) cpp_shaping_functions_get_type},

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

