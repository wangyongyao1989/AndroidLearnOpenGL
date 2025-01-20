
#ifndef ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#define ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#endif //ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H

#include <image/stb_image.h>
#include "GLCameraSenior.h"
#include "GLSeniorShader.h"

using namespace std;
using namespace glm;


const float GeometryPoint[] = {
        -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, // top-left
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, // top-right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f  // bottom-left
};


class GLSeniorGeometry {

private:

    int screenW, screenH;
    double timeValue;
    float lastX, lastY;
    int mActionMode;


    unsigned int VAO;
    unsigned int VBO;


    // camera
    GLCameraSenior mCamera;
    GLSeniorShader *geometryShader;

    unsigned int uboMatrices;


public:

    GLSeniorGeometry();

    ~GLSeniorGeometry();

    bool setupGraphics(int w, int h);

    void renderFrame();

    bool setSharderPath(const char *vertexPath, const char *fragRedPath, const char *geometryPath);


    void setMoveXY(float dx, float dy, int actionMode);

    void setOnScale(float scaleFactor, float focusX, float focusY, int actionMode);

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);

    int loadTexture(unsigned char *data, int width, int height, GLenum format);

    int loadCubemap(vector<std::string> faces);

};

