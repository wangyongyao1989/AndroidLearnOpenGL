//
// Created by MMM on 2024/8/8.
//

#include "OpenGLShader.h"



GLuint
OpenGLShader::createProgram() {
    LOGI("Creating GPU program...");
    vertexShader = loadShader(GL_VERTEX_SHADER, gVertexShaderCode);
    if (!vertexShader) {
        LOGE("Failed to load vertex shader");
        checkGlError("loadShader GL_VERTEX_SHADER");
        return 0;
    }

    fraShader = loadShader(GL_FRAGMENT_SHADER, gFragmentShaderCode);
    if (!fraShader) {
        LOGE("Failed to load fragment shader");
        checkGlError("loadShader GL_FRAGMENT_SHADER");
        return 0;
    }

    shaderId = glCreateProgram();      //创建一个着色程序对象
    if (shaderId) {
        glAttachShader(shaderId, vertexShader);        //把着色器附加到了程序对象上
        checkGlError("glAttachShader Vertex");
        glAttachShader(shaderId, fraShader);
        checkGlError("glAttachShader Fragment");

        LOGI("Linking program...");
        glLinkProgram(shaderId);   //链接程序对象
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(shaderId, GL_LINK_STATUS, &linkStatus);  //检测链接着色器程序是否失败
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(shaderId, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = (char *) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(shaderId, bufLength, NULL, buf);
                    LOGE("Could not link shader program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(shaderId);
            shaderId = 0;
        } else {
            LOGI("Shader program linked successfully with ID: %d", shaderId);
        }
    }
    return shaderId;
}

/**
 * 加载并编译单着色器源码
 * @param shaderType 着色器类型 (GL_VERTEX_SHADER 或 GL_FRAGMENT_SHADER)
 * @param pSource 着色器 GLSL 源码
 * @return 编译后的着色器对象句柄
 */
GLuint OpenGLShader::loadShader(GLenum shaderType, const char *pSource) {
    LOGI("Compiling shader type: %d", shaderType);
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
                    LOGE("Shader compilation failed (%d):\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);     //删除着色器对象
                shader = 0;
            }
        } else {
            LOGI("Shader type %d compiled successfully", shaderType);
        }
    }
    return shader;
}

bool OpenGLShader::getSharderPath(const char *vertexPath, const char *fragmentPath) {
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
    gVertexShaderCode = vertexCode.c_str();
    gFragmentShaderCode = fragmentCode.c_str();

    return true;
}

void OpenGLShader::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void OpenGLShader::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

OpenGLShader::~OpenGLShader() {
    if (vertexShader) {
        glDeleteShader(vertexShader);
    }
    if (fraShader) {
        glDeleteShader(fraShader);
    }
    vertexCode.clear();
    fragmentCode.clear();

    gVertexShaderCode = nullptr;
    gFragmentShaderCode = nullptr;
}

OpenGLShader::OpenGLShader() {

}
