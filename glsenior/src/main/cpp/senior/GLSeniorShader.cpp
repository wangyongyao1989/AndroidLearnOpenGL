//
// Created by MMM on 2024/8/8.
//
#include "../includes/GLSeniorShader.h"

/**
 * 创建顶点、片段着色器程序
 * @return
 */
GLuint
GLSeniorShader::createProgram() {
    vertexShader = loadShader(GL_VERTEX_SHADER, gVertexShaderCode);
    LOGI("=====gVertexShaderCode :%s", gVertexShaderCode);
    LOGI("======gFragmentShaderCode :%s", gFragmentShaderCode);
    if (!vertexShader) {
        checkGlError("loadShader GL_VERTEX_SHADER");
        return 0;
    }

    fraShader = loadShader(GL_FRAGMENT_SHADER, gFragmentShaderCode);

    if (!fraShader) {
        checkGlError("loadShader GL_FRAGMENT_SHADER");
        return 0;
    }

    shaderId = glCreateProgram();      //创建一个着色程序对象
    if (shaderId) {
        glAttachShader(shaderId, vertexShader);        //把着色器附加到了程序对象上
        checkGlError("glAttachShader");
        glAttachShader(shaderId, fraShader);
        checkGlError("glAttachShader");
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
                    LOGE("Could not link shaderId:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(shaderId);     //
            shaderId = 0;
        }
    }
    return shaderId;
}

/**
 * 创建顶点、几何、片段着色器程序
 * @return
 */
GLuint
GLSeniorShader::createVFGProgram() {
    vertexShader = loadShader(GL_VERTEX_SHADER, gVertexShaderCode);
    LOGI("=====gVertexShaderCode :%s", gVertexShaderCode);
    LOGI("======gFragmentShaderCode :%s", gFragmentShaderCode);
    LOGI("======gGeometryShaderCode :%s", gGeometryShaderCode);

    if (!vertexShader) {
        checkGlError("loadShader GL_VERTEX_SHADER");
        return 0;
    }

    fraShader = loadShader(GL_FRAGMENT_SHADER, gFragmentShaderCode);

    if (!fraShader) {
        checkGlError("loadShader GL_FRAGMENT_SHADER");
        return 0;
    }

    geometryShader = loadShader(GL_FRAGMENT_SHADER, gGeometryShaderCode);

    if (!geometryShader) {
        checkGlError("loadShader GeometryShader");
        return 0;
    }

    shaderId = glCreateProgram();      //创建一个着色程序对象
    if (shaderId) {
        glAttachShader(shaderId, vertexShader);        //把顶点着色器附加到了程序对象上
        checkGlError("glAttachShader");
        glAttachShader(shaderId, fraShader);           //把片段着色器附加到了程序对象上
        checkGlError("glAttachShader");
        glAttachShader(shaderId, geometryShader);      //把几何着色器附加到了程序对象上
        checkGlError("glAttachShader");
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
                    LOGE("Could not link shaderId:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(shaderId);     //
            shaderId = 0;
        }
    }
    return shaderId;
}

/**
 * 加载着色器
 * @param shaderType
 * @param pSource
 * @return
 */
GLuint GLSeniorShader::loadShader(GLenum shaderType, const char *pSource) {
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

bool GLSeniorShader::getSharderPath(const char *vertexPath, const char *fragmentPath) {
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
        LOGE("Could not getVFGSharderPath error :%s", e.what());
        return false;
    }
    gVertexShaderCode = vertexCode.c_str();
    gFragmentShaderCode = fragmentCode.c_str();

    return true;
}


bool GLSeniorShader::getSharderStringPath(string vertexPath, string fragmentPath) {
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
        LOGE("Could not getVFGSharderPath error :%s", e.what());
        return false;
    }
    gVertexShaderCode = vertexCode.c_str();
    gFragmentShaderCode = fragmentCode.c_str();

    return true;
}


bool GLSeniorShader::getVFGSharderPath(const char *vertexPath, const char *fragmentPath,
                                       const char *geometryPath) {
    ifstream vShaderFile;
    ifstream fShaderFile;
    ifstream gShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
    gShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        gShaderFile.open(geometryPath);

        stringstream vShaderStream, fShaderStream, gShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        gShaderStream << gShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        gShaderFile.close();

        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        geometryCode = gShaderStream.str();
    }
    catch (ifstream::failure &e) {
        LOGE("Could not getVFGSharderPath error :%s", e.what());
        return false;
    }
    gVertexShaderCode = vertexCode.c_str();
    gFragmentShaderCode = fragmentCode.c_str();
    gGeometryShaderCode = geometryCode.c_str();
    return true;
}

void GLSeniorShader::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void GLSeniorShader::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

GLSeniorShader::~GLSeniorShader() {
    if (vertexShader) {
        glDeleteShader(vertexShader);
    }
    if (fraShader) {
        glDeleteShader(fraShader);
    }
    if (!vertexCode.empty()) {
        vertexCode.clear();
    }
    if (!fragmentCode.empty()) {
        fragmentCode.clear();
    }
    if (!geometryCode.empty()) {
        geometryCode.clear();
    }


    gVertexShaderCode = nullptr;
    gFragmentShaderCode = nullptr;
    gGeometryShaderCode = nullptr;

}

GLSeniorShader::GLSeniorShader() {

}

void GLSeniorShader::setGVertexShaderCode(const char *gVertexShaderCode) {
    GLSeniorShader::gVertexShaderCode = gVertexShaderCode;
}

void GLSeniorShader::setGFragmentShaderCode(const char *gFragmentShaderCode) {
    GLSeniorShader::gFragmentShaderCode = gFragmentShaderCode;
}

void GLSeniorShader::setGGeometryShaderCode(const char *gFragmentShaderCode) {
    GLSeniorShader::gFragmentShaderCode = gFragmentShaderCode;
}
