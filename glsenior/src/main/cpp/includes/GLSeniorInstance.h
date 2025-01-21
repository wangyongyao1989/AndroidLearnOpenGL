
#ifndef ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#define ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#endif //ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H

#include <image/stb_image.h>
#include "GLCameraSenior.h"
#include "GLSeniorShader.h"

using namespace std;
using namespace glm;



// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
const float InstanceQuadVertices[] = {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
        0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        0.05f,  0.05f,  0.0f, 1.0f, 1.0f
};


class GLSeniorInstance {

private:

    int screenW, screenH;
    double timeValue;
    float lastX, lastY;
    int mActionMode;

    // camera
    GLCameraSenior mCamera;
    GLSeniorShader *instanceShader;

    glm::vec2 translations[100];

    unsigned int instanceVBO;
    unsigned int quadVAO, quadVBO;


public:

    GLSeniorInstance();

    ~GLSeniorInstance();

    bool setupGraphics(int w, int h);

    void renderFrame();

    bool setSharderPath(const char *vertexPath, const char *fragRedPath);


    void setMoveXY(float dx, float dy, int actionMode);

    void setOnScale(float scaleFactor, float focusX, float focusY, int actionMode);

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);

    int loadTexture(unsigned char *data, int width, int height, GLenum format);


};

