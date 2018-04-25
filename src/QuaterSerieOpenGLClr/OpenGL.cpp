#include "OpenGL.h"
#include <stdio.h>

OpenGL::OpenGL()
{
}

int initGL() 
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(
		GLFW_SAMPLES, 
		4
	);
	glfwWindowHint(
		GLFW_CONTEXT_VERSION_MAJOR, 
		3
	);
	glfwWindowHint(
		GLFW_CONTEXT_VERSION_MINOR,
		3
	);
	/* To make MacOS happy; should not be needed */
	glfwWindowHint(
		GLFW_OPENGL_FORWARD_COMPAT, 
		GL_TRUE
	);  
	glfwWindowHint(
		GLFW_OPENGL_PROFILE, 
		GLFW_OPENGL_CORE_PROFILE
	);

	/* Open a window and create its OpenGL context */
	window = glfwCreateWindow(
		1024, 
		768, 
		"Tutorial 0 - Keyboard and Mouse", 
		NULL, 
		NULL
	);

	if (window == NULL) 
	{
		fprintf(
			stderr, 
			"Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	/* Initialize GLEW */
	/* Needed for core profile */
	glewExperimental = true; 
	if (glewInit() != GLEW_OK) 
	{
		fprintf(
			stderr, 
			"Failed to initialize GLEW\n"
		);
		getchar();
		glfwTerminate();
		return -1;
	}


	/* Ensure we can capture the escape key being pressed below */
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	/* Hide the mouse and enable unlimited mouvement */
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* Set the mouse at the center of the screen */
	//glfwPollEvents();
	//glfwSetCursorPos(window, 1024 / 2, 768 / 2);

	/* Dark blue background */
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	/* Enable depth test */
	glEnable(GL_DEPTH_TEST);
	/* Accept fragment if it closer to the camera than the former one */
	glDepthFunc(GL_LESS);

	/* Cull triangles which normal is not towards the camera */
	glEnable(GL_CULL_FACE);

	return 1;
}


void initID() 
{
	structID stID;
	glGenVertexArrays(1, &stID.VertexArrayID);

	/* Create and compile our GLSL program from the shaders */
	stID.programID = LoadShaders(
		"TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader"
	);

	/* Get a handle for our "MVP" uniform */
	stID.MatrixID = glGetUniformLocation(
		stID.programID, 
		"MVP"
	);
	/* ajout tuto11 */
	stID.ViewMatrixID = glGetUniformLocation(
		stID.programID, 
		"V"
	);
	stID.ModelMatrixID = glGetUniformLocation(
		stID.programID, 
		"M"
	);

	/* Get a handle for our "myTextureSampler" uniform */
	stID.TextureID = glGetUniformLocation(
		stID.programID, 
		"myTextureSampler"
	);


}

void initBuffer() 
{
	structbuffer stbuffer;
	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	/* Two UV coordinatesfor each vertex. They were created withe Blender. */
	static const GLfloat g_uv_buffer_data[] = 
	{
		0.000059f, 0.000004f,
		0.000103f, 0.336048f,
		0.335973f, 0.335903f,
		1.000023f, 0.000013f,
		0.667979f, 0.335851f,
		0.999958f, 0.336064f,
		0.667979f, 0.335851f,
		0.336024f, 0.671877f,
		0.667969f, 0.671889f,
		1.000023f, 0.000013f,
		0.668104f, 0.000013f,
		0.667979f, 0.335851f,
		0.000059f, 0.000004f,
		0.335973f, 0.335903f,
		0.336098f, 0.000071f,
		0.667979f, 0.335851f,
		0.335973f, 0.335903f,
		0.336024f, 0.671877f,
		1.000004f, 0.671847f,
		0.999958f, 0.336064f,
		0.667979f, 0.335851f,
		0.668104f, 0.000013f,
		0.335973f, 0.335903f,
		0.667979f, 0.335851f,
		0.335973f, 0.335903f,
		0.668104f, 0.000013f,
		0.336098f, 0.000071f,
		0.000103f, 0.336048f,
		0.000004f, 0.671870f,
		0.336024f, 0.671877f,
		0.000103f, 0.336048f,
		0.336024f, 0.671877f,
		0.335973f, 0.335903f,
		0.667969f, 0.671889f,
		1.000004f, 0.671847f,
		0.667979f, 0.335851f
	};

	glGenBuffers(
		1, 
		&stbuffer.vertexbuffer
	);
	glBindBuffer(
		GL_ARRAY_BUFFER, 
		stbuffer.vertexbuffer
	);
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(g_vertex_buffer_data), 
		g_vertex_buffer_data, 
		GL_STATIC_DRAW
	);

	/* GLuint uvbuffer; */
	glGenBuffers(
		1, 
		&stbuffer.uvbuffer
	);
	glBindBuffer(
		GL_ARRAY_BUFFER, 
		stbuffer.uvbuffer
	);
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(g_uv_buffer_data), 
		g_uv_buffer_data, 
		GL_STATIC_DRAW
	);


}
