//
// Created by MMM on 2024/7/24.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#define ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#endif //ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H

#include "OpenGLSingleShaderBase.h"
#include <stb_image.h>


using namespace std;

class Opengles3D : public OpenGLSingleShaderBase {

private:
    unsigned int texture1;
    unsigned int texture2;
    unsigned char *data1;
    unsigned char *data2;
    int screenW, screenH;
    int width1, height1, nrChannels1;
    int width2, height2, nrChannels2;

public:

    Opengles3D();

    ~Opengles3D();

    bool setupGraphics(int w, int h) override;

    void renderFrame() override;

    bool setSharderPath(const char *vertexPath, const char *fragmentPath) override;

    void setPicPath(const char *pic1, const char *pic2);

//    void setPicPath(int w,int h,const char *picData);

};

