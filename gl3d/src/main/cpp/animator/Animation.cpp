//  Author : wangyongyao https://github.com/wangyongyao1989
// Created by MMM on 2025/2/10.
//

#include "../includes/animator/Animation.h"

Animation::Animation(const string &animationPath, ModelAnimation *model) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(animationPath, aiProcess_Triangulate);
    assert(scene && scene->mRootNode);
    auto animation = scene->mAnimations[0];
    m_Duration = animation->mDuration;
    LOGI("m_Duration ======:%f", m_Duration);

    m_TicksPerSecond = animation->mTicksPerSecond;
    LOGI("m_TicksPerSecond ======:%f", m_TicksPerSecond);

    aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
    globalTransformation = globalTransformation.Inverse();
    ReadHierarchyData(m_RootNode, scene->mRootNode);
    ReadMissingBones(animation, *model);
}

Animation::~Animation() {

}

Bone *Animation::FindBone(const string &name) {
    auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
                             [&](const Bone &Bone) {
                                 return Bone.GetBoneName() == name;
                             }
    );
    if (iter == m_Bones.end()) return nullptr;
    else return &(*iter);

//    LOGE("FindBone name: %s", name.c_str());
//    for (int i = 0; i < m_Bones.size(); ++i) {
//        Bone &bone = m_Bones[i];
//        const string &basicString = bone.GetBoneName();
//        LOGE("m_Bones[%d] name: %s", i, basicString.c_str());
//        if (basicString == name) {
//            return &bone;
//        }
//
//    }
//    return nullptr;

}

float Animation::GetTicksPerSecond() { return m_TicksPerSecond; }

float Animation::GetDuration() { return m_Duration; }

const AssimpNodeData &Animation::GetRootNode() { return m_RootNode; }

const std::map<std::string, BoneInfo> &Animation::GetBoneIDMap() {
    return m_BoneInfoMap;
}

void Animation::ReadMissingBones(const aiAnimation *animation, ModelAnimation &model) {
    int size = animation->mNumChannels;
    //getting m_BoneInfoMap from Model class
    auto &boneInfoMap = model.GetBoneInfoMap();
    //getting the m_BoneCounter from Model class
    int &boneCount = model.GetBoneCount();

    //reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++) {
        auto channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;

        if (boneInfoMap.find(boneName) == boneInfoMap.end()) {
            boneInfoMap[boneName].id = boneCount;
            boneCount++;
        }
        m_Bones.push_back(Bone(channel->mNodeName.data,
                               boneInfoMap[channel->mNodeName.data].id, channel));
    }

    m_BoneInfoMap = boneInfoMap;
}

void Animation::ReadHierarchyData(AssimpNodeData &dest, const aiNode *src) {
    assert(src);

    dest.name = src->mName.data;
    dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++) {
        AssimpNodeData newData;
        ReadHierarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}
