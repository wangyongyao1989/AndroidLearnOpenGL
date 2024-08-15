#include <jni.h>
#include <string>
#include <android/log.h>
#include "OpenglesFoundation.h"
#include "OpenglesTexture.h"
#include "Opengles3D.h"
#include "OpenglesCube3D.h"
#include "OpenglesMultiCube3D.h"
#include "OpenglesCamera3D.h"
#include "OpenglesLightCube.h"
#include "OpenglesDiffuseReflectionLight.h"
#include "OpenglesMirrorLight.h"
#include "OpenglesMaterial.h"
#include "OpenglesDiffuseMap.h"


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
OpenglesCamera3D *openglCamera3D;
OpenglesLightCube *openglLightCube;
OpenglesDiffuseReflectionLight *diffuseReflectionLight;
OpenglesMirrorLight *mirrorLight;
OpenglesMaterial *material;
OpenglesDiffuseMap *diffuseMap;


extern "C" JNIEXPORT jstring JNICALL
cpp_stringFromJNI(
        JNIEnv *env, jobject) {
    std::string hello = "Hello from C++";
    LOGD("cpp_stringFromJNI  hello = %s", hello.c_str());
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
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
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
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

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
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

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
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

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
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

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

/*********************** GL摄像头 *********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_camera_3d_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (openglCamera3D == nullptr)
        openglCamera3D = new OpenglesCamera3D();
    openglCamera3D->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_camera_3d_render_frame(JNIEnv *env, jobject thiz) {
    if (openglCamera3D == nullptr) return;
    openglCamera3D->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_camera_3d_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                               jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    if (openglCamera3D == nullptr) {
        openglCamera3D = new OpenglesCamera3D();
    }
    openglCamera3D->setSharderPath(vertexPath, fragPath);

    openglCamera3D->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}

extern "C"
JNIEXPORT void JNICALL
cpp_camera_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (openglCamera3D == nullptr) return;
    openglCamera3D->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_camera_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX, jfloat focusY,
                    jint actionMode) {
    if (openglCamera3D == nullptr) return;
    openglCamera3D->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL光照场景 *********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_light_cube_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (openglLightCube == nullptr)
        openglLightCube = new OpenglesLightCube();
    openglLightCube->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_light_cube_render_frame(JNIEnv *env, jobject thiz) {
    if (openglLightCube == nullptr) return;
    openglLightCube->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_light_cube_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                                jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    if (openglLightCube == nullptr) {
        openglLightCube = new OpenglesLightCube();
    }
    openglLightCube->setSharderPath(vertexPath, fragPath);

    openglLightCube->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}

extern "C"
JNIEXPORT void JNICALL
cpp_color_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);

    if (openglLightCube == nullptr) {
        openglLightCube = new OpenglesLightCube();
    }
    openglLightCube->setColorSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}

extern "C"
JNIEXPORT void JNICALL
cpp_light_cube_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (openglLightCube == nullptr) return;
    openglLightCube->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_light_cube_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX, jfloat focusY,
                        jint actionMode) {
    if (openglLightCube == nullptr) return;
    openglLightCube->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL漫反射光照 *********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_diffuse_reflection_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (diffuseReflectionLight == nullptr)
        diffuseReflectionLight = new OpenglesDiffuseReflectionLight();
    diffuseReflectionLight->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_diffuse_reflection_render_frame(JNIEnv *env, jobject thiz) {
    if (diffuseReflectionLight == nullptr) return;
    diffuseReflectionLight->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_diffuse_reflection_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                                        jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    if (diffuseReflectionLight == nullptr) {
        diffuseReflectionLight = new OpenglesDiffuseReflectionLight();
    }
    diffuseReflectionLight->setSharderPath(vertexPath, fragPath);

    diffuseReflectionLight->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}

extern "C"
JNIEXPORT void JNICALL
cpp_diffuse_reflection_color_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag,
                                              jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);

    if (diffuseReflectionLight == nullptr) {
        diffuseReflectionLight = new OpenglesDiffuseReflectionLight();
    }
    diffuseReflectionLight->setColorSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}

extern "C"
JNIEXPORT void JNICALL
cpp_diffuse_reflection_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (diffuseReflectionLight == nullptr) return;
    diffuseReflectionLight->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_diffuse_reflection_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                                jfloat focusY,
                                jint actionMode) {
    if (diffuseReflectionLight == nullptr) return;
    diffuseReflectionLight->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL镜面光照 *********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_mirror_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (mirrorLight == nullptr)
        mirrorLight = new OpenglesMirrorLight();
    mirrorLight->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_mirror_render_frame(JNIEnv *env, jobject thiz) {
    if (mirrorLight == nullptr) return;
    mirrorLight->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_mirror_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                                        jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    if (mirrorLight == nullptr) {
        mirrorLight = new OpenglesMirrorLight();
    }
    mirrorLight->setSharderPath(vertexPath, fragPath);

    mirrorLight->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}

extern "C"
JNIEXPORT void JNICALL
cpp_mirror_color_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag,
                                              jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);

    if (mirrorLight == nullptr) {
        mirrorLight = new OpenglesMirrorLight();
    }
    mirrorLight->setColorSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}

extern "C"
JNIEXPORT void JNICALL
cpp_mirror_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (mirrorLight == nullptr) return;
    mirrorLight->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_mirror_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                                jfloat focusY,
                                jint actionMode) {
    if (mirrorLight == nullptr) return;
    mirrorLight->setOnScale(scaleFactor, focusX, focusY, actionMode);
}

/*********************** GL材质 *********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_material_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (material == nullptr)
        material = new OpenglesMaterial();
    material->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_material_render_frame(JNIEnv *env, jobject thiz) {
    if (material == nullptr) return;
    material->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_material_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                            jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    if (material == nullptr) {
        material = new OpenglesMaterial();
    }
    material->setSharderPath(vertexPath, fragPath);

    material->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}

extern "C"
JNIEXPORT void JNICALL
cpp_material_color_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag,
                                  jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);

    if (material == nullptr) {
        material = new OpenglesMaterial();
    }
    material->setColorSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}

extern "C"
JNIEXPORT void JNICALL
cpp_material_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (material == nullptr) return;
    material->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_material_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                    jfloat focusY,
                    jint actionMode) {
    if (material == nullptr) return;
    material->setOnScale(scaleFactor, focusX, focusY, actionMode);
}


/*********************** GL漫反射贴图 *********************/

extern "C"
JNIEXPORT jboolean JNICALL
cpp_diffuse_map_init_opengl(JNIEnv *env, jobject thiz, jint width, jint height) {
    if (diffuseMap == nullptr)
        diffuseMap = new OpenglesDiffuseMap();
    diffuseMap->setupGraphics(width, height);
    return 0;
}

extern "C"
JNIEXPORT void JNICALL
cpp_diffuse_map_render_frame(JNIEnv *env, jobject thiz) {
    if (diffuseMap == nullptr) return;
    diffuseMap->renderFrame();

}

extern "C"
JNIEXPORT void JNICALL
cpp_diffuse_map_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag, jstring vertex,
                              jstring picsrc1, jstring picsrc2) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);
    const char *picsrc1Path = env->GetStringUTFChars(picsrc1, nullptr);
    const char *picsrc2Path = env->GetStringUTFChars(picsrc2, nullptr);

    if (diffuseMap == nullptr) {
        diffuseMap = new OpenglesDiffuseMap();
    }
    diffuseMap->setSharderPath(vertexPath, fragPath);

    diffuseMap->setPicPath(picsrc1Path, picsrc2Path);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);
    env->ReleaseStringUTFChars(picsrc1, picsrc1Path);
    env->ReleaseStringUTFChars(picsrc2, picsrc2Path);

}

