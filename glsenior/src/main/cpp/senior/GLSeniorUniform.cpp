

#include <iostream>
#include "../includes/GLSeniorUniform.h"

bool GLSeniorUniform::setupGraphics(int w, int h) {
    screenW = w;
    screenH = h;
    LOGI("setupGraphics(%d, %d)", w, h);
    GLuint CubeMapProgram = uniformShader->createProgram();
    if (!CubeMapProgram) {
        LOGE("Could not create CubeMapProgram shaderId.");
        return false;
    }

    GLuint skyboxProgram = skyboxShader->createProgram();
    if (!skyboxProgram) {
        LOGE("Could not create skyboxProgram shaderId.");
        return false;
    }

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    LOGI("glViewport successed!");

    //清屏
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    //开启深度测试
    glEnable(GL_DEPTH_TEST);

    // cube VAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(UniformVertices), &UniformVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *) (3 * sizeof(float)));

    // skybox VAO
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxUniformVertices), &skyboxUniformVertices,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);

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
        cubeTexture = loadTexture(data1, width1, height1, format);
    }

    uniformTexture = loadCubemap(faces);

    if (nrChannels2 == 1) {
        format = GL_RED;
    } else if (nrChannels2 == 3) {
        format = GL_RGB;
    } else if (nrChannels2 == 4) {
        format = GL_RGBA;
    }

    // shader configuration
    // --------------------
    uniformShader->use();
    uniformShader->setInt("texture1", 0);

    skyboxShader->use();
    skyboxShader->setInt("screenTexture", 0);


    return true;
}

void GLSeniorUniform::renderFrame() {

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw scene as normal
    uniformShader->use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(75.0f), glm::vec3(1.0f, 0.3f, 0.5f));
    glm::mat4 view = mCamera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom)
            , (float)screenW / (float)screenH, 0.1f, 100.0f);
    uniformShader->setMat4("model", model);
    uniformShader->setMat4("view", view);
    uniformShader->setMat4("projection", projection);
    uniformShader->setVec3("cameraPos", mCamera.Position);
    // cubes
    glBindVertexArray(cubeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, uniformTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    // draw skybox as last
    // change depth function so depth test passes when values are equal to depth buffer's content
    glDepthFunc(GL_LEQUAL);
    skyboxShader->use();
    // remove translation from the view matrix
    view = glm::mat4(glm::mat3(mCamera.GetViewMatrix()));
    skyboxShader->setMat4("view", view);
    skyboxShader->setMat4("projection", projection);
    // skybox cube
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, uniformTexture);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS); // set depth function back to default

    checkGlError("glDrawArrays");
}

bool GLSeniorUniform::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    uniformShader->getSharderPath(vertexPath, fragmentPath);
    return 0;
}

bool
GLSeniorUniform::setSharderScreenPath(const char *vertexScreenPath,
                                         const char *fragmentScreenPath) {
    skyboxShader->getSharderPath(vertexScreenPath, fragmentScreenPath);
    return 0;
}

void GLSeniorUniform::setPicPath(const char *pic1) {
    LOGI("setPicPath pic1==%s", pic1);
    data1 = stbi_load(pic1, &width1, &height1, &nrChannels1, 0);
}

void
GLSeniorUniform::setSkyBoxPicPath(const char *rightPic, const char *letfPic, const char *topPic,
                                     const char *bottomPic, const char *frontPic,
                                     const char *backPic) {
    faces.push_back(rightPic);
    faces.push_back(letfPic);
    faces.push_back(topPic);
    faces.push_back(bottomPic);
    faces.push_back(frontPic);
    faces.push_back(backPic);
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
    uniformShader = new GLSeniorShader();
    skyboxShader = new GLSeniorShader;
}

GLSeniorUniform::~GLSeniorUniform() {
    cubeTexture = 0;
    uniformTexture = 0;

    //析构函数中释放资源
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &skyboxVAO);

    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &skyboxVBO);


    uniformShader = nullptr;
    skyboxShader = nullptr;

    if (data1) {
        stbi_image_free(data1);
        data1 = nullptr;
    }

    faces.clear();
    colorVertexCode.clear();
    colorFragmentCode.clear();
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

/**
 * 加载纹理
 * @param path
 * @return
 */
int GLSeniorUniform::loadTexture(unsigned char *data, int width, int height, GLenum format) {
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


// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front)
// -Z (back)
// -------------------------------------------------------
int GLSeniorUniform::loadCubemap(vector<std::string> faces) {
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        } else {
            LOGE("Cubemap texture failed to load at path: %s ", faces[i].c_str());
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

