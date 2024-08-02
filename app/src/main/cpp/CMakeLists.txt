
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

project("androidlearnopengl")
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${CMAKE_PROJECT_NAME}
        SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        native-lib.cpp
        OpenglesFoundation.cpp
        OpenGLBase.cpp
        OpenglesTexture.cpp
        OpenGLStdImage.cpp
        Opengles3D.cpp
        OpenglesCube3D.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
#        jnigraphics
        EGL
        GLESv3
        OpenSLES
        log)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${distribution_DIR}/includes)