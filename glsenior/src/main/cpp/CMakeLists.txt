
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

project("glsenior")

set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(${CMAKE_PROJECT_NAME})

set(jnilibs ${CMAKE_SOURCE_DIR}/jniLibs)

set(third-party-libs

)

include_directories(


)

add_library(
        glsenior
        SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        GLSeniorJniCall.cpp
        GLSeniorStdImage.cpp
        senior/GLSeniorFlashLight.cpp
        senior/GLCameraSenior.cpp
        senior/GLSeniorShader.cpp
        senior/GLSeniorDepthTest.cpp
        senior/GLSeniorStencilTest.cpp
        senior/GLSeniorBlending.cpp


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