//
// Created by MMM on 2024/7/30.
//
#include "OpenglesLightCube.h"
#include <iostream>

bool OpenglesLightCube::setupGraphics(int w, int h) {
    screenW = w;
    screenH = h;
    LOGI("setupGraphics(%d, %d)", w, h);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    LOGI("glViewport successed!");

    //清屏
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lightCubeVertices11), lightCubeVertices11, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    return true;
}

void OpenglesLightCube::renderFrame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

    // be sure to activate shader when setting uniforms/drawing objects
    glUseProgram(lightingShader);
    setVec3(lightingShader, "objectColor", 1.0f, 0.5f, 0.31f);
    setVec3(lightingShader, "lightColor", 1.0f, 1.0f, 1.0f);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom),
                                            (float) screenW / (float) screenH, 0.1f, 100.0f);
    glm::mat4 view = mCamera.GetViewMatrix();
    setMat4(lightingShader, "projection", projection);
    setMat4(lightingShader, "view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    setMat4(lightingShader,"model", model);

    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    glUseProgram(lightCubeShader);
    setMat4(lightCubeShader, "projection", projection);
    setMat4(lightCubeShader, "view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    setMat4(lightCubeShader, "model", model);

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    checkGlError("glDrawArrays");
}

bool OpenglesLightCube::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    bool b = getSharderPath(vertexPath, fragmentPath);
    lightingShader = createSharderProgram();
    return b;
}

bool OpenglesLightCube::setColorSharderPath(const char *vertexPath, const char *fragmentPath) {
    bool b = getSharderPath(vertexPath, fragmentPath);
    lightCubeShader = createSharderProgram();
    return b;
}

void OpenglesLightCube::setPicPath(const char *pic1, const char *pic2) {
    LOGI("setPicPath pic1==%s", pic1);
    LOGI("setPicPath pic2==%s", pic2);
    // load image, create texture and generate mipmaps
    data1 = stbi_load(pic1, &width1, &height1, &nrChannels1, 0);
    data2 = stbi_load(pic2, &width2, &height2, &nrChannels2, 0);

}

void OpenglesLightCube::setMoveXY(float dx, float dy, int actionMode) {
    LOGI("setMoveXY dx:%f,dy:%f,actionMode:%d", dy, dy, actionMode);
    float xoffset = dx - lastX;
    float yoffset = lastY - dy; // reversed since y-coordinates go from bottom to top
    lastX = dx;
    lastY = dy;
    mActionMode = actionMode;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void OpenglesLightCube::setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
//    LOGI("setOnScale scaleFactor:%f,focusX:%f,focusY:%f,actionMode:%d", scaleFactor, focusX, focusY,
//         actionMode);
//    LOGI("setOnScale scaleFactor:%f", scaleFactor);
    float scale;
    if (actionMode == 1 || actionMode == 3) {
        scale = 45.0f;
    } else {
        if (scaleFactor > 1) {
            scale = (scaleFactor - 1) * 1000 + 45;
        } else {
            scale = 50 - (1 - scaleFactor) * 1000;
        }
    }
    LOGI("setOnScale scale:%f", scale);
    mCamera.ProcessScroll(scale);
}


OpenglesLightCube::OpenglesLightCube() {

}

OpenglesLightCube::~OpenglesLightCube() {
    texture1 = 0;
    data1 = nullptr;
    data2 = nullptr;

    //析构函数中释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(lightingShader);
    glDeleteProgram(lightCubeShader);


    colorVertexCode.clear();
    colorFragmentCode.clear();
}


