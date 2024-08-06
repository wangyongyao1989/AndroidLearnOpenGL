//
// Created by MMM on 2024/7/30.
//
#include "OpenglesCamera3D.h"
#include <iostream>

bool OpenglesCamera3D::setupGraphics(int w, int h) {
    screenW = w;
    screenH = h;
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

    //绑定VAO
    glBindVertexArray(VAO);
    //把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);


    // 1. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);


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


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    glUseProgram(shaderProgram); // don't forget to activate/use the shader before setting uniforms!
    glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);
//    setInt("texture2", 1);

    return true;
}

void OpenglesCamera3D::renderFrame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
    // bind Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    //2、使用程序
    glUseProgram(gProgram);
    checkGlError("glUseProgram");
    //开启深度测试
    glEnable(GL_DEPTH_TEST);

    // create transformations
    glm::mat4 view = glm::mat4(1.0f);           //观察矩阵(View Matrix)
    glm::mat4 projection = glm::mat4(1.0f);     //投影矩阵(Projection Matrix)

//    float radius = 10.0f;
//    timeValue = 10 / CLOCKS_PER_SEC;
//    float camX = static_cast<float>(sin(timeValue) * radius);
//    float camZ = static_cast<float>(cos(timeValue) * radius);
//    LOGI("setMoveXY camX:%f,camZ:%f", camX,camZ);
    //观察矩阵(View Matrix)平移,glm::LookAt函数需要一个位置、目标和上向量。
//    view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f),
//                       glm::vec3(0.0f, 1.0f, 0.0f));
//    projection = glm::perspective(glm::radians(45.0f), (float) screenW / (float) screenH, 0.1f,
//                                  100.0f);

    //观察矩阵(View Matrix)平移,glm::LookAt函数需要一个位置、目标和上向量。
    view = mCamera.GetViewMatrix();
    projection = glm::perspective(glm::radians(mCamera.Zoom), (float) screenW / (float) screenH,
                                  0.1f,
                                  100.0f);
    // pass them to the shaders (3 different ways)
    setMat4("projection", projection);
    setMat4("view", view);

    // render boxes
    glBindVertexArray(VAO);
    for (unsigned int i = 0; i < 10; i++) {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);                   //模型矩阵(Model Matrix)
        model = glm::translate(model, cameraCubePositions[i]);    //对获取到的模型移动到对应位置
        float angle = 20.0f * i;
        if (i < 6) {
            double timeValue = clock() * 10 / CLOCKS_PER_SEC;
            angle = timeValue * 25.0f;
        }
        //让模型经过旋转矩阵的变化
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    checkGlError("glDrawArrays");
}

bool OpenglesCamera3D::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    return getSharderPath(vertexPath, fragmentPath);
}

void OpenglesCamera3D::setPicPath(const char *pic1, const char *pic2) {
    LOGI("setPicPath pic1==%s", pic1);
    LOGI("setPicPath pic2==%s", pic2);
    // load image, create texture and generate mipmaps
    data1 = stbi_load(pic1, &width1, &height1, &nrChannels1, 0);
    data2 = stbi_load(pic2, &width2, &height2, &nrChannels2, 0);

}

void OpenglesCamera3D::setMoveXY(float dx, float dy, int actionMode) {
    LOGI("setMoveXY dx:%f,dy:%f,actionMode:%d", dy, dy, actionMode);
    float xoffset = dx - lastX;
    float yoffset = lastY - dy; // reversed since y-coordinates go from bottom to top
    lastX = dx;
    lastY = dy;
    mActionMode = actionMode;
    mCamera.ProcessXYMovement(xoffset, yoffset);
}

void OpenglesCamera3D::setOnScale(float scaleFactor, float focusX, float focusY, int actionMode) {
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


OpenglesCamera3D::OpenglesCamera3D() {

}

OpenglesCamera3D::~OpenglesCamera3D() {
    texture1 = 0;
    data1 = nullptr;
    data2 = nullptr;

}


