cmake_minimum_required(VERSION 3.16)
project(mot)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        src
        deps/FreeGLUT-3.2.1/include
        deps/glew-2.1.0/include
)


link_directories(
        deps/FreeGLUT-3.2.1/lib
        deps/glew-2.1.0/lib
)

# 将当前目录的所有源文件添加进变量
#aux_source_directory(. DIRS_SRCS)

#add_executable(mot src/main.cpp ${DIRS_SRCS} src/Examples/Shaders/Shader.h src/math3d.h)
add_executable(mot src/main.cpp src/Examples/Shaders/Shader.h src/math3d.h src/Examples/Shaders/ExampleShader.h
        src/Examples/IExample.h src/Examples/Point/ExampleRenderPoint.h src/Examples/Triangle/ExampleRenderTriangle.h src/Examples/Shaders/ExampleUniformVariables.h src/Examples/Shaders/ExampleTranslationTransformation.h)

target_link_libraries(mot
        freeglutd
        glew32
        )

add_custom_command(TARGET mot
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/FreeGLUT-3.2.1/dll/freeglutd.dll ${CMAKE_CURRENT_BINARY_DIR}/freeglutd.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/FreeGLUT-3.2.1/dll/freeglut.dll ${CMAKE_CURRENT_BINARY_DIR}/freeglut.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/deps/glew-2.1.0/dll/glew32.dll ${CMAKE_CURRENT_BINARY_DIR}/glew32.dll
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/vs.glsl ${CMAKE_CURRENT_BINARY_DIR}/vs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/fs.glsl ${CMAKE_CURRENT_BINARY_DIR}/fs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/uvs.glsl ${CMAKE_CURRENT_BINARY_DIR}/uvs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/ufs.glsl ${CMAKE_CURRENT_BINARY_DIR}/ufs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/wvs.glsl ${CMAKE_CURRENT_BINARY_DIR}/wvs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/Examples/Shaders/wfs.glsl ${CMAKE_CURRENT_BINARY_DIR}/wfs.glsl
        )