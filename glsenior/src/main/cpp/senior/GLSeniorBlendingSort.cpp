

#include <iostream>
#include "../includes/GLSeniorBlendingSort.h"

bool GLSeniorBlendingSort::setupGraphics(int w, int h) {
    screenW = w;
    screenH = h;
    LOGI("setupGraphics(%d, %d)", w, h);
    GLuint lightingProgram = blendingSortShader->createProgram();
    if (!lightingProgram) {
        LOGE("Could not create shaderId.");
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
//    glDepthFunc(GL_LESS);
    //深度函数(Depth Function)
//    glDepthFunc(GL_ALWAYS);

    // 设置混合
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // cube VAO
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(BlendingSortVertices), &BlendingSortVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glBindVertexArray(0);

    // plane VAO
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(blendingSortPlaneVertices), &blendingSortPlaneVertices,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glBindVertexArray(0);

    // transparent VAO
    glGenVertexArrays(1, &transparentVAO);
    glGenBuffers(1, &transparentVBO);
    glBindVertexArray(transparentVAO);
    glBindBuffer(GL_ARRAY_BUFFER, transparentVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentSortVertices), transparentSortVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);


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

    if (nrChannels2 == 1) {
        format = GL_RED;
    } else if (nrChannels2 == 3) {
        format = GL_RGB;
    } else if (nrChannels2 == 4) {
        format = GL_RGBA;
    }
    if (data2) {
        floorTexture = loadTexture(data2, width2, height2, format);
    }

    if (nrChannels3 == 1) {
        format = GL_RED;
    } else if (nrChannels3 == 3) {
        format = GL_RGB;
    } else if (nrChannels3 == 4) {
        format = GL_RGBA;
    }

    if (data3) {
        transparentTexture = loadTexture(data3, width3, height3, format);
    }

    // shader configuration
    // --------------------
    blendingSortShader->use();
    blendingSortShader->setInt("texture1", 0);

    return true;
}

void GLSeniorBlendingSort::renderFrame() {

    // sort the transparent windows before rendering
    // map会自动根据键值(Key)对它的值排序，所以只要我们添加了所有的位置，
    // 并以它的距离作为键，它们就会自动根据距离值排序了。
    map<float, glm::vec3> sorted;
    for (unsigned int i = 0; i < windows.size(); i++)
    {
        float distance = glm::length(mCamera.Position - windows[i]);
        sorted[distance] = windows[i];
    }

    // render
    // ------
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // be sure to activate shader when setting uniforms/drawing objects
    // view/projection transformations
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(mCamera.Zoom),
                                            (float) screenW / (float) screenH, 0.1f, 100.0f);
    vec3 cameraMove(0.0f, 0.0f, 3.0f);
    mCamera.Position = cameraMove;
    glm::mat4 view = mCamera.GetViewMatrix();

    blendingSortShader->setMat4("view", view);
    blendingSortShader->setMat4("projection", projection);
    // cubes
    glBindVertexArray(cubeVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, cubeTexture);
    model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    blendingSortShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    blendingSortShader->setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    // floor
    glBindVertexArray(planeVAO);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    blendingSortShader->setMat4("model", glm::mat4(1.0f));
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    // windows
    glBindVertexArray(transparentVAO);
    glBindTexture(GL_TEXTURE_2D, transparentTexture);

   //将以逆序（从远到近）从map中获取值，之后以正确的顺序绘制对应的窗户：
    for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, it->second);
        blendingSortShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    checkGlError("glDrawArrays");
}

bool GLSeniorBlendingSort::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    blendingSortShader->getSharderPath(vertexPath, fragmentPath);
    return 0;
}


void GLSeniorBlendingSort::setPicPath(const char *pic1, const char *pic2,
                                         const char *pic3) {
    LOGI("setPicPath pic1==%s", pic1);
    LOGI("setPicPath pic2==%s", pic2);
    data1 = stbi_load(pic1, &width1, &height1, &nrChannels1, 0);
    data2 = stbi_load(pic2, &width2, &height2, &nrChannels2, 0);
    data3 = stbi_load(pic3, &width3, &height3, &nrChannels3, 0);

}

void GLSeniorBlendingSort::setMoveXY(float dx, float dy, int actionMode) {
    LOGI("setMoveXY dx:%f,dy:%f,actionMode:%d", dy, dy, actionMode);
    float xoffset = dx - lastX;
    float yoffset = lastY - dy; // reversed since y-coordinates go from bottom to top
    lastX = dx;
    lastY = dy;
    mActionMode = actionMode;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void GLSeniorBlendingSort::setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
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


GLSeniorBlendingSort::GLSeniorBlendingSort() {
    blendingSortShader = new GLSeniorShader();
}

GLSeniorBlendingSort::~GLSeniorBlendingSort() {
    cubeTexture = 0;
    floorTexture = 0;
    transparentTexture = 0;
    //析构函数中释放资源
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &planeVBO);


    blendingSortShader = nullptr;

    if (data1) {
        stbi_image_free(data1);
        data1 = nullptr;
    }

    if (data2) {
        stbi_image_free(data2);
        data2 = nullptr;
    }

    if (data3) {
        stbi_image_free(data3);
        data3 = nullptr;
    }

    colorVertexCode.clear();
    colorFragmentCode.clear();
}

void GLSeniorBlendingSort::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void GLSeniorBlendingSort::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

/**
 * 加载纹理
 * @param path
 * @return
 */
int GLSeniorBlendingSort::loadTexture(unsigned char *data, int width, int height, GLenum format) {
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

