//
// Created by MMM on 2024/7/30.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLBASE_H
#define ANDROIDLEARNOPENGL_OPENGLBASE_H

#include <GLES3/gl3.h>              //导入的包为GL3对应的顶点程序和片元程序为：#version 320 es
#include <GLES3/gl3ext.h>
#include <android/log.h>
#include <fstream>
#include <sstream>
#include "iostream"
#include "OpenGLConstants.h"


#define LOG_TAG "wy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

using namespace std;

class OpenGLBase {
public:
    GLuint shaderProgram;   //着色程序对象
    GLuint vertexShader;  //顶点着色器
    GLuint fraShader;     //片段着色器

    unsigned int VBO, VAO;
    unsigned int EBO;

    GLuint gProgram;
    GLuint gvPositionHandle;
    //顶点着色器代码
    const char *gVertexShaderCode;
    //片段着色器代码
    const char *gFragmentShaderCode;

    string vertexCode;
    string fragmentCode;

private:

    GLuint loadShader(GLenum shaderType, const char *pSource);


public:

    OpenGLBase();

    ~OpenGLBase();

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);

    GLuint createProgram(const char *pVertexSource, const char *pFragmentSource);

    bool getSharderPath(const char *vertexPath, const char *fragmentPath);

    virtual bool setSharderPath(const char *vertexPath, const char *fragmentPath) = 0;

    virtual bool setupGraphics(int w, int h) = 0;

    virtual void renderFrame() = 0;

    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

};


#endif //ANDROIDLEARNOPENGL_OPENGLBASE_H
