
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

project("glsenior")

set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(${CMAKE_PROJECT_NAME})

set(jnilibs ${CMAKE_SOURCE_DIR}/jniLibs)

set(third-party-libs
        ${jnilibs}/${ANDROID_ABI}/libassimp.so
)

include_directories(


)

add_library(
        glsenior
        SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        GLSeniorJniCall.cpp
        GLSeniorStdImage.cpp
        senior/GLCameraSenior.cpp
        senior/GLSeniorShader.cpp
        senior/GLSeniorDepthTest.cpp
        senior/GLSeniorStencilTest.cpp
        senior/GLSeniorBlendingDiscard.cpp
        senior/GLSeniorBlendingSort.cpp
        senior/GLSeniorFBO.cpp
        senior/GLFBOPostProcessing.cpp
        senior/GLSeniorCubeMap.cpp
        senior/GLSeniorReflection.cpp
        senior/GLSeniorUniform.cpp
        senior/GLSeniorGeometry.cpp
        senior/GLSeniorInstance.cpp

        3d/GLSenior3DMesh.cpp
        3d/GLSenior3DModel.cpp
        3d/GLSenior3DShow.cpp


)

target_link_libraries(
        glsenior
        EGL
        GLESv3
        OpenSLES
        log
        android
        ${third-party-libs}

)

target_include_directories(
        glsenior
        PRIVATE
        ${distribution_DIR}/includes)