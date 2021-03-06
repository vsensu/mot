add_requires("glfw 3.3.2", {alias = "glfw"})
add_requires("glm 0.9.9+8", {alias = "glm"})

add_rules("mode.debug", "mode.release")

target("HelloWindow")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/HelloWindow/HelloWindow.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
        add_links("user32", "gdi32", "shell32")
    end

target("HelloTriangle")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/HelloTriangle/HelloTriangle.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
        add_links("user32", "gdi32", "shell32")
    end

target("HelloRectangle")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/HelloTriangle/HelloRectangle.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
        add_links("user32", "gdi32", "shell32")
    end


target("Shader_InOut")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/Shaders/Shader_InOut.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
        add_links("user32", "gdi32", "shell32")
    end

target("Shader_Uniform")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/Shaders/Shader_Uniform.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
        add_links("user32", "gdi32", "shell32")
    end

target("Shader_MoreAttributes")
    set_kind("binary")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("src/GetStarted/Shaders/Shader_MoreAttributes.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
        add_links("user32", "gdi32", "shell32")
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
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        fs = path.join(target:targetdir(), "fs.glsl")
        if not os.exists(fs) then
            os.cp("src/GetStarted/Shaders/fs.glsl", fs)
        end
        vs = path.join(target:targetdir(), "vs.glsl")
        if not os.exists(vs) then
            os.cp("src/GetStarted/Shaders/vs.glsl", vs)
        end
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
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container.jpg")
        if not os.exists(container) then
            os.cp("res/img/container.jpg", container)
        end
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
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container.jpg")
        if not os.exists(container) then
            os.cp("res/img/container.jpg", container)
        end
        awesomeface = path.join(target:targetdir(), "awesomeface.png")
        if not os.exists(awesomeface) then
            os.cp("res/img/awesomeface.png", awesomeface)
        end
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
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container.jpg")
        if not os.exists(container) then
            os.cp("res/img/container.jpg", container)
        end
        awesomeface = path.join(target:targetdir(), "awesomeface.png")
        if not os.exists(awesomeface) then
            os.cp("res/img/awesomeface.png", awesomeface)
        end
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
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container.jpg")
        if not os.exists(container) then 
            os.cp("res/img/container.jpg", container)
        end
        awesomeface = path.join(target:targetdir(), "awesomeface.png")
        if not os.exists(awesomeface) then
            os.cp("res/img/awesomeface.png", awesomeface)
        end
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
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container.jpg")
        if not os.exists(container) then
            os.cp("res/img/container.jpg", container)
        end
        awesomeface = path.join(target:targetdir(), "awesomeface.png")
        if not os.exists(awesomeface) then
            os.cp("res/img/awesomeface.png", awesomeface)
        end
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
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container.jpg")
        if not os.exists(container) then
            os.cp("res/img/container.jpg", container)
        end
        awesomeface = path.join(target:targetdir(), "awesomeface.png")
        if not os.exists(awesomeface) then
            os.cp("res/img/awesomeface.png", awesomeface)
        end
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
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container.jpg")
        if not os.exists(container) then
            os.cp("res/img/container.jpg", container)
        end
        awesomeface = path.join(target:targetdir(), "awesomeface.png")
        if not os.exists(awesomeface) then
            os.cp("res/img/awesomeface.png", awesomeface)
        end
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
        add_links("user32", "gdi32", "shell32")
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
        add_links("user32", "gdi32", "shell32")
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
        add_links("user32", "gdi32", "shell32")
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
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container2.png")
        if not os.exists(container) then
            os.cp("res/img/container2.png", container)
        end
        specular = path.join(target:targetdir(), "container2_specular.png")
        if not os.exists(specular) then
            os.cp("res/img/container2_specular.png", specular)
        end
    end)


target("DirectionalLight")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/Lighting/LightCasters/DirectionalLight.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container2.png")
        if not os.exists(container) then
            os.cp("res/img/container2.png", container)
        end
        specular = path.join(target:targetdir(), "container2_specular.png")
        if not os.exists(specular) then
            os.cp("res/img/container2_specular.png", specular)
        end
    end)

target("PointLight")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/Lighting/LightCasters/PointLight.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container2.png")
        if not os.exists(container) then
            os.cp("res/img/container2.png", container)
        end
        specular = path.join(target:targetdir(), "container2_specular.png")
        if not os.exists(specular) then
            os.cp("res/img/container2_specular.png", specular)
        end
    end)

target("FlashLight")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/Lighting/LightCasters/FlashLight.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container2.png")
        if not os.exists(container) then
            os.cp("res/img/container2.png", container)
        end
        specular = path.join(target:targetdir(), "container2_specular.png")
        if not os.exists(specular) then
            os.cp("res/img/container2_specular.png", specular)
        end
    end)

target("MultipleLights")
    set_kind("binary")
    set_languages("c++20")
    add_includedirs("$(projectdir)/deps/glad/include")
    add_includedirs("$(projectdir)/deps/stb_image")
    add_includedirs("src")
    add_files("$(projectdir)/deps/glad/src/*.c")
    add_files("$(projectdir)/deps/stb_image/*.cpp")
    add_files("src/Lighting/MultipleLights/MultipleLights.cpp")
    add_packages("glfw", "glm")
    if is_plat("windows") then 
        add_ldflags("-subsystem:windows", "-entry:mainCRTStartup", {force = true}) 
        add_links("user32", "gdi32", "shell32")
    end
    after_build(function (target)
        container = path.join(target:targetdir(), "container2.png")
        if not os.exists(container) then
            os.cp("res/img/container2.png", container)
        end
        specular = path.join(target:targetdir(), "container2_specular.png")
        if not os.exists(specular) then
            os.cp("res/img/container2_specular.png", specular)
        end
    end)
