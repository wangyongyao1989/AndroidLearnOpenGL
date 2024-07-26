//
// Created by MMM on 2024/7/24.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLESCODE_H
#define ANDROIDLEARNOPENGL_OPENGLESCODE_H

#include <GLES3/gl3.h>              //导入的包为GL3对应的顶点程序和片元程序为：#version 300 es
#include <GLES3/gl3ext.h>
#include <android/log.h>


#define LOG_TAG "wy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
static const char gVertexShader[] =
        "#version 320 es\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

static const char gFragmentShader[] =
        "#version 320 es\n"
        "precision mediump float;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

static const GLfloat gTriangleVertices[] = {
                                            0.0f, 0.5f,
                                            -0.5f, -0.5f,
                                            0.5f, -0.5f};


class OpenglesCode {

private:

    GLuint gProgram;
    GLuint gvPositionHandle;

    void printGLString(const char *name, GLenum s);

    GLuint loadShader(GLenum shaderType, const char *pSource);

    void checkGlError(const char *op);

    GLuint createProgram(const char *pVertexSource, const char *pFragmentSource);

public:

    bool setupGraphics(int w, int h);

    void renderFrame();
};


#endif //ANDROIDLEARNOPENGL_OPENGLESCODE_H
