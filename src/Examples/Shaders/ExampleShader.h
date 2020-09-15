#include "Examples/IExample.h"

#include <memory>

#include <GL/glew.h>

#include "math3d.h"
#include "Shader.h"

struct ExampleShader : public IExample
{
    GLuint VBO, VAO;
    std::string Title() override { return "Shader"; }
    void Init() override
    {
        std::array vertices = {
                Vector3F(0.5f, -0.5f, 0.f), Vector3F(1.f, 0.f, 0.f),
                Vector3F(-0.5f, -0.5f, 0.f), Vector3F(0.f, 1.f, 0.f),
                Vector3F(0.f, 0.5f, 0.f), Vector3F(0.f, 0.f, 1.f),
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertices.size()*sizeof(GLfloat), nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertices.size()*sizeof(GLfloat), (GLvoid*)(3*sizeof(GLfloat)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        shader = std::make_shared<Shader>("vs.glsl", "fs.glsl");
    }
    void Render() override
    {
        shader->Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    std::shared_ptr<Shader> shader;
};