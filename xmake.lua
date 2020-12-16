add_requires("glfw 3.3.2")
add_requires("glm 0.9.9+8")

target("HelloWindow")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/HelloWindow/HelloWindow.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end

target("HelloTriangle")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/HelloTriangle/HelloTriangle.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end

target("HelloRectangle")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/HelloTriangle/HelloRectangle.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end


target("Shader_InOut")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/Shaders/Shader_InOut.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end

target("Shader_Uniform")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/Shaders/Shader_Uniform.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end

target("Shader_MoreAttributes")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/Shaders/Shader_MoreAttributes.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end

target("Shader_File")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/Shaders/Shader_File.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end
    after_build(function (target)
        os.cp("src/GetStarted/Shaders/fs.glsl", path.join(target:targetdir(), "fs.glsl"))
        os.cp("src/GetStarted/Shaders/vs.glsl", path.join(target:targetdir(), "vs.glsl"))
    end)


target("HelloTexture")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/GetStarted/Textures/HelloTexture.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end
    after_build(function (target)
        os.cp("res/img/container.jpg", path.join(target:targetdir(), "container.jpg"))
    end)

target("TexturesCombined")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/GetStarted/Textures/TexturesCombined.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end
    after_build(function (target)
        os.cp("res/img/container.jpg", path.join(target:targetdir(), "container.jpg"))
        os.cp("res/img/awesomeface.png", path.join(target:targetdir(), "awesomeface.png"))
    end)


target("HelloTransform")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/GetStarted/Transform/HelloTransform.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end
    after_build(function (target)
        os.cp("res/img/container.jpg", path.join(target:targetdir(), "container.jpg"))
        os.cp("res/img/awesomeface.png", path.join(target:targetdir(), "awesomeface.png"))
    end)
    

target("Hello3D")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/GetStarted/CoordinateSystem/Hello3D.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end
    after_build(function (target)
        os.cp("res/img/container.jpg", path.join(target:targetdir(), "container.jpg"))
        os.cp("res/img/awesomeface.png", path.join(target:targetdir(), "awesomeface.png"))
    end)

target("Cube")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/GetStarted/CoordinateSystem/Cube.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end
    after_build(function (target)
        os.cp("res/img/container.jpg", path.join(target:targetdir(), "container.jpg"))
        os.cp("res/img/awesomeface.png", path.join(target:targetdir(), "awesomeface.png"))
    end)


target("HelloCamera")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/GetStarted/Camera/HelloCamera.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end
    after_build(function (target)
        os.cp("res/img/container.jpg", path.join(target:targetdir(), "container.jpg"))
        os.cp("res/img/awesomeface.png", path.join(target:targetdir(), "awesomeface.png"))
    end)

target("GodCamera")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/GetStarted/Camera/GodCamera.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end
    after_build(function (target)
        os.cp("res/img/container.jpg", path.join(target:targetdir(), "container.jpg"))
        os.cp("res/img/awesomeface.png", path.join(target:targetdir(), "awesomeface.png"))
    end)


target("Colors")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/Lighting/Colors/Colors.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end

target("BasicLighting")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/Lighting/BasicLighting/BasicLighting.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end

target("Materials")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/Lighting/Materials/Materials.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end

target("LightingMaps")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/Lighting/LightingMaps/LightingMaps.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
    end
    after_build(function (target)
        os.cp("res/img/container2.png", path.join(target:targetdir(), "container2.png"))
    end)
