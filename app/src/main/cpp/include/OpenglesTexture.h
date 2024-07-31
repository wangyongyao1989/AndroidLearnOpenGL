//
// Created by MMM on 2024/7/24.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#define ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#endif //ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H

#include "OpenGLBase.h"
#include <stb_image.h>

using namespace std;

class OpenglesTexture : public OpenGLBase {

private:
    unsigned int texture;
    unsigned char *data;
    int width, height, nrChannels;

public:

    OpenglesTexture();

    ~OpenglesTexture();

    bool setupGraphics(int w, int h) override;

    void renderFrame() override;

    bool setSharderPath(const char *vertexPath, const char *fragmentPath) override;

    void setPicPath(const char *pic);

//    void setPicPath(int w,int h,const char *picData);

};

