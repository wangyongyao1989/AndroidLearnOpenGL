#include <jni.h>
#include <string>
#include <android/log.h>
#include "GLSLLogUtils.h"


// 声明各个类的注册函数
void registerClassAlgoritmDrawing(JNIEnv *env);

void registerClassDesignGeneration(JNIEnv *env);

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

    registerClassAlgoritmDrawing(env);
    registerClassDesignGeneration(env);

    return JNI_VERSION_1_6;
}

