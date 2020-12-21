#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "Shader.h"
#include "Camera.h"
#define DEBUG_GL_ERRORS
#include "gl_errors.h"

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
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoords = aTexCoords;
}
)";

const std::string g_fs_code = R"(
#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform Light light;
uniform vec3 viewPos;
// 在BasicLighting.cpp的例子中，没有区分不同物体，所有物体对光的反应都是相同的
struct Material 
{
    // vec3 ambient; 移除了环境光的存储，因为环境光颜色在几乎所有情况下都等于漫反射颜色
    sampler2D diffuse;
    sampler2D specular;
    float shininess;    // 影响镜面高光的散射/半径
};
uniform Material material;

out vec4 FragColor;

void main()
{
    // 漫反射
    vec3 n = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(n, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    // 环境光
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // 镜面光
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, n);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
)";

const std::string g_fs_code_light = R"(
#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(lightColor, 1.0);
}
)";

struct MeshFace
{
    std::array<float, 12> vertices;
    glm::vec3 normal; // +x:0 +y:1 +z:2 -x:3 -y:4 -z:5
    std::array<float, 8> uvs;
};

struct MeshFaces
{
    static constexpr MeshFace kFrontFace {
            {1, 1, 1,
             0, 1, 1,
             0, 0, 1,
             1, 0, 1},
            glm::vec3{0, 0, 1},
            {
                1, 1,
                0, 1,
                0, 0,
                1, 0
            }};

    static constexpr MeshFace kLeftFace {
            {0, 1, 1,
             0, 1, 0,
             0, 0, 0,
             0, 0, 1},
            glm::vec3 {-1, 0, 0},
            {
                1, 1,
                0, 1,
                0, 0,
                1, 0
            }};
    static constexpr MeshFace kBackFace = {
            {0, 1, 0,
             1, 1, 0,
             1, 0, 0,
             0, 0, 0},
            glm::vec3{0, 0, -1},
            {
                1, 1,
                0, 1,
                0, 0,
                1, 0
            }};

    static constexpr MeshFace kRightFace = {
            {1, 1, 0,
             1, 1, 1,
             1, 0, 1,
             1, 0, 0},
            glm::vec3{1, 0, 0},
            {
                1, 1,
                0, 1,
                0, 0,
                1, 0
            }};

    static constexpr MeshFace kTopFace = {
            {1, 1, 0,
             0, 1, 0,
             0, 1, 1,
             1, 1, 1},
            glm::vec3{0, 1, 0},
            {
                1, 1,
                0, 1,
                0, 0,
                1, 0
            }};

    static constexpr MeshFace kBottomFace = {
            {0, 0, 0,
             1, 0, 0,
             1, 0, 1,
             0, 0, 1},
            glm::vec3{0, -1, 0},
            {
                1, 1,
                0, 1,
                0, 0,
                1, 0
            }};
};

struct Mesh {
    std::vector<float> vertices;
    std::vector<int> indices;
};

