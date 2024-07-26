//
// Created by MMM on 2024/7/24.
//

#include <malloc.h>
#include "OpenglesCode.h"
#include "OpenGLConstants.h"

void OpenglesCode::renderFrame() {

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
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    checkGlError("glDrawArrays");

}

bool OpenglesCode::setupGraphics(int w, int h) {
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
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
//    glBufferData(GL_ARRAY_BUFFER, sizeof(gTriangleVertices), gTriangleVertices, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //绑定EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // 1. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return true;
}

void OpenglesCode::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);

}

void OpenglesCode::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }

}

/**
 * 加载着色器
 * @param shaderType
 * @param pSource
 * @return
 */
GLuint OpenglesCode::loadShader(GLenum shaderType, const char *pSource) {
    GLuint shader = glCreateShader(shaderType);     //创建着色器
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);  //着色器源码附加到着色器对象上
        glCompileShader(shader);                    //编译着着色器
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                         shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);     //删除着色器对象
                shader = 0;
            }
        }
    }
    return shader;
}

/**
 *  连接编译顶点和片元程序
 * @param pVertexSource  顶点程序
 * @param pFragmentSource 片元程序
 * @return
 */
GLuint OpenglesCode::createProgram(const char *pVertexSource, const char *pFragmentSource) {
    vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    fraShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!fraShader) {
        return 0;
    }

    shaderProgram = glCreateProgram();      //创建一个着色程序对象
    if (shaderProgram) {
        glAttachShader(shaderProgram, vertexShader);        //把着色器附加到了程序对象上
        checkGlError("glAttachShader");
        glAttachShader(shaderProgram, fraShader);
        checkGlError("glAttachShader");
        glLinkProgram(shaderProgram);   //链接程序对象
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);  //检测链接着色器程序是否失败
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = (char *) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(shaderProgram, bufLength, NULL, buf);
                    LOGE("Could not link shaderProgram:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(shaderProgram);     //
            shaderProgram = 0;
        }
    }
    return shaderProgram;

}

OpenglesCode::~OpenglesCode() {
    if (vertexShader) {
        glDeleteShader(vertexShader);
    }
    if (fraShader) {
        glDeleteShader(fraShader);
    }
    //析构函数中释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}




