//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2024/10/25.
//

#ifndef ANDROIDLEARNOPENGL_GLSENIOR3DMESH_H
#define ANDROIDLEARNOPENGL_GLSENIOR3DMESH_H


//#include <glad/glad.h> // holds all OpenGL type declarations

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "GLSeniorShader.h"

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4


struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
    //bone indexes which will influence this vertex
    int m_BoneIDs[MAX_BONE_INFLUENCE];
    //weights from each bone
    float m_Weights[MAX_BONE_INFLUENCE];
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class GLSenior3DMesh {

public:
    // mesh Data
    vector<Vertex>       vertices;
    vector<unsigned int> indices;
    vector<Texture>      textures;
    unsigned int VAO;

    GLSenior3DMesh(vector<Vertex> vertices, vector<unsigned int> indices
             , vector<Texture> textures);

    ~GLSenior3DMesh();

    void Draw(GLSeniorShader &shader);


private:
    // render data
    unsigned int VBO, EBO;

    void setupMesh();

};


#endif //ANDROIDLEARNOPENGL_GLSENIOR3DMESH_H
