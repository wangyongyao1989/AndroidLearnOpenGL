//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2024/10/23.
//

#include "GL3DShow.h"

bool GL3DShow::setupGraphics(int w, int h) {
    screenW = w;
    screenH = h;
    GLuint modelProgram = modelShader->createProgram();
    if (!modelProgram) {
        LOGE("Could not create shaderId.");
        return false;
    }



    return false;
}

void GL3DShow::renderFrame() {

}

bool GL3DShow::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    modelShader->getSharderPath(vertexPath, fragmentPath);
    return false;
}


bool GL3DShow::setModelPath(const char *modelPath) {
    LOGI("setMosetModelPath :%s", modelPath);

    return false;
}

void GL3DShow::setMoveXY(float dx, float dy, int actionMode) {
    LOGI("setMoveXY dx:%f,dy:%f,actionMode:%d", dy, dy, actionMode);
    float xoffset = dx - lastX;
    float yoffset = lastY - dy; // reversed since y-coordinates go from bottom to top
    lastX = dx;
    lastY = dy;
    mActionMode = actionMode;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void GL3DShow::setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
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

void GL3DShow::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void GL3DShow::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

GL3DShow::GL3DShow() {
    modelShader = new GL3DShader();

}

GL3DShow::~GL3DShow() {

}


