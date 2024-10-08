//
// Created by MMM on 2024/7/30.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLSINGLESHADERBASE_H
#define ANDROIDLEARNOPENGL_OPENGLSINGLESHADERBASE_H

#include <GLES3/gl3.h>              //导入的包为GL3对应的顶点程序和片元程序为：#version 320 es
#include <GLES3/gl3ext.h>
#include <android/log.h>
#include <fstream>
#include <sstream>
#include "iostream"
#include "OpenGLConstants.h"

//glm库
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define LOG_TAG "wy"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

using namespace std;

/**
 * 仅对一对顶点/片段着色器加载使用的基类
 */
class OpenGLSingleShaderBase {
public:
    GLuint shaderProgram;   //着色程序对象


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
    GLuint vertexShader;  //顶点着色器
    GLuint fraShader;     //片段着色器
    GLuint loadShader(GLenum shaderType, const char *pSource);


public:

    OpenGLSingleShaderBase();

    ~OpenGLSingleShaderBase();

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);

    GLuint createProgram(const char *pVertexSource, const char *pFragmentSource);

    bool getSharderPath(const char *vertexPath, const char *fragmentPath);

    virtual bool setSharderPath(const char *vertexPath, const char *fragmentPath) = 0;

    virtual bool setupGraphics(int w, int h) = 0;

    virtual void renderFrame() = 0;

    void setBool(const string &name, bool value) const {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int) value);
    }

    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
    }

    void setVec2(const std::string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    }

    void setVec2(const std::string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), x, y);
    }

    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, float x, float y, float z, float w) const {
        glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

};


#endif //ANDROIDLEARNOPENGL_OPENGLSINGLESHADERBASE_H
