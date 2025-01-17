

#include <iostream>
#include "../includes/GLSeniorUniform.h"

bool GLSeniorUniform::setupGraphics(int w, int h) {
    screenW = w;
    screenH = h;
    LOGI("setupGraphics(%d, %d)", w, h);
    GLuint redShaderProgram = redShader->createProgram();
    if (!redShaderProgram) {
        LOGE("Could not create redShaderProgram shaderId.");
        return false;
    }

    GLuint blueShaderProgram = blueShader->createProgram();
    if (!blueShaderProgram) {
        LOGE("Could not create blueShaderProgram shaderId.");
        return false;
    }

    GLuint greenShaderProgram = greenShader->createProgram();
    if (!greenShaderProgram) {
        LOGE("Could not create greenShaderProgram shaderId.");
        return false;
    }

    GLuint yellowShaderProgram = yellowShader->createProgram();
    if (!yellowShaderProgram) {
        LOGE("Could not create yellowShaderProgram shaderId.");
        return false;
    }

    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UniformVertices), &UniformVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // configure a uniform buffer object
    // ---------------------------------
    // first. We get the relevant block indices
    unsigned int uniformBlockIndexRed = glGetUniformBlockIndex(redShader->shaderId, "Matrices");
    unsigned int uniformBlockIndexGreen = glGetUniformBlockIndex(greenShader->shaderId, "Matrices");
    unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(blueShader->shaderId, "Matrices");
    unsigned int uniformBlockIndexYellow = glGetUniformBlockIndex(yellowShader->shaderId, "Matrices");
    // then we link each shader's uniform block to this uniform binding point
    glUniformBlockBinding(redShader->shaderId, uniformBlockIndexRed, 0);
    glUniformBlockBinding(greenShader->shaderId, uniformBlockIndexGreen, 0);
    glUniformBlockBinding(blueShader->shaderId, uniformBlockIndexBlue, 0);
    glUniformBlockBinding(yellowShader->shaderId, uniformBlockIndexYellow, 0);

    // Now actually create the buffer
    glGenBuffers(1, &uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, uboMatrices, 0, 2 * sizeof(glm::mat4));

    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
    glm::mat4 projection = glm::perspective(45.0f, (float)screenW / (float)screenH, 0.1f, 100.0f);
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);



    return true;
}

void GLSeniorUniform::renderFrame() {

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the view and projection matrix in the uniform block - we only have to do this once per loop iteration.
    glm::mat4 view = mCamera.GetViewMatrix();
    glBindBuffer(GL_UNIFORM_BUFFER, uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // draw 4 cubes
    // RED
    glBindVertexArray(cubeVAO);
    redShader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.75f, 0.75f, 0.0f)); // move top-left
    redShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // GREEN
    greenShader->use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.75f, 0.75f, 0.0f)); // move top-right
    greenShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // YELLOW
    yellowShader->use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-0.75f, -0.75f, 0.0f)); // move bottom-left
    yellowShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // BLUE
    blueShader->use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.75f, -0.75f, 0.0f)); // move bottom-right
    blueShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    checkGlError("glDrawArrays");
}

bool GLSeniorUniform::setSharderPath(const char *vertexPath, const char *fragRedPath,
                                     const char *fragBluePath, const char *fragGreenPath,
                                     const char *fragYellowPath) {
    redShader->getSharderPath(vertexPath, fragRedPath);
    blueShader->getSharderPath(vertexPath, fragBluePath);
    greenShader->getSharderPath(vertexPath, fragGreenPath);
    yellowShader->getSharderPath(vertexPath, fragYellowPath);

    return 0;
}


void GLSeniorUniform::setMoveXY(float dx, float dy, int actionMode) {
    LOGI("setMoveXY dx:%f,dy:%f,actionMode:%d", dy, dy, actionMode);
    float xoffset = dx - lastX;
    float yoffset = lastY - dy; // reversed since y-coordinates go from bottom to top
    lastX = dx;
    lastY = dy;
    mActionMode = actionMode;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void GLSeniorUniform::setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
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


GLSeniorUniform::GLSeniorUniform() {
    redShader = new GLSeniorShader();
    blueShader = new GLSeniorShader();
    greenShader = new GLSeniorShader();
    yellowShader = new GLSeniorShader();

}

GLSeniorUniform::~GLSeniorUniform() {

    //析构函数中释放资源
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &skyboxVAO);

    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &skyboxVBO);


    redShader = nullptr;
    blueShader = nullptr;
    greenShader = nullptr;
    yellowShader = nullptr;

}

void GLSeniorUniform::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void GLSeniorUniform::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}



