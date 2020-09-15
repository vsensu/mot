#ifndef MOT_EXAMPLEUNIFORMVARIABLES_H
#define MOT_EXAMPLEUNIFORMVARIABLES_H

#include "Examples/IExample.h"

#include <GL/glew.h>

#include "math3d.h"
#include "Shader.h"

struct ExampleUniformVariables : public IExample
{
    GLuint VBO, VAO;
    std::string Title() override { return "Uniform Variables"; }
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

        shader = std::make_shared<Shader>("uvs.glsl", "ufs.glsl");

        // After linking the program we query the program object for the location of the uniform variable.
        // This is another example of a case where the application C/C++ execution environment needs to be mapped to
        // the shader execution environment. You don't have any direct access to shader content and
        // you cannot directly update its variables. When you compile the shader
        // the GLSL compiler assigns an index to each uniform variable.
        // In the internal representation of the shader inside the compiler access to the variable is
        // resolved using its index. That index is also available to the application via the glGetUniformLocation.
        // You call this function with the program object handle and the name of the variable.
        // The function returns the index or -1 if there was an error.
        // It is very important to check for errors (as we do above with the assertion) or
        // else future updates to the variables will not be delivered to the shader.
        // There are mainly two reasons why this function can fail.
        // You either misspelled the name of the variable or it was optimized away by the compiler.
        // If the GLSL compiler finds out that the variable is not actually used in the shader it can simply drop it.
        // In that case glGetUniformLocation will fail.
        gScaleLocation = glGetUniformLocation(shader->ShaderProgram, "gScale");
        assert(gScaleLocation != 0xFFFFFFFF);
    }
    void Render() override
    {
        // We maintain a static floating point variable that we increment a bit in every call to the render function
        // (you may want to play with 0.001 if it runs too slowly or too quickly on your machine).
        // The actual value which is passed to the shader is the sinus of the 'Scale' variable.
        // This is to create a nice loop between -1.0 and 1.0. Note that sinf() takes radians and not degrees as
        // a parameter but at this point we simply don't care. We just want the wave that sinus generates.
        // The result of sinf() is passed to the shader using glUniform1f.
        // OpenGL provides multiple instances of this function with the general form of glUniform{1234}{if}.
        // You can use it to load values into a 1D, 2D, 3D or 4D
        // (based on the number that follows the 'glUniform') vector of floating point or integer
        // (this is the 'i' or 'f' suffix).
        // There are also versions that take a vector address as a parameter as well as special version for matrices.
        // The first parameter to the function is the index location that we have extracted using glGetUniformLocation().
        static float Scale = 0.0f;
        Scale += 0.001f;
        glUniform1f(gScaleLocation, sinf(Scale));

        shader->Use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
    }

    std::shared_ptr<Shader> shader;
    GLint gScaleLocation;
};

#endif //MOT_EXAMPLEUNIFORMVARIABLES_H
