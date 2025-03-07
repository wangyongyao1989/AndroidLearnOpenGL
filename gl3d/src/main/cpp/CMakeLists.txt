
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

project("gl3dshow")

set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(${CMAKE_PROJECT_NAME})

set(jnilibs ${CMAKE_SOURCE_DIR}/jniLibs)

set(third-party-libs
        ${jnilibs}/${ANDROID_ABI}/libassimp.so
        ${jnilibs}/${ANDROID_ABI}/libfreetype.a
)

include_directories(
        includes/freetype_2_9_1

)

add_library(
        gl3dshow
        SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        GL3DJniCall.cpp
        gl3dshow/GL3DFlashLight.cpp

        gl3dshow/GL3DStdImage.cpp
        gl3dshow/GLCamera3D.cpp
        gl3dshow/GL3DShow.cpp
        gl3dshow/GL3DShader.cpp
        gl3dshow/GL3DMesh.cpp
        gl3dshow/GL3DModel.cpp
        gl3dshow/GLDrawText.cpp
        gl3dshow/GL3DAnimationShow.cpp

        animator/Animation.cpp
        animator/Animator.cpp
        animator/Bone.cpp
        animator/AssimpGLMHelpers.cpp
        animator/ModelAnimation.cpp


)

target_link_libraries(
        gl3dshow
        EGL
        GLESv3
        OpenSLES
        log
        android
        ${third-party-libs}

)

target_include_directories(
        gl3dshow
        PRIVATE
        ${distribution_DIR}/includes)