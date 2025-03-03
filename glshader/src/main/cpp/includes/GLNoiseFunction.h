//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/28.
//

#ifndef ANDROIDLEARNOPENGL_GLNOISEFUNCTION_H
#define ANDROIDLEARNOPENGL_GLNOISEFUNCTION_H

#include <vector>
#include "GLSLShader.h"

static float DNVertices[] = {
        0.8f, 0.8f, 0.0f,  // top right
        0.8f, -0.8f, 0.0f,  // bottom right
        -0.8f, -0.8f, 0.0f,  // bottom left
        -0.8f, 0.8f, 0.0f   // top left
};

static unsigned int DNIndices[] = {
        // 注意索引从0开始!
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
};

// Vertices for a full screen quad.
static const float kDNVerticek[8] = {
        -1.f, 1.f,
        -1.f, -1.f,
        1.f, 1.f,
        1.f, -1.f
};


class GLNoiseFunction {

public:
    GLNoiseFunction();

    ~GLNoiseFunction();

    bool setupGraphics(int w, int h);

    void renderFrame();

    bool setSharderPath(const char *vertexPath, const char *fragmentPath);

    bool setSharderStringPath(string vertexPath, string fragmentPath);

    bool setSharderStringPathes(string vertexPath, vector<string> fragmentPathes);

    void setParameters(uint32_t params);

    uint32_t getParameters();

    void setMoveXY(float dx, float dy, int actionMode);

private:

    int createProgram();

    int bindVertexAttribPointer();

    void deleteProgram(GLuint &program);

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);


private:
    int screenW, screenH;
    unsigned int VBO, VAO;
    unsigned int EBO;
    GLSLShader *glslShader = nullptr;
    GLint gvPositionHandle = 0;
    GLuint m_vertexPos = 0;
    GLuint m_resolutionLoc = 0;
    GLuint m_timeLoc = 0;
    GLuint m_moveXYLoc = 0;

    GLuint m_program = 0;

    bool isProgramChanged = true;


    size_t m_filter = 0;
    size_t m_prevFilter = 0;
    string m_vertexStringPath;
    vector<string> m_fragmentStringPathes;

    float lastX, lastY;
    int mActionMode;

};


#endif //ANDROIDLEARNOPENGL_GLNOISEFUNCTION_H
