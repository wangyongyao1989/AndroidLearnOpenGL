//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/20.
//

#include "GLShapingFunction.h"

bool GLShapingFunction::setupGraphics(int w, int h) {
    screenW = w;
    screenH = h;
    GLuint program = glslShader->createProgram();
    if (!program) {
        LOGE("Could not create program.");
        return false;
    }

    gvPositionHandle = glGetAttribLocation(program, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
         gvPositionHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    LOGI("glViewport successed!");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //绑定VAO
    glBindVertexArray(VAO);
    //把顶点数组复制到缓冲中供OpenGL使用
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SFVertices), SFVertices, GL_STATIC_DRAW);

    //绑定EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SFIndices), SFIndices, GL_STATIC_DRAW);


    // 1. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return false;
}

void GLShapingFunction::renderFrame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //2、使用程序
    glslShader->use();
    checkGlError("glUseProgram");
    glBindVertexArray(VAO);
//    glUseProgram(shaderProgram);
    glslShader->use();

    // update shader uniform
    double timeValue = clock() * 10 / CLOCKS_PER_SEC;
    float greenValue = static_cast<float>(sin(timeValue) / 3.0 + 0.5);
    int vertexColorLocation = glGetUniformLocation(glslShader->shaderId, "ourColor");

    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    checkGlError("glDrawArrays");
}

bool GLShapingFunction::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    glslShader->getSharderPath(vertexPath, fragmentPath);
    return false;
}

GLShapingFunction::GLShapingFunction() {
    glslShader = new GLSLShader();
}

GLShapingFunction::~GLShapingFunction() {
    //析构函数中释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glslShader = nullptr;

}

void GLShapingFunction::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void GLShapingFunction::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}


