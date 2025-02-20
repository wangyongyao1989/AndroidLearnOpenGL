//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/20.
//

#ifndef ANDROIDLEARNOPENGL_GLSHAPINGFUNCTION_H
#define ANDROIDLEARNOPENGL_GLSHAPINGFUNCTION_H
#include "GLSLShader.h"

static float SFVertices[] = {
        0.8f, 0.8f, 0.0f,  // top right
        0.8f, -0.8f, 0.0f,  // bottom right
        -0.8f, -0.8f, 0.0f,  // bottom left
        -0.8f, 0.8f, 0.0f   // top left
};

static unsigned int SFIndices[] = {
        // 注意索引从0开始!
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
};

class GLShapingFunction {

public:
    GLShapingFunction();

    ~GLShapingFunction();

    bool setupGraphics(int w, int h);

    void renderFrame();

    bool setSharderPath(const char *vertexPath, const char *fragmentPath);

private:

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);


private:
    int screenW, screenH;
    unsigned int VBO, VAO;
    unsigned int EBO;
    GLSLShader *glslShader = nullptr;

    GLint gvPositionHandle;
};


#endif //ANDROIDLEARNOPENGL_GLSHAPINGFUNCTION_H
