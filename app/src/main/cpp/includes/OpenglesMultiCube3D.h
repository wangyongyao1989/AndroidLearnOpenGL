//
// Created by MMM on 2024/7/24.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#define ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#endif //ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H

#include "OpenGLBase.h"
#include <stb_image.h>


using namespace std;

class OpenglesMultiCube3D : public OpenGLBase {

private:
    unsigned int texture1;
    unsigned int texture2;
    unsigned char *data1;
    unsigned char *data2;
    int screenW, screenH;
    int width1, height1, nrChannels1;
    int width2, height2, nrChannels2;

public:

    OpenglesMultiCube3D();

    ~OpenglesMultiCube3D();

    bool setupGraphics(int w, int h) override;

    void renderFrame() override;

    bool setSharderPath(const char *vertexPath, const char *fragmentPath) override;

    void setPicPath(const char *pic1, const char *pic2);


};

