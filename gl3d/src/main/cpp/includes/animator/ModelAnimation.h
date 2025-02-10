//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/10.
//

#ifndef ANDROIDLEARNOPENGL_MODELANIMATION_H
#define ANDROIDLEARNOPENGL_MODELANIMATION_H

//#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../image/stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../GL3DMesh.h"
#include "../GL3DShader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include "../animator/AssimpGLMHelpers.h"
#include "../animator/animata.h"


class ModelAnimation {

private:
    std::map<string, BoneInfo> m_BoneInfoMap;
    int m_BoneCounter = 0;

public:
    // model data
    // stores all the textures loaded so far,
    // optimization to make sure textures aren't loaded more than once.
    vector<Texture> textures_loaded;

    vector<GL3DMesh> meshes;
    string directory;
    bool gammaCorrection;

public:
    // constructor, expects a filepath to a 3D model.
    ModelAnimation(string const &path, bool gamma = false);

    // draws the model, and thus all its meshes
    void Draw(GL3DShader &shader);

    std::map<string, BoneInfo>& GetBoneInfoMap();

    int& GetBoneCount();

private:
    // loads a model with supported ASSIMP extensions from
    // file and stores the resulting meshes in the meshes vector.
    void loadModel(string const &path);

    // processes a node in a recursive fashion.
    // Processes each individual mesh located at the node
    // and repeats this process on its children nodes (if any).
    void processNode(aiNode *node, const aiScene *scene);

    void SetVertexBoneDataToDefault(Vertex &vertex);

    GL3DMesh processMesh(aiMesh *mesh, const aiScene *scene);

    void SetVertexBoneData(Vertex &vertex, int boneID, float weight);

    void ExtractBoneWeightForVertices(std::vector<Vertex> &vertices,
                                      aiMesh *mesh,
                                      const aiScene *scene);

    unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

    // checks all material textures of a given type
    // and loads the textures if they're not loaded yet.
    // the required info is returned as a Texture struct.
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);


};


#endif //ANDROIDLEARNOPENGL_MODELANIMATION_H
