//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/27.
//

#include "../includes/GLMatricesFunction.h"

bool GLMatricesFunction::setupGraphics(int w, int h) {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(MFVertices), MFVertices, GL_STATIC_DRAW);

    //绑定EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(MFIndices), MFIndices, GL_STATIC_DRAW);


    // 1. 设置顶点属性指针
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    return false;
}

void GLMatricesFunction::renderFrame() {
    if (m_filter != m_prevFilter) {
        m_prevFilter = m_filter;
        if (m_filter >= 0 && m_filter < m_fragmentStringPathes.size()) {
            isProgramChanged = true;
            deleteProgram(m_program);
            LOGI("render---m_filter：%d", m_filter);
            setSharderStringPath(m_vertexStringPath, m_fragmentStringPathes.at(m_filter));
            createProgram();
        }
    }
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (!bindVertexAttribPointer()) return;
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

bool GLMatricesFunction::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    glslShader->getSharderPath(vertexPath, fragmentPath);
    return false;
}

bool GLMatricesFunction::setSharderStringPath(string vertexPath, string fragmentPath) {
    glslShader->getSharderStringPath(vertexPath, fragmentPath);
    return false;
}

bool GLMatricesFunction::setSharderStringPathes(string vertexPath,
                                             vector<string> fragmentPathes) {
    m_fragmentStringPathes = fragmentPathes;
    m_vertexStringPath = vertexPath;
    return glslShader->getSharderStringPath(vertexPath, m_fragmentStringPathes.front());
}

GLMatricesFunction::GLMatricesFunction() {
    glslShader = new GLSLShader();
}

GLMatricesFunction::~GLMatricesFunction() {
    //析构函数中释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glslShader = nullptr;

    m_resolutionLoc = 0;
    m_timeLoc = 0;
}


void GLMatricesFunction::setParameters(uint32_t params) {
    m_filter = params;
}

uint32_t GLMatricesFunction::getParameters() {
    return m_filter;
}

int GLMatricesFunction::createProgram() {
    m_program = glslShader->createProgram();
    if (!m_program) {
        LOGE("Could not create program.");
        return 0;
    }

    m_vertexPos = (GLuint) glGetAttribLocation(m_program, "position");
    m_resolutionLoc = (GLuint) glGetAttribLocation(m_program, "u_resolution");
    m_timeLoc = (GLuint) glGetAttribLocation(m_program, "u_time");
    return m_program;
}

int GLMatricesFunction::bindVertexAttribPointer() {
    if (!m_program && !createProgram()) {
        LOGE("Could not use program.");
        return 0;
    }

    if (isProgramChanged) {
        glUseProgram(m_program);
        //绑定顶点程序中的position数据
        glVertexAttribPointer(m_vertexPos, 2, GL_FLOAT, GL_FALSE, 0, kMFVerticek);
        glEnableVertexAttribArray(m_vertexPos);

        if (m_resolutionLoc) {
            glslShader->setVec2("u_resolution", screenW, screenH);
        }

        isProgramChanged = false;
    }

    if (m_timeLoc) {
        double timeValue = clock() * 15 / CLOCKS_PER_SEC;
        glslShader->setFloat("u_time", timeValue);
    }


    return m_program;
}

void GLMatricesFunction::deleteProgram(GLuint &program) {
    if (m_program) {
        glUseProgram(0);
        glDeleteProgram(program);
        m_program = 0;
    }
}


void GLMatricesFunction::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void GLMatricesFunction::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}


