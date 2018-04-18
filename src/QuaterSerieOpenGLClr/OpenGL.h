#pragma once
// Include GLEW
#include <GL/glew.h>
// Include GLFW
#include <glfw3.h>
#include "shader.hpp" //LoadShaders

ref class OpenGL
{
public:
	OpenGL();

public:

};

int initGL();
void initID();
void initBuffer();


extern GLFWwindow* window;

struct structID
{
	GLuint VertexArrayID;
	GLuint programID;
	GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint TextureID;

};
//structID stID;


struct structbuffer
{
	GLuint vertexbuffer;
	GLuint uvbuffer;
};
//structbuffer stbuffer;



