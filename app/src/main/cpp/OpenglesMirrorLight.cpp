//
// Created by MMM on 2024/7/30.
//
#include "OpenglesMirrorLight.h"
#include <iostream>

bool OpenglesMirrorLight::setupGraphics(int w, int h) {
    screenW = w;
    screenH = h;
    LOGI("setupGraphics(%d, %d)", w, h);
    GLuint lightingProgram = lightColorShader->createProgram();
    if (!lightingProgram) {
        LOGE("Could not create shaderId.");
        return false;
    }
    GLuint lightingPositionHandle = glGetAttribLocation(lightingProgram, "gl_Position");
    checkGlError("lightingProgram glGetAttribLocation");

    GLuint lightCubeProgram = lightCubeShader->createProgram();
    if (!lightCubeProgram) {
        LOGE("Could not create shaderId.");
        return false;
    }
    GLuint lightCubePositionHandle = glGetAttribLocation(lightCubeProgram, "gl_Position");
    checkGlError("lightCubeProgram glGetAttribLocation");
    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    LOGI("glViewport successed!");

    //清屏
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    //绑定物体立方体数据
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(OpenglesMirrorLightVertices), OpenglesMirrorLightVertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);

    //绑定灯光立方体数据
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    return true;
}

void OpenglesMirrorLight::renderFrame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    //开启深度测试
    glEnable(GL_DEPTH_TEST);

    // be sure to activate shader when setting uniforms/drawing objects
    lightColorShader->use();
    lightColorShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
    lightColorShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    lightColorShader->setVec3("lightPos", OpenglesMirrorLightLightPos);
    lightColorShader->setVec3("viewPos", mCamera.Position);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom),
                                            (float) screenW / (float) screenH, 0.1f, 100.0f);
    glm::mat4 view = mCamera.GetViewMatrix();
    lightColorShader->setMat4("projection", projection);
    lightColorShader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), OpenglesMirrorLightLightPos);
    lightColorShader->setMat4("model", model);

    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    lightCubeShader->use();
    lightCubeShader->setMat4("projection", projection);
    lightCubeShader->setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, OpenglesMirrorLightLightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lightCubeShader->setMat4("model", model);

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    checkGlError("glDrawArrays");
}

bool OpenglesMirrorLight::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    lightColorShader->getSharderPath(vertexPath, fragmentPath);
    return 0;
}

bool OpenglesMirrorLight::setColorSharderPath(const char *vertexPath, const char *fragmentPath) {
    lightCubeShader->getSharderPath(vertexPath, fragmentPath);
    return false;
}

void OpenglesMirrorLight::setPicPath(const char *pic1, const char *pic2) {
    LOGI("setPicPath pic1==%s", pic1);
    LOGI("setPicPath pic2==%s", pic2);
    // load image, create texture and generate mipmaps
    data1 = stbi_load(pic1, &width1, &height1, &nrChannels1, 0);
    data2 = stbi_load(pic2, &width2, &height2, &nrChannels2, 0);

}

void OpenglesMirrorLight::setMoveXY(float dx, float dy, int actionMode) {
    LOGI("setMoveXY dx:%f,dy:%f,actionMode:%d", dy, dy, actionMode);
    float xoffset = dx - lastX;
    float yoffset = lastY - dy; // reversed since y-coordinates go from bottom to top
    lastX = dx;
    lastY = dy;
    mActionMode = actionMode;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void OpenglesMirrorLight::setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
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


OpenglesMirrorLight::OpenglesMirrorLight() {
    lightColorShader = new OpenGLShader();
    lightCubeShader = new OpenGLShader();
}

OpenglesMirrorLight::~OpenglesMirrorLight() {
    texture1 = 0;
    data1 = nullptr;
    data2 = nullptr;

    //析构函数中释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    lightCubeShader = nullptr;
    lightColorShader = nullptr;

    colorVertexCode.clear();
    colorFragmentCode.clear();
}

void OpenglesMirrorLight::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void OpenglesMirrorLight::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

