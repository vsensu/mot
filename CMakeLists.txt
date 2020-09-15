cmake_minimum_required(VERSION 3.16)
project(mot)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(deps/glfw-3.3.2)

# .h
include_directories(
        src
        deps/glad/include
        deps/glfw-3.3.2/include
)

# lib folder
link_directories(
        ${CMAKE_CURRENT_BINARY_DIR}/deps/glfw-3.3.2/src
)

# 将当前目录的所有源文件添加进变量
#aux_source_directory(. DIRS_SRCS)

add_executable(mot src/main.cpp src/Examples/Shaders/Shader.h src/math3d.h src/Examples/Shaders/ExampleShader.h
        src/Examples/IExample.h src/Examples/Point/ExampleRenderPoint.h src/Examples/Triangle/ExampleRenderTriangle.h
        src/Examples/Shaders/ExampleUniformVariables.h src/Examples/Shaders/ExampleTranslationTransformation.h
        deps/glad/src/glad.c)

# lib
target_link_libraries(mot
        glfw3
        )

# post build
add_custom_command(TARGET mot
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/vs.glsl ${CMAKE_CURRENT_BINARY_DIR}/vs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/fs.glsl ${CMAKE_CURRENT_BINARY_DIR}/fs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/uvs.glsl ${CMAKE_CURRENT_BINARY_DIR}/uvs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/ufs.glsl ${CMAKE_CURRENT_BINARY_DIR}/ufs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/wvs.glsl ${CMAKE_CURRENT_BINARY_DIR}/wvs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/wfs.glsl ${CMAKE_CURRENT_BINARY_DIR}/wfs.glsl
        )