//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2024/10/25.
//

#ifndef ANDROIDLEARNOPENGL_GLSENIOR3DMODEL_H
#define ANDROIDLEARNOPENGL_GLSENIOR3DMODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <image/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GLSenior3DMesh.h>
#include <GLSeniorShader.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class GLSenior3DModel {

private:
    vector<Texture> textures_loaded;
    vector<GLSenior3DMesh> meshes;
    string directory;
    bool gammaCorrection;

    // draws the model, and thus all its meshes



public:
    GLSenior3DModel(string const &path, bool gamma = false);

    void Draw(GLSeniorShader &shader);

private:
    // loads a model with supported ASSIMP extensions from file and stores
    // the resulting meshes in the meshes vector.
    void loadModel(string const &path);

    // processes a node in a recursive fashion. Processes each individual
    // mesh located at the node and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);

    GLSenior3DMesh processMesh(aiMesh *mesh, const aiScene *scene);

    // checks all material textures of a given type and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

    unsigned int TextureFromFile(const char *path, const string &directory, bool gamma);

};


#endif //ANDROIDLEARNOPENGL_GLSENIOR3DMODEL_H
