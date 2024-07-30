//
// Created by MMM on 2024/7/24.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#define ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H

#include "OpenGLBase.h"


using namespace std;

class OpenglesFoundation : public OpenGLBase {

private:

//    GLuint gProgram;
//    GLuint gvPositionHandle;
//    GLuint shaderProgram;   //着色程序对象
//
//    GLuint vertexShader;  //顶点着色器
//    GLuint fraShader;     //片段着色器
//
//
//    //顶点着色器代码
//    const char *gVertexShaderCode;
//    //片段着色器代码
//    const char *gFragmentShaderCode;
//
//    string vertexCode;
//    string fragmentCode;
//
//    unsigned int VBO, VAO;
//    unsigned int EBO;
//
//    void printGLString(const char *name, GLenum s);
//
//    GLuint loadShader(GLenum shaderType, const char *pSource);
//
//    void checkGlError(const char *op);
//
//    GLuint createProgram(const char *pVertexSource, const char *pFragmentSource);
//
//    ~OpenglesFoundation();

public:

    OpenglesFoundation();

    ~OpenglesFoundation();

    bool setupGraphics(int w, int h) override;

    void renderFrame() override;

    bool setSharderPath(const char *vertexPath, const char *fragmentPath) override;

};


#endif //ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
