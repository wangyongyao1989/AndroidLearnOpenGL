//
// Created by MMM on 2024/7/24.
//

#ifndef ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
#define ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H

#include "OpenGLSingleShaderBase.h"


using namespace std;

class OpenglesFoundation : public OpenGLSingleShaderBase {

private:

public:

    OpenglesFoundation();

    ~OpenglesFoundation();

    bool setupGraphics(int w, int h) override;

    void renderFrame() override;

    bool setSharderPath(const char *vertexPath, const char *fragmentPath) override;

};


#endif //ANDROIDLEARNOPENGL_OPENGLESFOUNDATION_H
