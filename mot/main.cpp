#include <iostream>
#include <map>
#include <memory>
#include <string>

#include <GL/glew.h>
#include <GL/glut.h>

#include "math3d.h"
#include "Examples/Shaders/Shader.h"

constexpr std::size_t InvalidExampleID = 0;
std::size_t example_id = InvalidExampleID;

struct Example
{
	virtual std::string Title() = 0;
	virtual void Init() = 0;
	virtual void Render() = 0;
};

// Draw point
struct ExampleRenderPoint : public Example
{
	// Store the handle of the vertex buffer object.
	GLuint VBO;
	
	std::string Title() override { return "Render a point"; }

	void Init() override
	{
		CreateVertexBuffer_Point();
	}

	void Render() override
	{
		RenderPoint();
	}

	void CreateVertexBuffer_Point()
	{
		// Create an array of vector and initialize to be zero. This will make the dot appear at the middle of the screen
		std::array<Vector3F, 1> vertices = { Vector3F(0.f, 0.f, 0.f) };

		// OpenGL defines several glGen* functions for generating objects of various types.
		// They often take two parameters - the first one specifies the number of objects you want to create
		// and the second is the address of an array of GLuints to store the handles that the driver allocates for you
		// (make sure the array is large enough to handle your request!)
		// At this point you don't specify what you intend to do with the buffers so they can be regarded as "generic". This is the job of the next function.
		glGenBuffers(1, &VBO);

		// OpenGL has a rather unique way of using handles.
		// In many APIs the handle is simply passed to any relevant function and the action is taken on that handle.
		// In OpenGL we bind the handle to a target name and then execute commands on that target.
		// These commands affect the bounded handle until another one is bound in its stead or the call above takes zero as the handle.
		// The target GL_ARRAY_BUFFER means that the buffer will contain an array of vertices.
		// Another useful target is GL_ELEMENT_ARRAY_BUFFER which means that the buffer contains the indices of the vertices in another buffer. 
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// After binding our object we fill it with data. The call above takes the target name (same as what we used for binding),
		// the size of the data in bytes, address of the array of vertices and a flag that indicates the usage pattern for this data.
		// Since we are not going to change the buffer contents we specify GL_STATIC_DRAW.
		// The opposite will be GL_DYNAMIC_DRAW. While this is only a hint to OpenGL it is a good thing to give some thought as to the proper flag to use.
		// The driver can rely on it for optimization heuristics (such as what is the best place in memory to store the buffer).
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
	}

	void RenderPoint()
	{
		// In the shaders tutorial you will see that vertex attributes used in the shader (position, normal, etc)
		// have an index mapped to them that enable you to create the binding between the data in the C/C++ program
		// and the attribute name inside the shader. In addition you must also enable each vertex attribute index.
		// In this tutorial we are not yet using any shader but the vertex position we have loaded into the buffer
		// is treated as vertex attribute index 0 in the fixed function pipeline (which becomes active when there is no shader bound).
		// You must enable each vertex attribute or else the data will not be accessible by the pipeline.
		glEnableVertexAttribArray(0);

		// Here we bind our buffer again as we prepare for making the draw call.
		// In this small program we only have one vertex buffer so making this call every frame is redundent but
		// in more complex programs there are multiple buffers to store your various models and
		// you must update the pipeline state with the buffer you intend to use.
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// This call tells the pipeline how to interpret the data inside the buffer.
		// The first parameter specifies the index of the attribute.
		// In our case we know that it is zero by default but
		// when we start using shaders we will either need to explicitly set the index in the shader or query it.
		// The second parameter is the number of components in the attribute (3 for X, Y and Z).
		// The third parameter is the data type of each component.
		// The next parameter indicates whether we want our attribute to be normalized before it is used in the pipeline.
		// It our case we want the data to pass un-changed.
		// The fifth parameter (called the 'stride') is the number of bytes between two instances of that attribute in the buffer.
		// When there is only one attribute (e.g. the buffer contains only vertex positions) and the data is tightly packed we pass the value zero.
		// If we have an array of structures that contain a position and normal (each one is a vector of 3 floats)
		// we will pass the size of the structure in bytes (6 * 4 = 24).
		// The last parameter is useful in the case of the previous example.
		// We need to specify the offset inside the structure where the pipeline will find our attribute.
		// In the case of the structure with the position and normal the offset of the position is zero while the offset of the normal is 12.
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		// Finally, we make the call to draw the geometry. All the commands that we've seen so far are important but
		// they only set the stage for the draw command. This is where the GPU really starts to work.
		// It will now combine the parameters of the draw call with the state that was built up to this point and render the results to the screen.
		// OpenGL provides several types of draw calls and each one is appropriate for a different case.
		// In general you can divide them up to two categories - ordered draws and indexed draws.
		// Ordered draws are simpler. The GPU traverses your vertex buffer, going through the vertices one by one, and
		// interprets them according to the topology specified in the draw call. For example,
		// if you specify GL_TRIANGLES then vertices 0-2 become the first triangle, 3-5 the second, etc.
		// If you want the same vertex to appear in more than one triangle you will need to specify it twice in the vertex buffer, which is a waste of space.
		// Indexed draws are more complex and involve an additional buffer called the index buffer.
		// The index buffer contains indices of the vertices in the vertex buffer.
		// The GPU scan the index buffer and in a similar fashion to the description above indices 0-2 become the first triangle and so on.
		// If you want the same vertex in two triangles simply specify its index twice in the index buffer.
		// The vertex buffer needs only to contain one copy. Index draws are more common in games because
		// most models are created from triangles that represent some surface (skin of a person, castle wall, etc)
		// with a lot of vertex sharing between them.
		// In this tutorial we use the simplest draw call - glDrawArrays. This is an ordered draw so there is no index buffer.
		// We specify the topology as points which means every vertex is one point. The next parameter is the index of the first vertex to draw.
		// In our case we want to start at the beginning of the buffer so we specify zero but
		// this enables us to store multiple models in the same buffer and then select the one to draw based on its offset in the buffer.
		// The last parameter is the number of vertices to draw.
		glDrawArrays(GL_POINTS, 0, 1);

		// It is good practice to disable each vertex attribute when it is not immediately used.
		// Leaving it enabled when a shader is not using it is a sure way of asking for trouble.
		glDisableVertexAttribArray(0);
	}
};

struct ExampleRenderTriangle : public Example
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

struct ExampleShader : public Example
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
		
		shader = std::make_shared<Shader>("core.vs", "core.frag");
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

static std::map<std::size_t, std::shared_ptr<Example>> examples = {
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
