#include <iostream>
#include <map>
#include <memory>
#include <string>

//#include <GL/glew.h>
//#include <GL/glut.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#include "Examples/IExample.h"
//#include "Examples/Point/ExampleRenderPoint.h"
//#include "Examples/Triangle/ExampleRenderTriangle.h"
//#include "Examples/Shaders/ExampleShader.h"
//#include "Examples/Shaders/ExampleUniformVariables.h"
//#include "Examples/Shaders/ExampleTranslationTransformation.h"
//
//constexpr std::size_t InvalidExampleID = 0;
//std::size_t example_id = InvalidExampleID;
//
//static std::map<std::size_t, std::shared_ptr<IExample>> examples = {
//        {1, std::make_shared<ExampleRenderPoint>()},
//        {2, std::make_shared<ExampleRenderTriangle>()},
//        {3, std::make_shared<ExampleShader>()},
//        {4, std::make_shared<ExampleUniformVariables>()},
//        {5, std::make_shared<ExampleTranslationTransformation>()},
//};
//
//// Render event callback function
//void RenderSceneCB()
//{
//    // The only thing we do in our render function is to clear the frame buffer (using the color specified above - try changing it)
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    // Do render stuff here...
//    if(example_id != InvalidExampleID)
//    {
//        examples[example_id]->Render();
//    }
//
//    // swap the roles of the back buffer and the front buffer.
//    glutSwapBuffers();
//
////    glutPostRedisplay();
//}

//int main(int argc, char** argv)
//{
//    for(const auto &example : examples)
//    {
//        std::cout << example.first << ": " << example.second->Title() << std::endl;
//    }
//    std::cout << ">";
//    std::cin >> example_id;
//
//    // This call initializes GLUT.
//    // The parameters can be provided directly from the command line and include useful options such as '-sync' and
//    // '-gldebug' which disable the asynchronous nature of X and automatically checks for GL errors and displays them (respectively).
//    glutInit(&argc, argv);
//
//    // Enable double buffering (drawing to a background buffer while another buffer is displayed) and the color buffer
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//
//    glutInitWindowSize(480, 320);
//    glutInitWindowPosition(100, 100);
//    auto title = example_id == InvalidExampleID ? "Invalid Example ID" :examples[example_id]->Title();
//    glutCreateWindow(title.c_str());
//
//    // Render callback
//    glutDisplayFunc(RenderSceneCB);
//    // Idle
//    glutIdleFunc(RenderSceneCB);
//
//    // Initialize GLEW and check for any errors. This must be done after GLUT has been initialized.
//    const GLenum res = glewInit();
//    if (res != GLEW_OK)
//    {
//        std::cerr << glewGetErrorString(res) << std::endl;
//        return 1;
//    }
//
//    // Set the color that will be used when clearing the frame buffer
//    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//    // Create vertex buffer and bind data
//    if(example_id != InvalidExampleID)
//    {
//        examples[example_id]->Init();
//    }
//
//    // Pass control to GLUT which now begins its own internal loop
//    glutMainLoop();
//
//    return 0;
//}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
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

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

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
