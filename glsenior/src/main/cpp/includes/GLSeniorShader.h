//
// Created by MMM on 2024/8/8.
//

#ifndef ANDROIDLEARNOPENGL_GLSeniorShader_H
#define ANDROIDLEARNOPENGL_GLSeniorShader_H

#include <GLES3/gl3.h>              //导入的包为GL3对应的顶点程序和片元程序为：#version 320 es
#include <GLES3/gl3ext.h>
#include <android/log.h>
#include <fstream>
#include <sstream>
#include "iostream"
#include "GLSeniorLogUtils.h"
//glm库
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


using namespace std;


class GLSeniorShader {

public:
    void setGVertexShaderCode(const char *gVertexShaderCode);

    void setGFragmentShaderCode(const char *gFragmentShaderCode);

    void setGGeometryShaderCode(const char *gFragmentShaderCode);

private:
    //顶点着色器代码
    const char *gVertexShaderCode = nullptr;
    //片段着色器代码
    const char *gFragmentShaderCode = nullptr;
    //几何着色器代码
    const char *gGeometryShaderCode = nullptr;

    string vertexCode;
    string fragmentCode;
    string geometryCode;    //几何着色器


    GLuint loadShader(GLenum shaderType, const char *pSource);


    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);

public:
    GLuint shaderId;
    GLuint vertexShader;  //顶点着色器
    GLuint fraShader;     //片段着色器
    GLuint geometryShader;     //几何着色器

    GLSeniorShader();

    ~GLSeniorShader();

    bool getSharderPath(const char *vertexPath, const char *fragmentPath);

    bool getVFGSharderPath(const char *vertexPath, const char *fragmentPath
                            , const char *geometryPath);

    bool getSharderStringPath(string vertexPath, string fragmentPath);

    GLuint createProgram();

    GLuint createVFGProgram();

    void use() const {
        glUseProgram(shaderId);
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const string &name, bool value) const {
        glUniform1i(glGetUniformLocation(shaderId, name.c_str()), (int) value);
    }

    // ------------------------------------------------------------------------
    void setInt(const string &name, int value) const {
        glUniform1i(glGetUniformLocation(shaderId, name.c_str()), value);
    }

    // ------------------------------------------------------------------------
    void setFloat(const string &name, float value) const {
        glUniform1f(glGetUniformLocation(shaderId, name.c_str()), value);
    }

    // ------------------------------------------------------------------------
    void setVec2(const string &name, const glm::vec2 &value) const {
        glUniform2fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
    }

    void setVec2(const string &name, float x, float y) const {
        glUniform2f(glGetUniformLocation(shaderId, name.c_str()), x, y);
    }

    // ------------------------------------------------------------------------
    void setVec3(const string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
    }

    void setVec3(const string &name, float x, float y, float z) const {
        glUniform3f(glGetUniformLocation(shaderId, name.c_str()), x, y, z);
    }

    // ------------------------------------------------------------------------
    void setVec4(const string &name, const glm::vec4 &value) const {
        glUniform4fv(glGetUniformLocation(shaderId, name.c_str()), 1, &value[0]);
    }

    void setVec4(const string &name, float x, float y, float z, float w) const {
        glUniform4f(glGetUniformLocation(shaderId, name.c_str()), x, y, z, w);
    }

    // ------------------------------------------------------------------------
    void setMat2(const string &name, const glm::mat2 &mat) const {
        glUniformMatrix2fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void setMat3(const string &name, const glm::mat3 &mat) const {
        glUniformMatrix3fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    // ------------------------------------------------------------------------
    void setMat4(const string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(shaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

};


#endif //ANDROIDLEARNOPENGL_GLSeniorShader_H
