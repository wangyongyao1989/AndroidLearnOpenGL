//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2024/10/23.
//

#ifndef ANDROIDLEARNOPENGL_GLSenior3DShow_H
#define ANDROIDLEARNOPENGL_GLSenior3DShow_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GLCameraSenior.h"
#include "GLSeniorShader.h"

#include "GLSenior3DModel.h"

class GLSenior3DShow {

private:
    GLCameraSenior mCamera;
    float lastX, lastY;
    int mActionMode;

    int screenW, screenH;
    GLSeniorShader *modelShader = nullptr;
    GLSenior3DModel *gl3DModel = nullptr;


public:

    GLSenior3DShow();

    ~GLSenior3DShow();

    bool setupGraphics(int w, int h);

    void renderFrame();

    bool setSharderPath(const char *vertexPath, const char *fragmentPath);

    bool setModelPath(const char *modelPath);

    void setMoveXY(float dx, float dy, int actionMode);

    void setOnScale(float scaleFactor, float focusX, float focusY, int actionMode);

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);
};


#endif //ANDROIDLEARNOPENGL_GLSenior3DShow_H
