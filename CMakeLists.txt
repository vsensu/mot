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
        src/Examples/IExample.h src/Examples/Point/ExampleRenderPoint.h src/Examples/Triangle/ExampleRenderTriangle.h)

target_link_libraries(mot
        freeglutd
        glew32
        )

#configure_file(deps/glew/dll/glew32.dll ${RUNTIME_OUTPUT_DIRECTORY}/glew32.dll COPYONLY)
file(COPY deps/FreeGLUT-3.2.1/dll/freeglutd.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY deps/FreeGLUT-3.2.1/dll/freeglut.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY deps/glew-2.1.0/dll/glew32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/Examples/Shaders/vs.glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/Examples/Shaders/fs.glsl DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
