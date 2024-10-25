#include <jni.h>
#include <string>
#include <android/log.h>

#define LOG_TAG "wy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

//包名+类名字符串定义：
const char *gl3d_class_name = "com/wangyongyao/gl3d/GL3DCallJni";

extern "C"
JNIEXPORT jboolean JNICALL
cpp_3dshow_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {

    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_3dshow_render_frame(JNIEnv *env, jobject thiz) {


}

extern "C"
JNIEXPORT void JNICALL
cpp_3dshow_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);


    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}


// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod methods[] = {
        {"native_3d_init_opengl",   "(II)Z", (void *) cpp_3dshow_init_opengl},
        {"native_3d_render_frame",  "()V",   (void *) cpp_3dshow_render_frame},
        {"native_3d_set_glsl_path", "(Ljava/lang/String;"
                                    "Ljava/lang/String;)V",
                                             (void *) cpp_3dshow_frag_vertex_path},

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

