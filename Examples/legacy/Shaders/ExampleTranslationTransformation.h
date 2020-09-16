#ifndef MOT_EXAMPLETRANSLATIONTRANSFORMATION_H
#define MOT_EXAMPLETRANSLATIONTRANSFORMATION_H

#include "Examples/IExample.h"

#include <GL/glew.h>

#include "math3d.h"
#include "Shader.h"

struct ExampleTranslationTransformation : public IExample
{
    GLuint VBO, VAO;
    std::string Title() override { return "Translation Transformation"; }

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

        shader = std::make_shared<Shader>("wvs.glsl", "wfs.glsl");

        gWorldLocation = glGetUniformLocation(shader->ShaderProgram, "gWorld");
        assert(gWorldLocation != 0xFFFFFFFF);
    }

    void Render() override
    {
        static float Scale = 0.0f;
        Scale += 0.001f;

        Matrix4F World;
        World.m[0][0] = 1.0f; World.m[0][1] = 0.0f; World.m[0][2] = 0.0f; World.m[0][3] = sinf(Scale);
        World.m[1][0] = 0.0f; World.m[1][1] = 1.0f; World.m[1][2] = 0.0f; World.m[1][3] = 0.0f;
        World.m[2][0] = 0.0f; World.m[2][1] = 0.0f; World.m[2][2] = 1.0f; World.m[2][3] = 0.0f;
        World.m[3][0] = 0.0f; World.m[3][1] = 0.0f; World.m[3][2] = 0.0f; World.m[3][3] = 1.0f;
        glUniformMatrix4fv(gWorldLocation, 1, GL_TRUE, &World.m[0][0]);

        shader->Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    std::shared_ptr<Shader> shader;
    GLint gWorldLocation;
};

#endif //MOT_EXAMPLETRANSLATIONTRANSFORMATION_H