extern "C"
JNIEXPORT void JNICALL
cpp_diffuse_map_color_frag_vertex_path(JNIEnv *env, jobject thiz, jstring frag,
                                    jstring vertex) {
    const char *fragPath = env->GetStringUTFChars(frag, nullptr);
    const char *vertexPath = env->GetStringUTFChars(vertex, nullptr);

    if (diffuseMap == nullptr) {
        diffuseMap = new OpenglesDiffuseMap();
    }
    diffuseMap->setColorSharderPath(vertexPath, fragPath);

    env->ReleaseStringUTFChars(frag, fragPath);
    env->ReleaseStringUTFChars(vertex, vertexPath);

}

extern "C"
JNIEXPORT void JNICALL
cpp_diffuse_map_move_xy(JNIEnv *env, jobject thiz, jfloat dx, jfloat dy, jint actionMode) {
    if (diffuseMap == nullptr) return;
    diffuseMap->setMoveXY(dx, dy, actionMode);
}

extern "C"
JNIEXPORT void JNICALL
cpp_diffuse_map_on_scale(JNIEnv *env, jobject thiz, jfloat scaleFactor, jfloat focusX,
                      jfloat focusY,
                      jint actionMode) {
    if (diffuseMap == nullptr) return;
    diffuseMap->setOnScale(scaleFactor, focusX, focusY, actionMode);
}


