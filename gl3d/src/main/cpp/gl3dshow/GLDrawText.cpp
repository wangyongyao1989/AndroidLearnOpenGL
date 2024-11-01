//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2024/10/30.
//

#include "GLDrawText.h"
#include "freetype_2_9_1/freetype/freetype.h"

bool GLDrawText::setupGraphics(int w, int h, const char *path) {
    screenW = w;
    screenH = h;
    LOGI("setupGraphics(%d, %d)", w, h);
    LOGI("ttf: %s", path);
    LOGI("Thread ID:%d", std::this_thread::get_id());
    LoadFacesByASCII(path);
    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    //清屏
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    // Set OpenGL options
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint createProgram = drawTextShader->createProgram();
    checkGlError("createProgram");
    if (!createProgram) {
        LOGE("Could not create shaderId.");
        return false;
    } else {
        LOGD("Shader createProgram succeed");
    }
    GLuint positionHandle = glGetAttribLocation(createProgram, "gl_Position");
    checkGlError("glGetAttribLocation");
    LOGE("positionHandle:%d", positionHandle);

    if (!positionHandle) {
        LOGE("Could not find gl_Position");
        return false;
    }

    glm::vec2 viewport(screenW, screenH);
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(screenW), 0.0f,
                                      static_cast<GLfloat>(screenH));
    drawTextShader->use();
    drawTextShader->setMat4("projection", projection);
    checkGlError("drawTextShader->setMat4(projection");


    // Configure VAO/VBO for texture quads
    glGenVertexArrays(1, &VAO);
    checkGlError("glGenVertexArrays(1, &VAO);");

    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    checkGlError("glBindVertexArray");

    return false;
}

void GLDrawText::renderFrame() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); //禁用byte-alignment限制
    glEnable(GL_BLEND);
    //glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    checkGlError("glBlendFunc");

    glm::vec2 viewport(screenW, screenH);

    RenderText("This is sample text", 300.0f, 500.0f, 2.0f, glm::vec3(0.8, 0.1f, 0.1f), viewport);

}

bool GLDrawText::setSharderPath(const char *vertexPath, const char *fragmentPath) {
    drawTextShader->getSharderPath(vertexPath, fragmentPath);
    return false;
}


GLDrawText::GLDrawText() {
    drawTextShader = new GL3DShader();
}

GLDrawText::~GLDrawText() {

    if (drawTextShader) {
        delete drawTextShader;
        drawTextShader = nullptr;
    }


}

void GLDrawText::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("OpenGL %s = %s\n", name, v);
}

void GLDrawText::checkGlError(const char *op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

void
GLDrawText::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale,
                       glm::vec3 color, glm::vec2 viewport) {

    // 激活对应的渲染状态
    drawTextShader->use();
    checkGlError("drawTextShader->use()");
    drawTextShader->setVec3("textColor", color.x, color.y, color.z);

    glActiveTexture(GL_TEXTURE0);
    checkGlError("glActiveTexture");
    glBindVertexArray(VAO);
    checkGlError("glBindVertexArray(VAO)");

    // 遍历文本中所有的字符
    std::string::const_iterator c;
//    x *= viewport.x;
//    y *= viewport.y;
    LOGE("RenderText x:%f == y:%f", x, y);
    LOGE("RenderText viewportX:%f == viewportY:%f", viewport.x, viewport.y);

    for (c = text.begin(); c != text.end(); c++) {
        Character ch = Characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
        // 归一化
//        xpos /= viewport.x;
//        ypos /= viewport.y;

        GLfloat w = ch.Size.x * scale;
        GLfloat h = ch.Size.y * scale;

//        w /= viewport.x;
//        h /= viewport.y;
//        LOGE("TextRenderSample::RenderText [xpos,ypos,w,h]=[%f, %f, %f, %f], ch.advance >> 6 = %d"
//                , xpos, ypos, w, h, ch.Advance >> 6);

        // 对每个字符更新VBO
        GLfloat vertices[6][4] = {
                {xpos,     ypos + h, 0.0, 0.0},
                {xpos,     ypos,     0.0, 1.0},
                {xpos + w, ypos,     1.0, 1.0},

                {xpos,     ypos + h, 0.0, 0.0},
                {xpos + w, ypos,     1.0, 1.0},
                {xpos + w, ypos + h, 1.0, 0.0}
        };
        // 在四边形上绘制字形纹理
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        checkGlError("glBindTexture");
        // 更新VBO内存的内容
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        checkGlError("glBindBuffer");
        // Be sure to use glBufferSubData and not glBufferData
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        checkGlError("glBufferSubData");
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        checkGlError("glBindBuffer(GL_ARRAY_BUFFER");
        // 绘制四边形
        glDrawArrays(GL_TRIANGLES, 0, 6);
        checkGlError("glDrawArrays(GL_TRIANGLES");

        // 更新位置到下一个字形的原点，注意单位是1/64像素
        // 位偏移6个单位来获取单位为像素的值 (2^6 = 64)
        x += (ch.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

}

void GLDrawText::LoadFacesByASCII(const char *path) {
    // FreeType
    FT_Library ft;
    // All functions return a value different than 0 whenever an error occurred
    if (FT_Init_FreeType(&ft))
        LOGE("ERROR::FREETYPE: Could not init FreeType Library");

    // Load font as face
    FT_Face face;
    if (FT_New_Face(ft, path, 0, &face))
        LOGE("ERROR::FREETYPE: Failed to load font");

    // Set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, 48);

    // Disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Load first 128 characters of ASCII set
    for (GLubyte c = 0; c < 128; c++) {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            LOGE("ERROR::FREETYTPE: Failed to load Glyph");
            continue;
        }
        // Generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        checkGlError("LoadFacesByASCII glGenTextures");
//        LOGE("fore c= %d",c);
//        LOGE("texture === %d",texture);

        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                //选择GL_LUMINANCE来于:
                // https://stackoverflow.com/questions/70285879/android12-opengles3-0-glteximage2d-0x502-error
                GL_LUMINANCE,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_LUMINANCE,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // Now store character for later use
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<GLuint>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    checkGlError("glBindTexture(GL_TEXTURE_2D, 0);");

    // Destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    LOGE("FT_Done_FreeType");

}





