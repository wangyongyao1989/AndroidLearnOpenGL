
#include "OpenglesMultiLight.h"
#include <iostream>

bool OpenglesMultiLight::setupGraphics(int w, int h) {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(MultiLightVertices), MultiLightVertices, GL_STATIC_DRAW);
    glBindVertexArray(cubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //绑定灯光立方体数据
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // load and create a texture
    LOGI("load and create a texture!");
    GLenum format;
    if (nrChannels1 == 1) {
        format = GL_RED;
    } else if (nrChannels1 == 3) {
        format = GL_RGB;
    } else if (nrChannels1 == 4) {
        format = GL_RGBA;
    }
//    LOGI("texture1 format==%d", format);
    if (data1) {
        diffuseMapTexture = loadTexture(data1, width1, height1, format);
    }

    if (nrChannels2 == 1) {
        format = GL_RED;
    } else if (nrChannels2 == 3) {
        format = GL_RGB;
    } else if (nrChannels2 == 4) {
        format = GL_RGBA;
    }
    if (data2) {
        specularMapTexture = loadTexture(data2, width2, height2, format);
    }

    lightColorShader->use();
    lightColorShader->setInt("material.diffuse", 0);
    lightColorShader->setInt("material.specular", 1);

    return true;
}

void OpenglesMultiLight::renderFrame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

    //开启深度测试
    glEnable(GL_DEPTH_TEST);
    // be sure to activate shader when setting uniforms/drawing objects
    lightColorShader->use();
    lightColorShader->setVec3("viewPos", mCamera.Position);
    // material properties
    lightColorShader->setFloat("material.shininess", 32.0f);


    //1、定向光照
    lightColorShader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
    lightColorShader->setVec3("dirLight.ambient", 0.5f, 0.5f, 0.5f);
    lightColorShader->setVec3("dirLight.diffuse", 1.0f, 1.0f, 1.0f);
    lightColorShader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

    //2、点光源
    //点光源1
    lightColorShader->setVec3("pointLights[0].position", pointLightPositions[0]);
    lightColorShader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
    lightColorShader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
    lightColorShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
    lightColorShader->setFloat("pointLights[0].constant", 1.0f);
    lightColorShader->setFloat("pointLights[0].linear", 0.09f);
    lightColorShader->setFloat("pointLights[0].quadratic", 0.032f);
    // point light 2
    lightColorShader->setVec3("pointLights[1].position", pointLightPositions[1]);
    lightColorShader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
    lightColorShader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
    lightColorShader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
    lightColorShader->setFloat("pointLights[1].constant", 1.0f);
    lightColorShader->setFloat("pointLights[1].linear", 0.09f);
    lightColorShader->setFloat("pointLights[1].quadratic", 0.032f);
    // point light 3
    lightColorShader->setVec3("pointLights[2].position", pointLightPositions[2]);
    lightColorShader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
    lightColorShader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
    lightColorShader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
    lightColorShader->setFloat("pointLights[2].constant", 1.0f);
    lightColorShader->setFloat("pointLights[2].linear", 0.09f);
    lightColorShader->setFloat("pointLights[2].quadratic", 0.032f);
    // point light 4
    lightColorShader->setVec3("pointLights[3].position", pointLightPositions[3]);
    lightColorShader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
    lightColorShader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
    lightColorShader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
    lightColorShader->setFloat("pointLights[3].constant", 1.0f);
    lightColorShader->setFloat("pointLights[3].linear", 0.09f);
    lightColorShader->setFloat("pointLights[3].quadratic", 0.032f);

    // 3、聚光
    lightColorShader->setVec3("spotLight.position", mCamera.Position);
    lightColorShader->setVec3("spotLight.direction", mCamera.Front);
    lightColorShader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
    lightColorShader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
    lightColorShader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
    lightColorShader->setFloat("spotLight.constant", 1.0f);
    lightColorShader->setFloat("spotLight.linear", 0.09f);
    lightColorShader->setFloat("spotLight.quadratic", 0.032f);
    lightColorShader->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    lightColorShader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom),
                                            (float) screenW / (float) screenH, 0.1f, 100.0f);
    vec3 cameraMove(0.0f, 0.0f, 8.0f);
    mCamera.Position = cameraMove;
    glm::mat4 view = mCamera.GetViewMatrix();
    lightColorShader->setMat4("projection", projection);
    lightColorShader->setMat4("view", view);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.3f, 0.5f));
    lightColorShader->setMat4("model", model);

    // bind diffuse map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMapTexture);

    // bind specular map
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMapTexture);


    // render containers
    glBindVertexArray(cubeVAO);
    for (unsigned int i = 0; i < 10; i++)
    {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, MultiLightCubePositions[i]);
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        lightColorShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }


    // also draw the lamp object
    lightCubeShader->use();
    lightCubeShader->setMat4("projection", projection);
    lightCubeShader->setMat4("view", view);

    glBindVertexArray(lightCubeVAO);
    for (unsigned int i = 0; i < 4; i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightPositions[i]);
        model = glm::scale(model, glm::vec3(0.3f)); // Make it a smaller cube
        lightCubeShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    checkGlError("glDrawArrays");
}

bool OpenglesMultiLight::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    lightColorShader->getSharderPath(vertexPath, fragmentPath);
    return 0;
}

bool OpenglesMultiLight::setColorSharderPath(const char *vertexPath, const char *fragmentPath) {
    lightCubeShader->getSharderPath(vertexPath, fragmentPath);
    return false;
}

void OpenglesMultiLight::setPicPath(const char *pic1, const char *pic2) {
    LOGI("setPicPath pic1==%s", pic1);
    LOGI("setPicPath pic2==%s", pic2);
    data1 = stbi_load(pic1, &width1, &height1, &nrChannels1, 0);
    data2 = stbi_load(pic2, &width2, &height2, &nrChannels2, 0);
}

void OpenglesMultiLight::setMoveXY(float dx, float dy, int actionMode) {
    LOGI("setMoveXY dx:%f,dy:%f,actionMode:%d", dy, dy, actionMode);
    float xoffset = dx - lastX;
    float yoffset = lastY - dy; // reversed since y-coordinates go from bottom to top
    lastX = dx;
    lastY = dy;
    mActionMode = actionMode;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void OpenglesMultiLight::setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
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


OpenglesMultiLight::OpenglesMultiLight() {
    lightColorShader = new OpenGLShader();
    lightCubeShader = new OpenGLShader();
}

OpenglesMultiLight::~OpenglesMultiLight() {
    diffuseMapTexture = 0;
    specularMapTexture = 0;
    //析构函数中释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    lightCubeShader = nullptr;
    lightColorShader = nullptr;

    if (data1) {
        stbi_image_free(data1);
        data1 = nullptr;
    }

    if (data2) {
        stbi_image_free(data2);
        data2 = nullptr;
    }

    colorVertexCode.clear();
    colorFragmentCode.clear();
}

void OpenglesMultiLight::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void OpenglesMultiLight::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

/**
 * 加载纹理
 * @param path
 * @return
 */
int OpenglesMultiLight::loadTexture(unsigned char *data, int width, int height, GLenum format) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
//    LOGI("loadTexture format =%d", format);
    if (data) {
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

