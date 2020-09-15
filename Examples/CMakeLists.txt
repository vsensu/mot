
# .h
include_directories(
        ${PROJECT_SOURCE_DIR}/deps/glad/include
        ${PROJECT_SOURCE_DIR}/deps/glfw-3.3.2/include
)

# lib folder
link_directories(
        ${PROJECT_BINARY_DIR}/deps/glfw-3.3.2/src
)

add_executable(HelloWindow WIN32 GetStarted/HelloWindow/HelloWindow.cpp ${PROJECT_SOURCE_DIR}/deps/glad/src/glad.c)

## lib
target_link_libraries(HelloWindow
        glfw3
        )

set(GUI_ONLY_BINARIES HelloWindow)
if (MSVC)
    # Tell MSVC to use main instead of WinMain for Windows subsystem executables
    set_target_properties(${GUI_ONLY_BINARIES} PROPERTIES
            LINK_FLAGS "/ENTRY:mainCRTStartup")
endif()
