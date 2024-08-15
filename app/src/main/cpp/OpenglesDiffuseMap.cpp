
#include "OpenglesDiffuseMap.h"
#include <iostream>

bool OpenglesDiffuseMap::setupGraphics(int w, int h) {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(DiffuseMapVertices), DiffuseMapVertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //绑定灯光立方体数据
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    return true;
}

void OpenglesDiffuseMap::renderFrame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

    //开启深度测试
    glEnable(GL_DEPTH_TEST);
    // be sure to activate shader when setting uniforms/drawing objects
    lightColorShader->use();

//    lightColorShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    double timeValue = clock() * 8 / CLOCKS_PER_SEC;
    vec3 lightColor;
    lightColor.x = sin(timeValue * 2.0f);
    lightColor.y = sin(timeValue * 0.7f);
    lightColor.z = sin(timeValue * 1.3f);
    vec3 diffuseColor = lightColor * glm::vec3(0.5f); // decrease the influence
    vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // low influence
    lightColorShader->setVec3("light.ambient", ambientColor);
    lightColorShader->setVec3("light.diffuse", diffuseColor);
    lightColorShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    lightColorShader->setVec3("light.position", DiffuseMapLightPos);
    lightColorShader->setVec3("viewPos", mCamera.Position);

    lightColorShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
    lightColorShader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    lightColorShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
    lightColorShader->setFloat("material.shininess", 32.0f);

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom),
                                            (float) screenW / (float) screenH, 0.1f, 100.0f);
    vec3 cameraMove(0.0f, 0.0f, 5.0f);
    mCamera.Position = cameraMove;
    glm::mat4 view = mCamera.GetViewMatrix();
    lightColorShader->setMat4("projection", projection);
    lightColorShader->setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), DiffuseMapLightPos);
    lightColorShader->setMat4("model", model);

    // render the cube
    glBindVertexArray(cubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // also draw the lamp object
    lightCubeShader->use();
    lightCubeShader->setMat4("projection", projection);
    lightCubeShader->setMat4("view", view);
    model = glm::mat4(1.0f);
    model = glm::translate(model, DiffuseMapLightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    lightCubeShader->setMat4("model", model);

    glBindVertexArray(lightCubeVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    checkGlError("glDrawArrays");
}

bool OpenglesDiffuseMap::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    lightColorShader->getSharderPath(vertexPath, fragmentPath);
    return 0;
}

bool OpenglesDiffuseMap::setColorSharderPath(const char *vertexPath, const char *fragmentPath) {
    lightCubeShader->getSharderPath(vertexPath, fragmentPath);
    return false;
}

void OpenglesDiffuseMap::setPicPath(const char *pic1, const char *pic2) {
    picSrc1 = pic1;
    picSrc2 = pic2;
    LOGI("setPicPath picSrc1==%s", picSrc1);
    LOGI("setPicPath picSrc2==%s", picSrc2);
}

void OpenglesDiffuseMap::setMoveXY(float dx, float dy, int actionMode) {
    LOGI("setMoveXY dx:%f,dy:%f,actionMode:%d", dy, dy, actionMode);
    float xoffset = dx - lastX;
    float yoffset = lastY - dy; // reversed since y-coordinates go from bottom to top
    lastX = dx;
    lastY = dy;
    mActionMode = actionMode;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void OpenglesDiffuseMap::setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
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


OpenglesDiffuseMap::OpenglesDiffuseMap() {
    lightColorShader = new OpenGLShader();
    lightCubeShader = new OpenGLShader();
}

OpenglesDiffuseMap::~OpenglesDiffuseMap() {
    texture1 = 0;
    picSrc1 = nullptr;
    picSrc2 = nullptr;
    //析构函数中释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    lightCubeShader = nullptr;
    lightColorShader = nullptr;

    colorVertexCode.clear();
    colorFragmentCode.clear();
}

void OpenglesDiffuseMap::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void OpenglesDiffuseMap::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

/**
 * 加载纹理
 * @param path
 * @return
 */
int OpenglesDiffuseMap::loadTexture(const char *path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        checkGlError("Texture failed to load at path: ");
        stbi_image_free(data);
    }

    return textureID;
}

