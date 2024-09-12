//
// Created by MMM on 2024/7/30.
//
#include "OpenglesTexture.h"
#include <iostream>

bool OpenglesTexture::setupGraphics(int w, int h) {

    LOGI("setupGraphics(%d, %d)", w, h);
    LOGI("gVertexShaderCode :%s", gVertexShaderCode);
    LOGI("gFragmentShaderCode :%s", gFragmentShaderCode);
    gProgram = createProgram(gVertexShaderCode, gFragmentShaderCode);
    if (!gProgram) {
        LOGE("Could not create shaderId.");
        return false;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
         gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    LOGI("glViewport successed!");

    //清屏
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //绑定VAO
    glBindVertexArray(VAO);
    //把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textureDemoVertices), textureDemoVertices, GL_STATIC_DRAW);

    //绑定EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textureDemoIndices), indices, GL_STATIC_DRAW);


    // 1. 设置顶点属性指针
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // tell stb_image.h to flip loaded texture's on the y-axis.
    stbi_set_flip_vertically_on_load(true);

    if (data1) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width1, height1, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data1);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data2) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data2);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    glUseProgram(shaderProgram); // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
    // or set it via the texture class
    setInt("texture2", 1);

    return true;
}

void OpenglesTexture::renderFrame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // bind Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //2、使用程序
    glUseProgram(gProgram);
    checkGlError("glUseProgram");
    glBindVertexArray(VAO);

    // be sure to activate the shader before any calls to glUniform
    glUseProgram(shaderProgram);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    checkGlError("glDrawArrays");
}

bool OpenglesTexture::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    return getSharderPath(vertexPath, fragmentPath);
}

void OpenglesTexture::setPicPath(const char *pic1, const char *pic2) {
    LOGI("setPicPath pic1==%s", pic1);
    LOGI("setPicPath pic2==%s", pic2);
    // load image, create texture and generate mipmaps
    data1 = stbi_load(pic1, &width1, &height1, &nrChannels1, 0);
    data2 = stbi_load(pic2, &width2, &height2, &nrChannels2, 0);

}


OpenglesTexture::OpenglesTexture() {

}

OpenglesTexture::~OpenglesTexture() {
    texture1 = 0;
    texture2 = 0;
    data1 = nullptr;
    data2 = nullptr;

}


