//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2024/10/23.
//

#ifndef ANDROIDLEARNOPENGL_GL3DSHOW_H
#define ANDROIDLEARNOPENGL_GL3DSHOW_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GLCamera3D.h"
#include "GL3DShader.h"

class GL3DShow {

private:


    GLCamera3D mCamera;
    float lastX, lastY;
    int mActionMode;

    int screenW, screenH;
    GL3DShader *modelShader;


public:

    GL3DShow();

    ~GL3DShow();

    bool setupGraphics(int w, int h);

    void renderFrame();

    bool setSharderPath(const char *vertexPath, const char *fragmentPath);

    bool setModelPath(const char *modelPath);

    void setMoveXY(float dx, float dy, int actionMode);

    void setOnScale(float scaleFactor, float focusX, float focusY, int actionMode);

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);
};


#endif //ANDROIDLEARNOPENGL_GL3DSHOW_H
