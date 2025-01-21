//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2024/10/23.
//

#include "../includes/GLSenior3DShow.h"


bool GLSenior3DShow::setupGraphics(int w, int h) {
    screenW = w;
    screenH = h;
    GLuint modelProgram = modelShader->createProgram();
    if (!modelProgram) {
        LOGE("Could not create shaderId.");
        return false;
    }
    LOGE("modelProgram========.");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    modelMatrices = new glm::mat4[amount];
    double timeValue = clock() * 10 / CLOCKS_PER_SEC;
    srand(static_cast<unsigned int>(timeValue)); // initialize random seed
    float radius = 30.0;
    float offset = 2.5f;
    for (unsigned int i = 0; i < amount; i++) {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float) i / (float) amount * 360.0f;
        float displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        float y = displacement *
                  0.4f; // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int) (2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    return false;
}

void GLSenior3DShow::renderFrame() {

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // configure transformation matrices
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                            (float) screenW / (float) screenH,
                                            0.1f, 1000.0f);
    glm::mat4 view = mCamera.GetViewMatrix();;
    modelShader->use();
    modelShader->setMat4("projection", projection);
    modelShader->setMat4("view", view);

    // draw planet
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.5f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    modelShader->setMat4("model", model);
    planet3DModel->Draw(*modelShader);

    // draw meteorites
    for (unsigned int i = 0; i < amount; i++) {
        modelShader->setMat4("model", modelMatrices[i]);
        rock3DModel->Draw(*modelShader);
    }
}

bool GLSenior3DShow::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    modelShader->getSharderPath(vertexPath, fragmentPath);
    return false;
}


bool GLSenior3DShow::setModelPath(const char *modelPath1, const char *modelPath2) {
    LOGI("setMosetModelPath :%s", modelPath1);
    LOGI("setMosetModelPath :%s", modelPath2);

    string rockModel(modelPath1);
    string planetModel(modelPath1);

    rock3DModel = new GLSenior3DModel(rockModel, false);
    planet3DModel = new GLSenior3DModel(planetModel, false);
    return false;
}

void GLSenior3DShow::setMoveXY(float dx, float dy, int actionMode) {
    LOGI("setMoveXY dx:%f,dy:%f,actionMode:%d", dy, dy, actionMode);
    float xoffset = dx - lastX;
    float yoffset = lastY - dy; // reversed since y-coordinates go from bottom to top
    lastX = dx;
    lastY = dy;
    mActionMode = actionMode;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void GLSenior3DShow::setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
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

void GLSenior3DShow::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void GLSenior3DShow::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

GLSenior3DShow::GLSenior3DShow() {
    modelShader = new GLSeniorShader();

}

GLSenior3DShow::~GLSenior3DShow() {
    if (modelShader) {
        delete modelShader;
        modelShader = nullptr;
    }

    if (rock3DModel) {
        delete rock3DModel;
        rock3DModel = nullptr;
    }

    if (planet3DModel) {
        delete planet3DModel;
        planet3DModel = nullptr;
    }

    if (modelMatrices) {
        delete modelMatrices;
        modelMatrices = nullptr;
    }

    lastX = 0;
    lastY = 0;
    mActionMode = 0;
    screenW = 0;
    screenH = 0;


}


