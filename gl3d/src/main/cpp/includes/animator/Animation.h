//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/10.
//

#ifndef ANDROIDLEARNOPENGL_ANIMATION_H
#define ANDROIDLEARNOPENGL_ANIMATION_H

#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <functional>
#include "../animator/Bone.h"
#include "../animator/animata.h"
#include "../GL3DMesh.h"
#include "../animator/ModelAnimation.h"

struct AssimpNodeData {
    glm::mat4 transformation;
    std::string name;
    int childrenCount;
    std::vector<AssimpNodeData> children;
};

class Animation {

private:
    float m_Duration;
    int m_TicksPerSecond;
    std::vector<Bone> m_Bones;
    AssimpNodeData m_RootNode;
    std::map<std::string, BoneInfo> m_BoneInfoMap;

public:
    Animation() = default;

    Animation(const std::string &animationPath, ModelAnimation *model);

    ~Animation();

    Bone *FindBone(const std::string &name);

    inline float GetTicksPerSecond();

    inline float GetDuration();

    inline const AssimpNodeData &GetRootNode();

    inline const std::map<std::string, BoneInfo> &GetBoneIDMap();

private:
    void ReadMissingBones(const aiAnimation *animation, ModelAnimation &model);

    void ReadHierarchyData(AssimpNodeData &dest, const aiNode *src);


};


#endif //ANDROIDLEARNOPENGL_ANIMATION_H
