//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/10.
//

#ifndef ANDROIDLEARNOPENGL_ASSIMPGLMHELPERS_H
#define ANDROIDLEARNOPENGL_ASSIMPGLMHELPERS_H

#include<assimp/quaternion.h>
#include<assimp/vector3.h>
#include<assimp/matrix4x4.h>
#include<glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>

class AssimpGLMHelpers {

public:
    static inline glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4 &from);

    static inline glm::vec3 GetGLMVec(const aiVector3D &vec);

    static inline glm::quat GetGLMQuat(const aiQuaternion &pOrientation);
};


#endif //ANDROIDLEARNOPENGL_ASSIMPGLMHELPERS_H
