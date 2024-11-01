//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2024/10/30.
//

#ifndef ANDROIDLEARNOPENGL_GLDRAWTEXT_H
#define ANDROIDLEARNOPENGL_GLDRAWTEXT_H

#include "GL3DShader.h"
#include <map>
// FreeType
#include <freetype_2_9_1/ft2build.h>
#include <freetype_2_9_1/freetype/ftglyph.h>
#include FT_FREETYPE_H

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
};


class GLDrawText {

private:
    int screenW, screenH;
    GL3DShader *drawTextShader = nullptr;
    map<GLchar, Character> Characters;
    GLuint VAO = GL_NONE;
    GLuint VBO = GL_NONE;

    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale,
                    glm::vec3 color, glm::vec2 viewport);

    void LoadFacesByASCII(const char *path);

    void printGLString(const char *name, GLenum s);

    void checkGlError(const char *op);

public:

    GLDrawText();

    ~GLDrawText();

    bool setupGraphics(int w, int h, const char *path);

    void renderFrame();

    bool setSharderPath(const char *vertexPath, const char *fragmentPath);


};


#endif //ANDROIDLEARNOPENGL_GLDRAWTEXT_H
