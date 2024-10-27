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
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

    //开启深度测试
    glEnable(GL_DEPTH_TEST);
    // be sure to activate shader when setting uniforms/drawing objects
    modelShader->use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom),
                                            (float) screenW / (float) screenH, 0.1f, 100.0f);

    vec3 cameraMove(0.0f, 0.0f, 6.0f);
    mCamera.Position = cameraMove;
    glm::mat4 view = mCamera.GetViewMatrix();
    modelShader->setMat4("projection", projection);
    modelShader->setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(0.4f);
    // translate it down so it's at the center of the scene
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    // it's a bit too big for our scene, so scale it down
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    modelShader->setMat4("model", model);
    gl3DModel->Draw(*modelShader);
}

bool GL3DShow::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    modelShader->getSharderPath(vertexPath, fragmentPath);
    return false;
}


bool GL3DShow::setModelPath(const char *modelPath) {
    LOGI("setMosetModelPath :%s", modelPath);
    string model(modelPath);
    gl3DModel = new GL3DModel(model, false);
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
    if (modelShader) {
        delete modelShader;
        modelShader = nullptr;
    }

    if (gl3DModel) {
        delete gl3DModel;
        gl3DModel = nullptr;
    }

    lastX = 0;
    lastY = 0;
    mActionMode = 0;
    screenW = 0;
    screenH = 0;


}


