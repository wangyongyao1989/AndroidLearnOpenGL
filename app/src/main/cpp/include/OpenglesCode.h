//
// Created by MMM on 2024/7/24.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLESCODE_H
#define ANDROIDLEARNOPENGL_OPENGLESCODE_H

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/log.h>


#define LOG_TAG "wy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
static const char gVertexShader[] =
        "attribute vec4 vPosition;\n"
        "void main() {\n"
        "  gl_Position = vPosition;\n"
        "}\n";

static const char gFragmentShader[] =
        "precision mediump float;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n";
static const GLfloat gTriangleVertices[] = {0.0f, 0.5f, -0.5f, -0.5f,
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