static void add_face(Mesh &mesh, const MeshFace &face) {
    std::size_t index = 0;
    constexpr std::size_t vertex_float_count = 8;
    constexpr std::size_t face_vertex_count = 4;
    for (int i = 0; i < face_vertex_count; ++i) {
        auto x = face.vertices[index++];
        auto y = face.vertices[index++];
        auto z = face.vertices[index++];

        auto u = face.uvs[2*i];
        auto v = face.uvs[2*i+1];

        mesh.vertices.push_back(x);
        mesh.vertices.push_back(y);
        mesh.vertices.push_back(z);
        mesh.vertices.push_back(face.normal.x);
        mesh.vertices.push_back(face.normal.y);
        mesh.vertices.push_back(face.normal.z);
        mesh.vertices.push_back(u);
        mesh.vertices.push_back(v);
    }

    auto index_start = mesh.vertices.size()/vertex_float_count - face_vertex_count;
    mesh.indices.push_back(index_start);
    mesh.indices.push_back(index_start + 1);
    mesh.indices.push_back(index_start + 2);
    mesh.indices.push_back(index_start + 2);
    mesh.indices.push_back(index_start + 3);
    mesh.indices.push_back(index_start);
}

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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lighting Maps", nullptr, nullptr);
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

    // 创建纹理对象
    GLuint diffuseMap;
    glGenTextures(1, &diffuseMap);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载生成纹理
    int width, height, nrChannels;
    unsigned char *data = stbi_load("container2.png", &width, &height, &nrChannels, 0);
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

    // 创建纹理对象
    GLuint specularMap;
    glGenTextures(1, &specularMap);
    glBindTexture(GL_TEXTURE_2D, specularMap);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 加载生成纹理
    data = stbi_load("container2_specular.png", &width, &height, &nrChannels, 0);
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

    Mesh box;
    add_face(box, MeshFaces::kFrontFace);
    add_face(box, MeshFaces::kBackFace);
    add_face(box, MeshFaces::kLeftFace);
    add_face(box, MeshFaces::kRightFace);
    add_face(box, MeshFaces::kTopFace);
    add_face(box, MeshFaces::kBottomFace);

    // 顶点数组对象, 顶点缓冲对象, 索引缓冲对象
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 绑定
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * box.vertices.size(), box.vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * box.indices.size(), box.indices.data(), GL_STATIC_DRAW);
    constexpr GLuint posLocation = 0;
    constexpr GLint posFloatCount = 3;
    constexpr GLuint normalLocation = 1;
    constexpr GLint normalFloatCount = 3;
    constexpr GLuint uvLocation = 2;
    constexpr GLint uvFloatCount = 2;
    constexpr GLint vertexFloatCount = posFloatCount + normalFloatCount + uvFloatCount;
    glVertexAttribPointer(posLocation, posFloatCount, GL_FLOAT, GL_FALSE,  vertexFloatCount * sizeof(float), nullptr);
    glEnableVertexAttribArray(posLocation);
    glVertexAttribPointer(normalLocation, normalFloatCount, GL_FLOAT, GL_FALSE,  vertexFloatCount * sizeof(float), (void*)(posFloatCount*sizeof(float)));
    glEnableVertexAttribArray(normalLocation);
    glVertexAttribPointer(uvLocation, uvFloatCount, GL_FLOAT, GL_FALSE,  vertexFloatCount * sizeof(float), (void*)((posFloatCount+normalFloatCount)*sizeof(float)));
    glEnableVertexAttribArray(uvLocation);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);

    // Shader
    Shader<CreateShaderProgramFromString> shader(g_vs_code, g_fs_code);
    Shader<CreateShaderProgramFromString> shader_light(g_vs_code, g_fs_code_light);

    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(3.0f, 0.0f, 0.0f),
        glm::vec3(6.0f, 0.0f, 0.0f),
        glm::vec3(9.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 3.0f, 0.0f),
        glm::vec3(0.0f, 6.0f, 0.0f),
        glm::vec3(0.0f, 9.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, 6.0f),
        glm::vec3(0.0f, 0.0f, 9.0f),
    };

    glm::vec3 lightPos(3.f, 0.f, 0.f);

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

        // 当我们渲染一个物体时要使用着色器程序
        shader.Use();
        shader.LoadUniform("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
        shader.LoadUniform("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
        shader.LoadUniform("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
        shader.LoadUniform("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        shader.LoadUniform("light.constant", 1.0f);
        shader.LoadUniform("light.linear", 0.09f);
        shader.LoadUniform("light.quadratic", 0.032f);
        shader.LoadUniform("viewPos", camera.pos());
        // 当只有单个VAO时，不用每帧都绑定
        glBindVertexArray(VAO);
        // Transform
        glm::mat4 proj = camera.Perspective(static_cast<float>(SCR_WIDTH/SCR_HEIGHT));
        shader.LoadUniform("proj", proj);
        glm::mat4 view = camera.View();
        shader.LoadUniform("view", view);

        shader.LoadUniform("material.diffuse", 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);

        shader.LoadUniform("material.specular", 1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);

        shader.LoadUniform("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
        shader.LoadUniform("material.shininess", 64.f);
        for(std::size_t i = 0; i < 10; ++i)
        {
            glm::mat4 model = glm::translate(glm::mat4(1.f), cubePositions[i]);
//            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.f), glm::vec3(0.5f, 1.f, 0.f));
            shader.LoadUniform("model", model);
            // 绘制物体
            glCheck(glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr));
        }

        // draw light
        shader_light.Use();
        shader_light.LoadUniform("proj", proj);
        shader_light.LoadUniform("view", view);
        glm::mat4 model = glm::translate(glm::mat4(1.f), lightPos);
        shader_light.LoadUniform("model", model);
        shader_light.LoadUniform("lightColor", glm::vec3(1.0f, 1.f, 1.f)); // 或者使用着色器类设置
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

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
