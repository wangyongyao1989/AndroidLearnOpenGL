//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/10.
//

#ifndef ANDROIDLEARNOPENGL_GL3DANIMATIONSHOW_H
#define ANDROIDLEARNOPENGL_GL3DANIMATIONSHOW_H
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "GLCamera3D.h"
#include "GL3DShader.h"
#include "../animator/ModelAnimation.h"
#include "animator/Animation.h"
#include "animator/Animator.h"

class GL3DAnimationShow {
private:
    GLCamera3D mCamera;
    float lastX, lastY;
    int mActionMode;

    int screenW, screenH;
    GL3DShader *modelShader = nullptr;
    ModelAnimation *gl3DModel = nullptr;
    Animation *animation = nullptr;
    Animator *animator = nullptr;

    // timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

public:

    GL3DAnimationShow();

    ~GL3DAnimationShow();

    bool setupGraphics(int w, int h);

    void renderFrame();

    bool setSharderPath(const char *vertexPath, const char *fragmentPath);

    bool setModelPath(const char *modelPath);

    void setMoveXY(float dx, float dy, int actionMode);

    void setOnScale(float scaleFactor, float focusX, float focusY, int actionMode);

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);
};


#endif //ANDROIDLEARNOPENGL_GL3DANIMATIONSHOW_H
