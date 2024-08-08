//
// Created by MMM on 2024/8/8.
//

#include "OpenGLMultiShaderBase.h"

GLuint
OpenGLMultiShaderBase::createProgram(const char *pVertexSource, const char *pFragmentSource) {
    GLuint shaderProgram = 0;
    vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        checkGlError("loadShader GL_VERTEX_SHADER");
        return 0;
    }

    fraShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!fraShader) {
        checkGlError("loadShader GL_FRAGMENT_SHADER");
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

GLuint OpenGLMultiShaderBase::createSharderProgram() {
    GLuint gProgram = createProgram(gVertexShaderCode, gFragmentShaderCode);
    if (!gProgram) {
        LOGE("Could not create shaderProgram.");
        return -1;
    }
    return gProgram;
}


bool OpenGLMultiShaderBase::getSharderPath(const char *vertexPath, const char *fragmentPath) {
    ifstream vShaderFile;
    ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (ifstream::failure &e) {
        LOGE("Could not getSharderPath error :%s", e.what());
        return false;
    }

    const char *verCode = vertexCode.c_str();
    const char *fraCode = fragmentCode.c_str();

    gVertexShaderCode = vertexCode.c_str();
    gFragmentShaderCode = vertexCode.c_str();
    LOGI("=====gVertexShaderCode :%s", gVertexShaderCode);
    LOGI("======gFragmentShaderCode :%s", gFragmentShaderCode);
    return true;
}

/**
 * 加载着色器
 * @param shaderType
 * @param pSource
 * @return
 */
GLuint OpenGLMultiShaderBase::loadShader(GLenum shaderType, const char *pSource) {
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

OpenGLMultiShaderBase::OpenGLMultiShaderBase() {

}

OpenGLMultiShaderBase::~OpenGLMultiShaderBase() {
    if (vertexShader) {
        glDeleteShader(vertexShader);
    }
    if (fraShader) {
        glDeleteShader(fraShader);
    }
    vertexCode.clear();
    fragmentCode.clear();
}

void OpenGLMultiShaderBase::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void OpenGLMultiShaderBase::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}






