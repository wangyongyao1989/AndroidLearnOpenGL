

#include <iostream>
#include "../includes/GLSeniorGeometry.h"

bool GLSeniorGeometry::setupGraphics(int w, int h) {
    screenW = w;
    screenH = h;
    LOGI("setupGraphics(%d, %d)", w, h);
    GLuint redShaderProgram = geometryShader->createVFGProgram();
    if (!redShaderProgram) {
        LOGE("Could not create redShaderProgram shaderId.");
        return false;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GeometryPoint), &GeometryPoint, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glBindVertexArray(0);

    return true;
}

void GLSeniorGeometry::renderFrame() {

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw points
    geometryShader->use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 4);

    checkGlError("glDrawArrays");
}

bool GLSeniorGeometry::setSharderPath(const char *vertexPath, const char *fragRedPath,
                                      const char *geometryPath) {
    geometryShader->getVFGSharderPath(vertexPath, fragRedPath, geometryPath);

    return 0;
}


void GLSeniorGeometry::setMoveXY(float dx, float dy, int actionMode) {
    LOGI("setMoveXY dx:%f,dy:%f,actionMode:%d", dy, dy, actionMode);
    float xoffset = dx - lastX;
    float yoffset = lastY - dy; // reversed since y-coordinates go from bottom to top
    lastX = dx;
    lastY = dy;
    mActionMode = actionMode;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void GLSeniorGeometry::setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
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


GLSeniorGeometry::GLSeniorGeometry() {
    geometryShader = new GLSeniorShader();
}

GLSeniorGeometry::~GLSeniorGeometry() {

    //析构函数中释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    geometryShader = nullptr;

}

void GLSeniorGeometry::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void GLSeniorGeometry::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}



