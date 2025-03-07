
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

project("glsl")

set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(${CMAKE_PROJECT_NAME})

set(jnilibs ${CMAKE_SOURCE_DIR}/jniLibs)



include_directories(

)

add_library(
        glsl
        SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        GLSLJniCall.cpp
        shader/GLSLStdImage.cpp
        shader/GLSLCamera.cpp
        shader/GLSLShader.cpp

        shader/GLShapingFunction.cpp
        shader/GLColorFunction.cpp
        shader/GLShapeFunction.cpp
        shader/GLMatricesFunction.cpp
        shader/GLSLPatternsFunction.cpp


)

target_link_libraries(
        glsl
        EGL
        GLESv3
        OpenSLES
        log
        android

)

target_include_directories(
        glsl
        PRIVATE
        ${distribution_DIR}/includes)