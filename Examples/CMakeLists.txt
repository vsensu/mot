
# .h
include_directories(
        ${PROJECT_SOURCE_DIR}/deps/glad/include
        ${PROJECT_SOURCE_DIR}/deps/stb_image
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
add_executable(Colors WIN32 Lighting/Colors/Colors.cpp GetStarted/Shaders/Shader.h GetStarted/Camera/Camera.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)
add_executable(BasicLighting WIN32 Lighting/Colors/BasicLighting.cpp Lighting/Colors/gl_errors.h Lighting/Colors/gl_errors.cpp GetStarted/Shaders/Shader.h GetStarted/Camera/Camera.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)
add_executable(Materials WIN32 Lighting/Colors/Materials.cpp Lighting/Colors/gl_errors.h Lighting/Colors/gl_errors.cpp GetStarted/Shaders/Shader.h GetStarted/Camera/Camera.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)
add_executable(LightingMaps WIN32 Lighting/Colors/LightingMaps.cpp Lighting/Colors/gl_errors.h Lighting/Colors/gl_errors.cpp GetStarted/Shaders/Shader.h GetStarted/Camera/Camera.h
        ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c ${PROJECT_SOURCE_DIR}/deps/stb_image/stb_image.cpp)

## lib
target_link_libraries(HelloWindow
        ${CONAN_LIBS}
        )
target_link_libraries(HelloTriangle
        ${CONAN_LIBS}
        )
target_link_libraries(HelloRectangle
        ${CONAN_LIBS}
        )
target_link_libraries(ShaderInOut
        ${CONAN_LIBS}
        )
target_link_libraries(ShaderUniform
        ${CONAN_LIBS}
        )
target_link_libraries(ShaderMoreAttributes
        ${CONAN_LIBS}
        )
target_link_libraries(ShaderFile
        ${CONAN_LIBS}
        )
target_link_libraries(HelloTexture
        ${CONAN_LIBS}
        )
target_link_libraries(TexturesCombined
        ${CONAN_LIBS}
        )
target_link_libraries(HelloTransform
        ${CONAN_LIBS}
        )
target_link_libraries(Hello3D
        ${CONAN_LIBS}
        )
target_link_libraries(Cube
        ${CONAN_LIBS}
        )
target_link_libraries(HelloCamera
        ${CONAN_LIBS}
        )
target_link_libraries(GodCamera
        ${CONAN_LIBS}
        )
target_link_libraries(Colors
        ${CONAN_LIBS}
        )
target_link_libraries(BasicLighting
        ${CONAN_LIBS}
        )
target_link_libraries(Materials
        ${CONAN_LIBS}
        )
target_link_libraries(LightingMaps
        ${CONAN_LIBS}
        )

set(GUI_ONLY_BINARIES HelloWindow HelloTriangle HelloRectangle ShaderInOut ShaderUniform ShaderMoreAttributes ShaderFile
        HelloTexture TexturesCombined HelloTransform Hello3D Cube HelloCamera GodCamera Colors BasicLighting Materials LightingMaps)
if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${GUI_ONLY_BINARIES} PROPERTIES
            LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()

# post build
add_custom_command(TARGET ShaderFile
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Shaders/vs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/vs.glsl
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Shaders/fs.glsl ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/fs.glsl
        )
add_custom_command(TARGET HelloTexture
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/container.jpg
        )
add_custom_command(TARGET TexturesCombined
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/awesomeface.png
        )
add_custom_command(TARGET HelloTransform
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/awesomeface.png
        )
add_custom_command(TARGET Hello3D
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/awesomeface.png
        )
add_custom_command(TARGET Cube
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/awesomeface.png
        )
add_custom_command(TARGET HelloCamera
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/awesomeface.png
        )
add_custom_command(TARGET GodCamera
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/container.jpg ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/container.jpg
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/GetStarted/Textures/awesomeface.png ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/awesomeface.png
        )
add_custom_command(TARGET LightingMaps
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/Lighting/Colors/container2.png ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/container2.png
        )
