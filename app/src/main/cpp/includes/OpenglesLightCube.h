//
// Created by MMM on 2024/7/24.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#define ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#endif //ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H

#include "OpenGLBase.h"
#include <stb_image.h>
#include "Camera3D.h"


using namespace std;
using namespace glm;
// world space positions of our cubes
const vec3 LightCubePositions[] = {
        vec3(0.0f, 0.0f, 0.0f),
        vec3(2.0f, 5.0f, -15.0f),
        vec3(-1.5f, -2.2f, -2.5f),
        vec3(-3.8f, -2.0f, -12.3f),
        vec3(2.4f, -0.4f, -3.5f),
        vec3(-1.7f, 3.0f, -7.5f),
        vec3(1.3f, -2.0f, -2.5f),
        vec3(1.5f, 2.0f, -2.5f),
        vec3(1.5f, 0.2f, -1.5f),
        vec3(-1.3f, 1.0f, -1.5f)
};

class OpenglesLightCube : public OpenGLBase {

private:
    unsigned int texture1;
    unsigned int texture2;
    unsigned char *data1;
    unsigned char *data2;
    int screenW, screenH;
    int width1, height1, nrChannels1;
    int width2, height2, nrChannels2;
    double timeValue;
    float lastX, lastY;
    int mActionMode;

    // camera
    Camera3D mCamera;

public:

    OpenglesLightCube();

    ~OpenglesLightCube();

    bool setupGraphics(int w, int h) override;

    void renderFrame() override;

    bool setSharderPath(const char *vertexPath, const char *fragmentPath) override;

    void setPicPath(const char *pic1, const char *pic2);

    void setMoveXY(float dx, float dy, int actionMode);

    void setOnScale(float scaleFactor,float focusX, float focusY, int actionMode);

};

