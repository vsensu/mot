#include <GL/glew.h>
#include <GL/glut.h>

// render event callback function
void RenderSceneCB()
{
    // The only thing we do in our render function is to clear the frame buffer (using the color specified above - try changing it)
    glClear(GL_COLOR_BUFFER_BIT);

	// swap the roles of the back buffer and the front buffer.
    glutSwapBuffers();
}

int main(int argc, char ** argv)
{    
    glutInit(&argc, argv);
    
    //  enables double buffering (drawing to a background buffer while another buffer is displayed) and the color buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    
    glutInitWindowSize(480, 320);
    glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 01");
    
    glutDisplayFunc(RenderSceneCB);
    
	// set the color that will be used when clearing the frame buffer
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // passes control to GLUT which now begins its own internal loop
    glutMainLoop();
  
    return 0;
}
