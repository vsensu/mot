#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Shaders
    Shader<CreateShaderProgramFromFile> shader("vs.glsl", "fs.glsl");

    // 顶点数据
    float vertices[] = {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[] = { // 注意索引从0开始!
            0, 1, 3, // 第一个三角形
            1, 2, 3  // 第二个三角形
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
    constexpr GLint vertexFloatCount = posFloatCount;
    // 定义OpenGL如何理解该顶点数据
    glVertexAttribPointer(posLocation, posFloatCount, GL_FLOAT, GL_FALSE,  vertexFloatCount * sizeof(float), nullptr);
    // 启用顶点属性 顶点属性默认是禁用的
    glEnableVertexAttribArray(posLocation);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // 主循环
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // 输入处理
        // -----
        processInput(window);

        // 渲染
        glClear(GL_COLOR_BUFFER_BIT);

        // 当我们渲染一个物体时要使用着色器程序
        shader.Use();

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue)/2) + 0.5f;
        shader.SetUniform("ourColor", 0.f, greenValue, 0.f, 1.f);

        // 当只有单个VAO时，不用每帧都绑定
        glBindVertexArray(VAO);
        // 绘制物体
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
