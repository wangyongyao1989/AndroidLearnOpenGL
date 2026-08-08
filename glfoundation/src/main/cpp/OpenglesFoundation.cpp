//
// Created by MMM on 2024/7/24.
//

#include <malloc.h>
#include "OpenglesFoundation.h"

using namespace std;

void OpenglesFoundation::renderFrame() {

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //2、使用程序
    glUseProgram(gProgram);
    checkGlError("glUseProgram");
    // seeing as we only have a single VAO there's no need to bind it every time,
    // but we'll do so to keep things a bit more organized
    glBindVertexArray(VAO);
    // 3、绘制物体
//    glDrawArrays(GL_TRIANGLES, 0, 3);
//    glDrawArrays(GL_TRIANGLES, 0, 6);

    // be sure to activate the shader before any calls to glUniform
    glUseProgram(shaderProgram);
    // update shader uniform
    double timeValue = clock() * 10 / CLOCKS_PER_SEC;
    float greenValue = static_cast<float>(sin(timeValue) / 3.0 + 0.5);
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    checkGlError("glDrawArrays");

}


bool OpenglesFoundation::setupGraphics(int w, int h) {
    LOGI("Starting OpenGL ES Graphics Setup...");
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);

    LOGI("Viewport size: %dx%d", w, h);

    // 编译并链接着色器程序
    gProgram = createProgram(gVertexShaderCode, gFragmentShaderCode);
    if (!gProgram) {
        LOGE("Failed to create shader program in setupGraphics");
        return false;
    }

    // 获取顶点着色器中 vPosition 属性的位置
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("Attribute 'vPosition' location: %d", gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    // 初始化背景颜色为深青色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    /**
     * 数据缓冲管理 (VAO/VBO/EBO)
     * 1. VAO (Vertex Array Object): 记录顶点属性配置
     * 2. VBO (Vertex Buffer Object): 将顶点数据传输到 GPU 显存
     * 3. EBO (Element Buffer Object): 索引缓冲，实现顶点复用
     */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 绑定 VAO 开始记录状态
    glBindVertexArray(VAO);

    // 传输顶点坐标数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 传输索引数据
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 配置顶点属性指针 (位置:0, 大小:3, 类型:float, 步长:3*float)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    // 解绑，防止后续操作意外修改当前 VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    LOGI("OpenglesFoundation setup successfully finished.");
    return true;
}

bool OpenglesFoundation::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    return getSharderPath(vertexPath, fragmentPath);
}

OpenglesFoundation::~OpenglesFoundation() {

}

OpenglesFoundation::OpenglesFoundation() {

}








