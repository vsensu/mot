#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

#include "../Shaders/Shader.h"
#include "Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float deltaTime = 0.0f; // 当前帧与上一帧的时间差
float lastFrame = 0.0f; // 上一帧的时间

Camera camera;

const std::string g_vs_code = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = vec2(aTexCoord.x, 1-aTexCoord.y);
}
)";

const std::string g_fs_code = R"(
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2) * vec4(ourColor, 1.0);
}
)";

int main()
{
    // glfw: 初始化glfw并设置openGL版本，设置只使用Core
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // OpenGL的核心模式**要求**我们使用VAO，所以它知道该如何处理我们的顶点输入。如果我们绑定VAO失败，OpenGL会拒绝绘制任何东西。
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw 创建窗口
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello Rectangle", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // clear时填充色
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    // 线框模式
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    // Shader
    Shader<CreateShaderProgramFromString> shader(g_vs_code, g_fs_code);

    // 创建纹理对象
    GLuint texture1;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载生成纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0 /*mipmap*/, GL_RGB, width, height, 0/*legacy*/, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // 第二个纹理
    GLuint texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载生成纹理
    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0 /*mipmap*/, GL_RGBA, width, height, 0/*legacy*/, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // 顶点数据
    float vertices[] = {
            //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
            0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
            0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,    // 左上

            0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
            0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    unsigned int indices[] = { // 注意索引从0开始!
            0, 1, 3, // 第一个三角形
            1, 2, 3,  // 第二个三角形

            4, 5, 7,
            5, 6, 7,

            3, 2, 7,
            2, 6, 7,

            4, 5, 0,
            5, 1, 0,

            4, 0, 7,
            0, 3, 7,

            5, 1, 6,
            1, 2, 6
    };

    // 顶点数组对象, 顶点缓冲对象, 索引缓冲对象
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 绑定
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    constexpr GLuint posLocation = 0;
    constexpr GLint posFloatCount = 3;
    constexpr GLint colorFloatCount = 3;
    constexpr GLint coordFloatCount = 2;
    constexpr GLint vertexFloatCount = posFloatCount + colorFloatCount + coordFloatCount;
    glVertexAttribPointer(posLocation, posFloatCount, GL_FLOAT, GL_FALSE,  vertexFloatCount * sizeof(float), nullptr);
    glEnableVertexAttribArray(posLocation);
    constexpr GLuint colorLocation = 1;
    glVertexAttribPointer(colorLocation, colorFloatCount, GL_FLOAT, GL_FALSE, vertexFloatCount * sizeof(float), (void*)(posFloatCount*sizeof(float)));
    glEnableVertexAttribArray(colorLocation);
    constexpr GLuint coordLocation = 2;
    glVertexAttribPointer(coordLocation, coordFloatCount, GL_FLOAT, GL_FALSE, vertexFloatCount * sizeof(float), (void*)((posFloatCount+colorFloatCount)*sizeof(float)));
    glEnableVertexAttribArray(coordLocation);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    shader.Use(); // 不要忘记在设置uniform变量之前激活着色器程序！
    // 将texture1名称 关联到 GL_TEXTURE0 纹理单元
    glUniform1i(glGetUniformLocation(shader.shaderProgram, "texture1"), 0); // 手动设置
    // 将texture2名称 关联到 GL_TEXTURE1 纹理单元
    shader.SetUniform("texture2", 1); // 或者使用着色器类设置

    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // 主循环
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // 输入处理
        // -----
        processInput(window);

        // 渲染
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 绑定纹理
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        // 当我们渲染一个物体时要使用着色器程序
        shader.Use();
        // 当只有单个VAO时，不用每帧都绑定
        glBindVertexArray(VAO);
        // Transform
        glm::mat4 proj = camera.Perspective(static_cast<float>(width/height));
        shader.SetUniform("proj", glm::value_ptr(proj));
        glm::mat4 view = camera.View();
        shader.SetUniform("view", glm::value_ptr(view));
        for(std::size_t i = 0; i < 10; ++i)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.f), cubePositions[i]);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.f), glm::vec3(0.5f, 1.f, 0.f));
            shader.SetUniform("model", glm::value_ptr(model));
            // 绘制物体
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
        }

        // glfw: 交换双缓冲
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        // 事件
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.MoveForward(deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.MoveBackward(deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.MoveLeft(deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.MoveRight(deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    camera.MouseCallback(window, xpos, ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.Zoom(yoffset);
}
