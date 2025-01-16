//  Author : wangyongyao https://github.com/wangyongyao1989


#ifndef MYYFFMPEG_GLFBOPostProcessing_H
#define MYYFFMPEG_GLFBOPostProcessing_H

#endif //MYYFFMPEG_GLFBOPostProcessing_H

#include <cstdint>
#include <memory>
#include <android/native_window.h>
#include <android/asset_manager.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <vector>
#include <image/stb_image.h>
#include <jni.h>


#include "GLCameraSenior.h"
#include "GLSeniorShader.h"



using namespace std;
using namespace glm;


const float PostProcessingVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
};

const float PostProcessingPlaneVertices[] = {
        // positions          // texture Coords (note we set these higher than 1
        // (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
        5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
        -5.0f, -0.5f, 5.0f, 0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,

        5.0f, -0.5f, 5.0f, 2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f, 0.0f, 2.0f,
        5.0f, -0.5f, -5.0f, 2.0f, 2.0f
};

// vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
const float PostProcessingQuadVertices[] = {
        // positions   // texCoords
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
};

class GLFBOPostProcessing {
private:
    unsigned int cubeTexture;
    unsigned int floorTexture;
    unsigned char *data1 = nullptr;
    unsigned char *data2 = nullptr;
    int screenW, screenH;
    int width1, height1, nrChannels1;
    int width2, height2, nrChannels2;
    double timeValue;
    float lastX, lastY;
    int mActionMode;


    unsigned int cubeVAO;
    unsigned int cubeVBO;

    unsigned int planeVAO;
    unsigned int planeVBO;

    unsigned int quadVAO;
    unsigned int quadVBO;

    unsigned int framebuffer;
    unsigned int rbo;
    unsigned int textureColorbuffer;



    string colorVertexCode;
    string colorFragmentCode;

    // camera
    GLCameraSenior mCamera;
    GLSeniorShader *fBOShader;
    GLSeniorShader *screenShader;

public:

    GLFBOPostProcessing();

    ~GLFBOPostProcessing();

    bool setupGraphics(int w, int h);

    void renderFrame();

    bool setSharderPath(const char *vertexPath, const char *fragmentPath);

    bool setSharderScreenPath(const char *vertexPathScreen, const char *fragmentPathScreen);

    bool setSharderScreenPathes(string vertexScreenPath, vector<string> fragmentScreenPathes);

    void setPicPath(const char *pic1, const char *pic2);

    void setMoveXY(float dx, float dy, int actionMode);

    void setOnScale(float scaleFactor, float focusX, float focusY, int actionMode);

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);

    int loadTexture(unsigned char *data, int width, int height, GLenum format);


    void setParameters(uint32_t i);

    jint getParameters();

    size_t m_filter = 0;

    string m_vertexStringPath;
    vector<string> m_fragmentStringPathes;

};