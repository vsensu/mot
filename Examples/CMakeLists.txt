
# .h
include_directories(
        ${PROJECT_SOURCE_DIR}/deps/glad/include
        ${PROJECT_SOURCE_DIR}/deps/glfw-3.3.2/include
        ${PROJECT_SOURCE_DIR}/deps/stb_image
        ${PROJECT_SOURCE_DIR}/deps/glm-0.9.9.8
)

# lib folder
link_directories(
        ${PROJECT_BINARY_DIR}/deps/glfw-3.3.2/src
)

# executable
add_executable(HelloWindow WIN32 GetStarted/HelloWindow/HelloWindow.cpp ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c)
add_executable(HelloTriangle WIN32 GetStarted/HelloTriangle/HelloTriangle.cpp ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c)
add_executable(HelloRectangle WIN32 GetStarted/HelloTriangle/HelloRectangle.cpp ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c)
add_executable(ShaderInOut WIN32 GetStarted/Shaders/Shader_InOut.cpp ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c)
add_executable(ShaderUniform WIN32 GetStarted/Shaders/Shader_Uniform.cpp ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c)
add_executable(ShaderMoreAttributes WIN32 GetStarted/Shaders/Shader_MoreAttributes.cpp ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c)
add_executable(ShaderFile WIN32 GetStarted/Shaders/Shader_File.cpp GetStarted/Shaders/Shader.h ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c)
add_executable(HelloTexture WIN32 GetStarted/Textures/HelloTexture.cpp GetStarted/Shaders/Shader.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)
add_executable(TexturesCombined WIN32 GetStarted/Textures/TexturesCombined.cpp GetStarted/Shaders/Shader.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)
add_executable(HelloTransform WIN32 GetStarted/Transform/HelloTransform.cpp GetStarted/Shaders/Shader.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)
add_executable(Hello3D WIN32 GetStarted/CoordinateSystem/Hello3D.cpp GetStarted/Shaders/Shader.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)
add_executable(Cube WIN32 GetStarted/CoordinateSystem/Cube.cpp GetStarted/Shaders/Shader.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)
add_executable(HelloCamera WIN32 GetStarted/Camera/HelloCamera.cpp GetStarted/Shaders/Shader.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)
add_executable(GodCamera WIN32 GetStarted/Camera/GodCamera.cpp GetStarted/Shaders/Shader.h GetStarted/Camera/Camera.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)

## lib
target_link_libraries(HelloWindow
        glfw3
        )
target_link_libraries(HelloTriangle
        glfw3
        )
target_link_libraries(HelloRectangle
        glfw3
        )
target_link_libraries(ShaderInOut
        glfw3
        )
target_link_libraries(ShaderUniform
        glfw3
        )
target_link_libraries(ShaderMoreAttributes
        glfw3
        )
target_link_libraries(ShaderFile
        glfw3
        )
target_link_libraries(HelloTexture
        glfw3
        )
target_link_libraries(TexturesCombined
        glfw3
        )
target_link_libraries(HelloTransform
        glfw3
        )
target_link_libraries(Hello3D
        glfw3
        )
target_link_libraries(Cube
        glfw3
        )
target_link_libraries(HelloCamera
        glfw3
        )
target_link_libraries(GodCamera
        glfw3
        )

set(GUI_ONLY_BINARIES HelloWindow HelloTriangle HelloRectangle ShaderInOut ShaderUniform ShaderMoreAttributes ShaderFile
        HelloTexture TexturesCombined HelloTransform Hello3D Cube HelloCamera GodCamera)
if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${GUI_ONLY_BINARIES} PROPERTIES
            LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

# post build
add_custom_command(TARGET ShaderFile
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Shaders/vs.glsl ${CMAKE_CURRENT_BINARY_DIR}/vs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Shaders/fs.glsl ${CMAKE_CURRENT_BINARY_DIR}/fs.glsl
        )
add_custom_command(TARGET HelloTexture
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg
        )
add_custom_command(TARGET TexturesCombined
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png
        )
add_custom_command(TARGET HelloTransform
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png
        )
add_custom_command(TARGET Hello3D
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png
        )
add_custom_command(TARGET Cube
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png
        )
add_custom_command(TARGET HelloCamera
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png
        )
add_custom_command(TARGET GodCamera
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_CURRENT_BINARY_DIR}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_CURRENT_BINARY_DIR}/awesomeface.png
        )
