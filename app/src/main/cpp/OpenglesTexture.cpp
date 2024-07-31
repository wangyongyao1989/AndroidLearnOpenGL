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
        LOGE("Could not create shaderProgram.");
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
    // -------------------------

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    return true;
}

void OpenglesTexture::renderFrame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    // bind Texture
    glBindTexture(GL_TEXTURE_2D, texture);
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

void OpenglesTexture::setPicPath(const char *pic) {
    LOGI("setPicPath pic==%s", pic);
    picSrc = pic;
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    LOGI("setupGraphics picSrc==%s", picSrc);

//    data = stbi_load(picSrc, &width, &height, &nrChannels, 0);
    LOGI("setPicPath picSrc==%s", picSrc);

}


OpenglesTexture::OpenglesTexture() {

}

OpenglesTexture::~OpenglesTexture() {

}


