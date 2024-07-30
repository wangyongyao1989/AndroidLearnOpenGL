//
// Created by MMM on 2024/7/24.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#define ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H

#include <GLES3/gl3.h>              //导入的包为GL3对应的顶点程序和片元程序为：#version 320 es
#include <GLES3/gl3ext.h>
#include <android/log.h>
#include <fstream>
#include <sstream>
#include "iostream"


#define LOG_TAG "wy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

using namespace std;

class OpenglesFoundation {

private:

    GLuint gProgram;
    GLuint gvPositionHandle;
    GLuint shaderProgram;   //着色程序对象

    GLuint vertexShader;  //顶点着色器
    GLuint fraShader;     //片段着色器


    //顶点着色器代码
    const char *gVertexShaderCode;
    //片段着色器代码
    const char *gFragmentShaderCode;

    string vertexCode;
    string fragmentCode;

    unsigned int VBO, VAO;
    unsigned int EBO;

    void printGLString(const char *name, GLenum s);

    GLuint loadShader(GLenum shaderType, const char *pSource);

    void checkGlError(const char *op);

    GLuint createProgram(const char *pVertexSource, const char *pFragmentSource);

    ~OpenglesFoundation();

public:


    bool getSharderPath(const char *vertexPath, const char *fragmentPath);

    bool setupGraphics(int w, int h);

    void renderFrame();
};


#endif //ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
