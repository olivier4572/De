// Include standard headers
#include <stdio.h>
//#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

using namespace glm;

//#include <common/shader.hpp>
//#include <common/texture.hpp>
//#include <common/controls.hpp>

#include "shader.hpp"
#include "texture.hpp"
#include "controls.hpp"

#include <common/text2D.hpp>

// récupération des quaternions et affichage console
#using <System.dll>
using namespace System;
//using namespace System::IO::Ports;
using namespace System::Threading;


#include "SerieCLI.h"


#include <string>
//#include <iostream>  
//using namespace std;


public ref class QuaterSerieOpenGLClr
{

	ref struct structQuater
	{
		int timeStamp;
		int x;
		int y;
		int z;
		int w;
	};

private:
	static bool _continue;
//	static SerialPort^ _serialPort;
	static structQuater _quater;
	static SerieCLI^ serie;


public:
	static int Main()
	{

		//Thread^ readThread = gcnew Thread(gcnew ThreadStart(QuaterSerieOpenGLClr::Read));
		Thread^ readThread;
		serie = gcnew SerieCLI();



		// Initialise GLFW
		if (!glfwInit())
		{
			fprintf(stderr, "Failed to initialize GLFW\n");
			getchar();
			return -1;
		}

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Open a window and create its OpenGL context
		window = glfwCreateWindow(1024, 768, "Tutorial 0 - Keyboard and Mouse", NULL, NULL);
		if (window == NULL) {
			fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
			getchar();
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) {
			fprintf(stderr, "Failed to initialize GLEW\n");
			getchar();
			glfwTerminate();
			return -1;
		}

		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
		// Hide the mouse and enable unlimited mouvement
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Set the mouse at the center of the screen
		//glfwPollEvents();
		//glfwSetCursorPos(window, 1024 / 2, 768 / 2);

		// Dark blue background
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		// Enable depth test
		glEnable(GL_DEPTH_TEST);
		// Accept fragment if it closer to the camera than the former one
		glDepthFunc(GL_LESS);

		// Cull triangles which normal is not towards the camera
		glEnable(GL_CULL_FACE);

		GLuint VertexArrayID;
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);

		// Create and compile our GLSL program from the shaders
		GLuint programID = LoadShaders("TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader");

		// Get a handle for our "MVP" uniform
		GLuint MatrixID = glGetUniformLocation(programID, "MVP");
		//ajout tuto11
		GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
		GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
		//fin ajout tuto11

		// Load the texture
		GLuint Texture = loadDDS("uvtemplate.DDS");

		// Get a handle for our "myTextureSampler" uniform
		GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

		// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
		// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
		static const GLfloat g_vertex_buffer_data[] = {
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

		// Two UV coordinatesfor each vertex. They were created withe Blender.
		static const GLfloat g_uv_buffer_data[] = {
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

		GLuint vertexbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		GLuint uvbuffer;
		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

		// Initialize our little text library with the Holstein font
		initText2D("Holstein.DDS");

		quat gOrientationInit;
		bool bPressSpace = false;
		gOrientationInit.x = 0;
		gOrientationInit.y = 0;
		gOrientationInit.z = 0;
		gOrientationInit.w = 0;
		bool bFirst = true;
		do {
			if (!_continue) {
				if (!bFirst) { readThread->Join(); }
				if (serie->_serialPort->IsOpen) {
					serie->_serialPort->Close(); }
				try
				{
					serie->_serialPort->Open();
				}
				catch (Exception^)
				{
					int i=0;
					i = i + 1;
				}
				_continue = true;
				bFirst = false;
				readThread = gcnew Thread(gcnew ThreadStart(QuaterSerieOpenGLClr::Read));
				readThread->Start();
			}

			// Clear the screen
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Use our shader
			glUseProgram(programID);

			// Compute the MVP matrix from keyboard and mouse input
			//computeMatricesFromInputs();
			computeMatricesFromInputsQuater(_quater.x,_quater.y,_quater.z, _quater.w);
			glm::mat4 ProjectionMatrix = getProjectionMatrix();
			glm::mat4 ViewMatrix = getViewMatrix();
			//glm::mat4 ModelMatrix = glm::mat4(1.0);

			vec3 gPosition(0.0f, 0.0f, 0.5f);
			quat gOrientation;
			gOrientation.x = _quater.x/10000.0;
			gOrientation.y = _quater.y/10000.0;
			gOrientation.z = _quater.z/10000.0;
			gOrientation.w = _quater.w/10000.0;

			glm::mat4 RotationMatrix = mat4_cast(gOrientation);
			glm::mat4 RotationMatrixInit = mat4_cast(gOrientationInit);
			glm::mat4 TranslationMatrix = translate(mat4(), gPosition); // A bit to the right
			glm::mat4 ScalingMatrix = scale(mat4(), vec3(1.0f, 1.0f, 1.0f));
			glm::mat4 ModelMatrix = TranslationMatrix * RotationMatrix * ScalingMatrix / RotationMatrixInit;

			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

			// Send our transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			// ajout tuto11
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
			//fin ajout tuto11

			// Bind our texture in Texture Unit 0
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Texture);
			// Set our "myTextureSampler" sampler to user Texture Unit 0
			glUniform1i(TextureID, 0);

			// 1rst attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glVertexAttribPointer(
				0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);

			// 2nd attribute buffer : UVs
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
			glVertexAttribPointer(
				1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				2,                                // size : U+V => 2
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);

			// Draw the triangle !
			glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);


			char text[256];
			//sprintf(text, "%.2f sec", glfwGetTime());
			sprintf(text, "Qx:%d \t Qy:%d \t Qz:%d \t Qw:%d \t", _quater.x, _quater.y, _quater.z, _quater.w);
			printText2D(text, 1, 1, 20);

			// Swap buffers
			glfwSwapBuffers(window);
			glfwPollEvents();

			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && bPressSpace == false) {
				gOrientationInit.x = _quater.x / 10000.0;
				gOrientationInit.y = _quater.y / 10000.0;
				gOrientationInit.z = _quater.z / 10000.0;
				gOrientationInit.w = _quater.w / 10000.0;
				bPressSpace = true;
			}
			if (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS) {
				bPressSpace = false;
			}

		} // Check if the ESC key was pressed or the window was closed
		while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(window) == 0);

		readThread->Join();
		if (serie->_serialPort->IsOpen) { serie->_serialPort->Close(); }


		_continue = false;

		// Cleanup VBO and shader
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &uvbuffer);
		glDeleteProgram(programID);
		glDeleteTextures(1, &TextureID);
		glDeleteVertexArrays(1, &VertexArrayID);

		// Close OpenGL window and terminate GLFW
		glfwTerminate();


		return 0;
	}

	static void Read()
	{
		String^ delimStr = "_";
		array<Char>^ delimiter = delimStr->ToCharArray();
		while (_continue)
		{
			try
			{
				array<String^>^ words;
				try
				{
					String^ message = serie->_serialPort->ReadLine();
					words = message->Split(delimiter);
				}
				catch(System::IO::IOException ^){
					int i = 0;
					i = i + 1;

				}
				//printf("Trame : %s\n", message);
				
				if (words->Length == 11) {
					if (words[1] != "" && words[2] != "" && words[3] != "" && words[4] != "") {
						std::string b;
						MarshalString(words[1], b);
						_quater.timeStamp = std::stoi(b);
						MarshalString(words[2], b);
						_quater.x = std::stoi(b);
						MarshalString(words[3], b);
						_quater.y = std::stoi(b);
						MarshalString(words[4], b);
						_quater.z = std::stoi(b);

						if (_quater.x > 10000) { _quater.x = _quater.x - 65536;}
						if (_quater.y > 10000) { _quater.y = _quater.y - 65536; }
						if (_quater.z > 10000) { _quater.z = _quater.z - 65536; }


						double w = 1.0 - (double(_quater.x) / 10000.0 * double(_quater.x) / 10000.0 + double(_quater.y) / 10000.0*double(_quater.y) / 10000.0 + double(_quater.z) / 10000.0*double(_quater.z) / 10000.0);
						w = sqrt(w);
						_quater.w =(int) (w * 10000.0);
						printf("Quater : %d %d %d %d %d\n", _quater.timeStamp, _quater.x, _quater.y, _quater.z, _quater.w);
					}
				}

			}
			catch (TimeoutException ^) {
				printf("timeOutException");
				_continue = false;
			}
		}
	}

	static void MarshalString(String ^ s, std::string& os) {
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}
};
int main()
{
	QuaterSerieOpenGLClr::Main();
}