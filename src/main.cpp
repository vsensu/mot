#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

#include "math3d.h"
#include "Examples/IExample.h"
#include "Examples/Point/ExampleRenderPoint.h"
#include "Examples/Triangle/ExampleRenderTriangle.h"
#include "Examples/Shaders/ExampleShader.h"

constexpr std::size_t InvalidExampleID = 0;
std::size_t example_id = InvalidExampleID;

static std::map<std::size_t, std::shared_ptr<IExample>> examples = {
        {1, std::make_shared<ExampleRenderPoint>()},
        {2, std::make_shared<ExampleRenderTriangle>()},
        {3, std::make_shared<ExampleShader>()},
};

// Render event callback function
void RenderSceneCB()
{
    // The only thing we do in our render function is to clear the frame buffer (using the color specified above - try changing it)
    glClear(GL_COLOR_BUFFER_BIT);

    // Do render stuff here...
    if(example_id != InvalidExampleID)
    {
        examples[example_id]->Render();
    }

    // swap the roles of the back buffer and the front buffer.
    glutSwapBuffers();
}


int main(int argc, char** argv)
{
    for(const auto &example : examples)
    {
        std::cout << example.first << ": " << example.second->Title() << std::endl;
    }
    std::cout << ">";
    std::cin >> example_id;

    // This call initializes GLUT.
    // The parameters can be provided directly from the command line and include useful options such as '-sync' and
    // '-gldebug' which disable the asynchronous nature of X and automatically checks for GL errors and displays them (respectively).
    glutInit(&argc, argv);

    // Enable double buffering (drawing to a background buffer while another buffer is displayed) and the color buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    glutInitWindowSize(480, 320);
    glutInitWindowPosition(100, 100);
    auto title = example_id == InvalidExampleID ? "Invalid Example ID" :examples[example_id]->Title();
    glutCreateWindow(title.c_str());

    // Render callback
    glutDisplayFunc(RenderSceneCB);

    // Initialize GLEW and check for any errors. This must be done after GLUT has been initialized.
    const GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        std::cerr << glewGetErrorString(res) << std::endl;
        return 1;
    }

    // Set the color that will be used when clearing the frame buffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Create vertex buffer and bind data
    if(example_id != InvalidExampleID)
    {
        examples[example_id]->Init();
    }

    // Pass control to GLUT which now begins its own internal loop
    glutMainLoop();

    return 0;
}