// 重点：定义类名和函数签名，如果有多个方法要动态注册，在数组里面定义即可
static const JNINativeMethod methods[] = {
        {"stringFromJNI",                                 "()Ljava/lang/String;",  (std::string *) cpp_stringFromJNI},
        {"native_callback",                               "()V",                   (void *) cpp_init_callback},
        //Foundation
        {"native_foundation_init_opengl",                 "(II)Z",                 (void *) cpp_foundation_init_opengl},
        {"native_foundation_render_frame",                "()V",                   (void *) cpp_foundation_render_frame},
        {"native_foundation_set_glsl_path",               "(Ljava/lang/String;"
                                                          "Ljava/lang/String;)V",  (void *) cpp_foundation_frag_vertex_path},
        //Texture
        {"native_texture_init_opengl",                    "(II)Z",                 (void *) cpp_texture_init_opengl},
        {"native_texture_render_frame",                   "()V",                   (void *) cpp_texture_render_frame},

        {"native_texture_set_glsl_path",                  "(Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_texture_frag_vertex_path},
        //3D基础
        {"native_3d_init_opengl",                         "(II)Z",                 (void *) cpp_3d_init_opengl},
        {"native_3d_render_frame",                        "()V",                   (void *) cpp_3d_render_frame},

        {"native_3d_set_glsl_path",                       "(Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_3d_frag_vertex_path},
        //立方体3D
        {"native_cube_3d_init_opengl",                    "(II)Z",                 (void *) cpp_cube_3d_init_opengl},
        {"native_cube_3d_render_frame",                   "()V",                   (void *) cpp_cube_3d_render_frame},

        {"native_cube_3d_set_glsl_path",                  "(Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_cube_3d_frag_vertex_path},
        //多立方体3D
        {"native_multi_cube_3d_init_opengl",              "(II)Z",                 (void *) cpp_multi_cube_3d_init_opengl},
        {"native_multi_cube_3d_render_frame",             "()V",                   (void *) cpp_multi_cube_3d_render_frame},

        {"native_multi_cube_3d_set_glsl_path",            "(Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_multi_cube_3d_frag_vertex_path},

        //摄像头
        {"native_camera_3d_init_opengl",                  "(II)Z",                 (void *) cpp_camera_3d_init_opengl},
        {"native_camera_3d_render_frame",                 "()V",                   (void *) cpp_camera_3d_render_frame},

        {"native_camera_3d_set_glsl_path",                "(Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_camera_3d_frag_vertex_path},
        {"native_camera_move_xy",                         "(FFI)V",                (void *) cpp_camera_move_xy},
        {"native_camera_on_scale",                        "(FFFI)V",               (void *) cpp_camera_on_scale},

        //光照场景
        {"native_light_cube_init_opengl",                 "(II)Z",                 (void *) cpp_light_cube_init_opengl},
        {"native_light_cube_render_frame",                "()V",                   (void *) cpp_light_cube_render_frame},
        {"native_color_set_glsl_path",                    "(Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_color_frag_vertex_path},
        {"native_light_cube_set_glsl_path",               "(Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_light_cube_frag_vertex_path},
        {"native_light_cube_move_xy",                     "(FFI)V",                (void *) cpp_light_cube_move_xy},
        {"native_light_cube_on_scale",                    "(FFFI)V",               (void *) cpp_light_cube_on_scale},

        //漫反射光照
        {"native_diffuse_reflection_init_opengl",         "(II)Z",                 (void *) cpp_diffuse_reflection_init_opengl},
        {"native_diffuse_reflection_render_frame",        "()V",                   (void *) cpp_diffuse_reflection_render_frame},
        {"native_diffuse_reflection_color_set_glsl_path", "(Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_diffuse_reflection_color_frag_vertex_path},
        {"native_diffuse_reflection_set_glsl_path",       "(Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_diffuse_reflection_frag_vertex_path},
        {"native_diffuse_reflection_move_xy",             "(FFI)V",                (void *) cpp_diffuse_reflection_move_xy},
        {"native_diffuse_reflection_on_scale",            "(FFFI)V",               (void *) cpp_diffuse_reflection_on_scale},

        //镜面光照
        {"native_mirror_init_opengl",                     "(II)Z",                 (void *) cpp_mirror_init_opengl},
        {"native_mirror_render_frame",                    "()V",                   (void *) cpp_mirror_render_frame},
        {"native_mirror_color_set_glsl_path",             "(Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_mirror_color_frag_vertex_path},
        {"native_mirror_set_glsl_path",                   "(Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_mirror_frag_vertex_path},
        {"native_mirror_move_xy",                         "(FFI)V",                (void *) cpp_mirror_move_xy},
        {"native_mirror_on_scale",                        "(FFFI)V",               (void *) cpp_mirror_on_scale},

        //材质
        {"native_material_init_opengl",                     "(II)Z",                 (void *) cpp_material_init_opengl},
        {"native_material_render_frame",                    "()V",                   (void *) cpp_material_render_frame},
        {"native_material_color_set_glsl_path",             "(Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_material_color_frag_vertex_path},
        {"native_material_set_glsl_path",                   "(Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String"
                                                          ";Ljava/lang/String;)V", (void *) cpp_material_frag_vertex_path},
        {"native_material_move_xy",                         "(FFI)V",                (void *) cpp_material_move_xy},
        {"native_material_on_scale",                        "(FFFI)V",               (void *) cpp_material_on_scale},

        //漫反射贴图
        {"native_diffuse_map_init_opengl",                     "(II)Z",                 (void *) cpp_diffuse_map_init_opengl},
        {"native_diffuse_map_render_frame",                    "()V",                   (void *) cpp_diffuse_map_render_frame},
        {"native_diffuse_map_color_set_glsl_path",             "(Ljava/lang/String"
                                                            ";Ljava/lang/String;)V", (void *) cpp_diffuse_map_color_frag_vertex_path},
        {"native_diffuse_map_set_glsl_path",                   "(Ljava/lang/String"
                                                            ";Ljava/lang/String"
                                                            ";Ljava/lang/String"
                                                            ";Ljava/lang/String;)V", (void *) cpp_diffuse_map_frag_vertex_path},
        {"native_diffuse_map_move_xy",                         "(FFI)V",                (void *) cpp_diffuse_map_move_xy},
        {"native_diffuse_map_on_scale",                        "(FFFI)V",               (void *) cpp_diffuse_map_on_scale},

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
