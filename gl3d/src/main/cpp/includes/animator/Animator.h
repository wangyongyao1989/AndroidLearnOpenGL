//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/10.
//

#ifndef ANDROIDLEARNOPENGL_ANIMATOR_H
#define ANDROIDLEARNOPENGL_ANIMATOR_H

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include "../animator/Animation.h"
#include "../animator/Bone.h"


class Animator {

private:
    std::vector<glm::mat4> m_FinalBoneMatrices;
    Animation *m_CurrentAnimation;
    float m_CurrentTime;
    float m_DeltaTime;

public:
    Animator(Animation *animation);

    void UpdateAnimation(float dt);

    void PlayAnimation(Animation *pAnimation);

    void CalculateBoneTransform(const AssimpNodeData *node,
                                glm::mat4 parentTransform);

    std::vector<glm::mat4> GetFinalBoneMatrices();

};


#endif //ANDROIDLEARNOPENGL_ANIMATOR_H
