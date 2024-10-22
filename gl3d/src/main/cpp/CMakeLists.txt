
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")

project("gl3d")
set(distribution_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(${CMAKE_PROJECT_NAME})
add_library(
        gl3d
        SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        GL3DJniCall.cpp
        

)

target_link_libraries(
        gl3d
        log)

target_include_directories(
        gl3d
        PRIVATE
        ${distribution_DIR}/includes)