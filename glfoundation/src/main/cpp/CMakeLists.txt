
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

project("glfoundation")
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(${CMAKE_PROJECT_NAME})
add_library(
        glfoundation
        SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        native-lib.cpp
        OpenglesFoundation.cpp
        OpenGLSingleShaderBase.cpp
        OpenglesTexture.cpp
        OpenGLStdImage.cpp
        Opengles3D.cpp
        OpenglesCube3D.cpp
        OpenglesMultiCube3D.cpp
        OpenglesCamera3D.cpp
        Camera3D.cpp
        OpenglesLightCube.cpp
        OpenGLShader.cpp
        OpenglesDiffuseReflectionLight.cpp
        OpenglesSpecularLight.cpp
        OpenglesMaterial.cpp
        OpenglesDiffuseMap.cpp
        OpenglesSpecularMap.cpp
        OpenglesDirectionLight.cpp
        OpenglesAttenuationLight.cpp
        OpenglesFlashLight.cpp
        OpenglesSpotLight.cpp
        OpenglesMultiLight.cpp

)

target_link_libraries(
        glfoundation
        android
#        jnigraphics
        EGL
        GLESv3
        OpenSLES
        log)

target_include_directories(
        glfoundation
        PRIVATE
        ${distribution_DIR}/includes)