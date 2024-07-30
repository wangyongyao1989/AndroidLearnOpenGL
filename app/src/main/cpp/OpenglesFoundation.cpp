//
// Created by MMM on 2024/7/24.
//

#include <malloc.h>
#include "OpenglesFoundation.h"

using namespace std;

void OpenglesFoundation::renderFrame() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //2、使用程序
    glUseProgram(gProgram);
    checkGlError("glUseProgram");
    // seeing as we only have a single VAO there's no need to bind it every time,
    // but we'll do so to keep things a bit more organized
    glBindVertexArray(VAO);
    // 3、绘制物体
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glDrawArrays(GL_TRIANGLES, 0, 6);

    // be sure to activate the shader before any calls to glUniform
    glUseProgram(shaderProgram);
    // update shader uniform
    double timeValue = clock() * 10 / CLOCKS_PER_SEC;
    float greenValue = static_cast<float>(sin(timeValue) / 3.0 + 0.5);
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    checkGlError("glDrawArrays");

}


bool OpenglesFoundation::setupGraphics(int w, int h) {
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    LOGI("gVertexShaderCode :%s", gVertexShaderCode);
    LOGI("gFragmentShaderCode :%s", gFragmentShaderCode);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    LOGI("Maximum nr of vertex attributes supported: :%d", nrAttributes);
//    gProgram = createProgram(gVertexShader, gFragmentShader);
    gProgram = createProgram(gVertexShaderCode, gFragmentShaderCode);
    if (!gProgram) {
        LOGE("Could not create shaderProgram.");
        return false;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
         gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    LOGI("glViewport successed!");

    //清屏
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //绑定VAO
    glBindVertexArray(VAO);
    //把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(gTriangleVertices), gTriangleVertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //绑定EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // 1. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

bool OpenglesFoundation::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    return getSharderPath(vertexPath, fragmentPath);
}

OpenglesFoundation::~OpenglesFoundation() {

}

OpenglesFoundation::OpenglesFoundation() {

}








