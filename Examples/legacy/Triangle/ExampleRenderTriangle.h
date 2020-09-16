#ifndef MOT_EXAMPLERENDERTRIANGLE_H
#define MOT_EXAMPLERENDERTRIANGLE_H

#include "Examples/IExample.h"

#include <GL/glew.h>

#include "math3d.h"

struct ExampleRenderTriangle : public IExample
{
    GLuint VBO;

    std::string Title() override { return "Render a triangle"; }

    void Init() override
    {
        CreateVertexBuffer_Triangle();
    }
    void Render() override
    {
        RenderTriangle();
    }

    void CreateVertexBuffer_Triangle()
    {
        // We extended the array to contain three vertices.
        std::array vertices = {
                Vector3F(-1.f, -1.f, 0.f),
                Vector3F(1.f, -1.f, 0.f),
                Vector3F(0.f, 1.f, 0.f),
        };

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
    }

    void RenderTriangle()
    {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
        // We draw triangles instead of points and we draw 3 vertices instead of 1.
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
    }
};

#endif //MOT_EXAMPLERENDERTRIANGLE_H
