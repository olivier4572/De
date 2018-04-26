/* Include standard headers */
#include <stdio.h>
#include <string>

/* Include GLEW */
#include <GL/glew.h>

/* Include GLFW */
#include <glfw3.h>
GLFWwindow* window;

/* Include GLM */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;

/* récupération des quaternions et affichage console */
//#include "shader.hpp"
#include "texture.hpp"
#include "controls.hpp"
#include "text2D.hpp"

/*
* il faut me mettre avant using namespace System;
* pour éviter   error C2872: 'IServiceProvider' : ambiguous symbol
* shellexecute
*/
#include <shlobj.h> 

#using <System.dll>
using namespace System;
using namespace System::Threading;
using namespace System::IO;

#include "SerieCLI.h"
#include "OpenGL.h"
//ifstream,fichier
#include <fstream> 

#define DEBUG true;


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
	/* force a sortir de la boucle Read */
	static bool _continueRead;
	/* erreur de lecture port sérir dans la boucle Read */
	static bool _erreurRead;  
	static structQuater _quater;
	static SerieCLI^ serie;

public:
	static int Main()
	{
		/*
		* Thread^ readThread = 
		*	gcnew Thread(gcnew ThreadStart(QuaterSerieOpenGLClr::Read));
		*/
		Thread^ readThread;
		serie = gcnew SerieCLI();
		if (!initGL()) 
		{
			return -1;
		}

		//initID();
		GLuint VertexArrayID;
		GLuint programID;
		GLuint MatrixID;
		GLuint ViewMatrixID;
		GLuint ModelMatrixID;
		GLuint TextureID;

		glGenVertexArrays(
			1, 
			&VertexArrayID
		);

		/* Create and compile our GLSL program from the shaders */
		programID = LoadShaders(
			"TransformVertexShader.vertexshader", 
			"TextureFragmentShader.fragmentshader"
		);

		/* Get a handle for our "MVP" uniform */
		MatrixID = glGetUniformLocation(
			programID, 
			"MVP"
		);
		/* ajout tuto11 */
		ViewMatrixID = glGetUniformLocation(
			programID,
			"V"
		);
		ModelMatrixID = glGetUniformLocation(
			programID, 
			"M"
		);

		/* Get a handle for our "myTextureSampler" uniform */
		TextureID = glGetUniformLocation(
			programID, 
			"myTextureSampler"
		);


		glBindVertexArray(VertexArrayID);

		/* Load the texture */
		GLuint Texture = loadDDS("Image/de6.DDS");
		//GLuint Texture = loadDDS("Image/Sans titre.DDS");

		//initBuffer();


		/* 
		* Our vertices. Tree consecutive floats give a 3D vertex; 
		* Three consecutive vertices give a triangle.
		* A cube has 6 faces with 2 triangles each, 
		* so this makes 6*2=12 triangles, and 12*3 vertices
		*/
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

		/* 
		* Two UV coordinatesfor each vertex. 
		* They were created withe Blender
		*/
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

		GLuint vertexbuffer;
		glGenBuffers(
			1, 
			&vertexbuffer
		);

		glBindBuffer(
			GL_ARRAY_BUFFER, 
			vertexbuffer
		);

		glBufferData(
			GL_ARRAY_BUFFER, 
			sizeof(g_vertex_buffer_data), 
			g_vertex_buffer_data, 
			GL_STATIC_DRAW
		);

		GLuint uvbuffer;
		glGenBuffers(
			1, 
			&uvbuffer
		);

		glBindBuffer(
			GL_ARRAY_BUFFER, 
			uvbuffer
		);

		glBufferData(
			GL_ARRAY_BUFFER, 
			sizeof(g_uv_buffer_data),
			g_uv_buffer_data, 
			GL_STATIC_DRAW
		);

		/* Initialize our little text library with the Holstein font */
		initText2D("Image/Holstein.DDS");

		quat gOrientationInitQuat;
		vec3 gOrientationInitEuler;

		bool bPressSpace = false;

		gOrientationInitQuat.x  = 0;
		gOrientationInitQuat.y  = 0;
		gOrientationInitQuat.z  = 0;
		gOrientationInitQuat.w  = 0;
		gOrientationInitEuler.x = 0;
		gOrientationInitEuler.y = 0;
		gOrientationInitEuler.z = 0;

		bool bFirst = true;
		bool bEsc	= false;
		bool bFinProgramme;
		bool bPressTab = false;

		std::string sFace	= "NU";
		double lastTime		= glfwGetTime();
		float lastdeltaTime = 0;
		do 
		{
			double currentTime  = glfwGetTime();
			float deltaTime		= (float)(currentTime - lastTime);

			if (!bEsc)
			{
				if (!_continueRead) 
				{
					if (!bFirst) 
					{
						readThread->Join(); 
						delete readThread;
					}
					if (serie->_serialPort->IsOpen) 
					{
						serie->_serialPort->Close();
					}
					try
					{
						serie->_serialPort->Open();
						bFirst = true;
					}
					catch (Exception^ e)
					{
						/* toujours pas de connection serie */
						System::String^ chaine = gcnew System::String("");
						chaine = chaine->Concat(e->Message);
						Log(chaine, "MainSerie");
						delete chaine;
					}
					if (serie->_serialPort->IsOpen) 
					{
						if (bFirst) 
						{
							readThread = gcnew Thread(
								gcnew ThreadStart(
									QuaterSerieOpenGLClr::ReadQuater
								)
							);
							readThread->Start();
							_continueRead = true;
							bFirst = false;
						}
					}
				}
			}

			/* Clear the screen */
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			/* Use our shader */
			glUseProgram(programID);

			/* Compute the MVP matrix from keyboard and mouse input */
			//computeMatricesFromInputs();
			computeMatricesFromInputsQuater();
			glm::mat4 ProjectionMatrix  = getProjectionMatrix();
			glm::mat4 ViewMatrix		= getViewMatrix();
			//glm::mat4 ModelMatrix = glm::mat4(1.0);

			vec3 gPosition(0.0f, 0.0f, 0.0f);

			quat gOrientationQuat;
			gOrientationQuat.x = _quater.x / 10000.0;
			gOrientationQuat.y = _quater.y / 10000.0;
			gOrientationQuat.z = _quater.z / 10000.0;
			gOrientationQuat.w = _quater.w / 10000.0;

			vec3 gOrientationEuler;
			gOrientationEuler.x = _quater.z / 10.0 / 360 * (3.14 * 2);
			gOrientationEuler.y = _quater.y / 10.0 / 360 * (3.14 * 2);
			gOrientationEuler.z = _quater.x / 10.0 / 360 * (3.14 * 2);

			glm::mat4 RotationMatrix = mat4_cast(gOrientationQuat);
			glm::mat4 RotationMatrixInit = mat4_cast(gOrientationInitQuat);
			/* euler */
			/*glm::mat4 RotationMatrix = eulerAngleYXZ(
				gOrientationEuler.x, 
				gOrientationEuler.y, 
				gOrientationEuler.z
			);*/
			/*glm::mat4 RotationMatrixInit = eulerAngleYXZ(
				gOrientationInitEuler.x, 
				gOrientationInitEuler.y, 
				gOrientationInitEuler.z
			);*/

			/* A bit to the right */
			glm::mat4 TranslationMatrix = translate(
				mat4(), 
				gPosition
			); 

			glm::mat4 ScalingMatrix = scale(
				mat4(), 
				vec3(
					1.0f, 
					1.0f, 
					1.0f
				)
			);

			glm::mat4 ModelMatrix = (
				TranslationMatrix / 
				RotationMatrixInit * 
				RotationMatrix * 
				ScalingMatrix
				);
			/*glm::mat4 ModelMatrix = 
				TranslationMatrix * RotationMatrix * ScalingMatrix;*/


			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

			/* 
			* Send our transformation to the currently bound shader, 
			* in the "MVP" uniform 
			*/
			glUniformMatrix4fv(
				MatrixID, 
				1, 
				GL_FALSE, 
				&MVP[0][0]
			);

			/* ajout tuto11 */
			glUniformMatrix4fv(
				ModelMatrixID, 
				1, 
				GL_FALSE, 
				&ModelMatrix[0][0]
			);

			glUniformMatrix4fv(
				ViewMatrixID, 
				1, 
				GL_FALSE, 
				&ViewMatrix[0][0]
			);
			/* fin ajout tuto11 */

			/* Bind our texture in Texture Unit 0 */
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(
				GL_TEXTURE_2D, 
				Texture
			);

			/* Set our "myTextureSampler" sampler to user Texture Unit 0 */
			glUniform1i(
				TextureID, 
				0
			);

			/* 1rst attribute buffer : vertices */
			glEnableVertexAttribArray(0);
			glBindBuffer(
				GL_ARRAY_BUFFER, 
				vertexbuffer
			);

			glVertexAttribPointer(
				0, /* attribute. No particular reason for 0, 
				   but must match the layout in the shader.*/
				3,         /* size */
				GL_FLOAT,  /* type */
				GL_FALSE,  /* normalized? */
				0,         /* stride */
				(void*)0   /* array buffer offset */
			);

			/* 2nd attribute buffer : UVs  */
			glEnableVertexAttribArray(1);
			glBindBuffer(
				GL_ARRAY_BUFFER, 
				uvbuffer
			);

			glVertexAttribPointer(
				1, /* attribute. No particular reason for 1, 
				   but must match the layout in the shader. */
				2,         /* size : U+V => 2 */
				GL_FLOAT,  /* type */
				GL_FALSE,  /* normalized? */
				0,         /* stride */
				(void*)0   /* array buffer offset */
			);

			/* Draw the triangle ! */
			/* 12*3 indices starting at 0 -> 12 triangles */
			glDrawArrays(
				GL_TRIANGLES, 
				0, 
				12 * 3
			); 

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);

			char text[256];
			//sprintf(text, "%.2f sec", glfwGetTime());
			sprintf(
				text, 
				"Qx:%0.0f \t Qy:%0.0f \t Qz:%0.0f \t Qw:%0.0f \t", 
				gOrientationQuat.x * 10000, 
				gOrientationQuat.y * 10000, 
				gOrientationQuat.z * 10000, 
				gOrientationQuat.w * 10000
			);

			printText2D(
				text, 
				1, 
				1, 
				20
			);

			EcrireFichierQuater();
			
			std::string s = TestPresenceFichier();
			if (s != "NU") 
			{
				sFace = s;
				SupprimeFace(sFace);
			}

			std::string sFaceSub;

			if (sFace.length()>6)
			{
				sFaceSub = sFace.substr(2, sFace.length() - 6);
			}
			else
			{
				sFaceSub = sFace;
			}
			AfficheFace(sFaceSub);
			//AfficheFace(sFace);

			/* Swap buffers */
			glfwSwapBuffers(window);
			glfwPollEvents();

			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && 
				bPressSpace == false) 
			{
				gOrientationInitQuat.x	= _quater.x / 10000.0;
				gOrientationInitQuat.y	= _quater.y / 10000.0;
				gOrientationInitQuat.z	= _quater.z / 10000.0;
				gOrientationInitQuat.w	= _quater.w / 10000.0;
				gOrientationInitEuler.x = _quater.z / 10.0 / 360 * (3.14 * 2);
				gOrientationInitEuler.y = _quater.y / 10.0 / 360 * (3.14 * 2);
				gOrientationInitEuler.z = _quater.x / 10.0 / 360 * (3.14 * 2);

				bPressSpace = true;
			}
			
			if (glfwGetKey(window, GLFW_KEY_SPACE) != GLFW_PRESS)
			{
				bPressSpace = false;
			}

			//if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && bPressTab == false)
			if (deltaTime - lastdeltaTime > 0.5)
			{
				lastdeltaTime = deltaTime;
				bPressTab = true;
				HINSTANCE result;

				char text[256];
				sprintf(
					text, 
					"%d %d %d %d", 
					_quater.x, 
					_quater.y, 
					_quater.z, 
					_quater.w
				);

#if DEBUG
				result = ShellExecute(
					NULL, 
					NULL, 
					"..\\x64\\Debug\\ModeleFaceDeQuaterAzureAPI.exe", 
					text, 
					NULL, 
					SW_SHOWMINIMIZED
				);
#else
				result = ShellExecute(
					NULL, 
					NULL, 
					"ModeleFaceDeQuaterAzureAPI.exe", 
					text, 
					NULL, 
					SW_HIDE
				);
#endif
				/*result = ShellExecute(
				NULL, 
				NULL, 
				"C:\\Donnees\\Projet\\cdr\\De\\git\\De\\src\\x64\\Debug\
					\ModeleFaceDeQuaterAzureAPI.exe", 
				NULL, 
				NULL, 
				SW_SHOWDEFAULT
				); */

				/*
				SHELLEXECUTEINFO rSEI = { 0 };
				rSEI.cbSize = sizeof(rSEI);
				rSEI.lpVerb = "open";
				rSEI.lpFile = "..\\x64\\Debug\\ModeleFaceDeQuaterAzureAPI.exe";
				rSEI.lpParameters = 0;
				rSEI.nShow = SW_NORMAL;
				rSEI.fMask = SEE_MASK_NOCLOSEPROCESS;

				// you should check for an error here
				int ret = ShellExecuteEx(&rSEI); 

				while (TRUE)
				{
				DWORD nStatus = MsgWaitForMultipleObjects(
				1, 
				&rSEI.hProcess, 
				FALSE,
				INFINITE, 
				QS_ALLINPUT   // drop through on user activity
				);

				if (nStatus == WAIT_OBJECT_0) 
				{  // done: the program has ended
				break;
				}

				MSG msg;     // else process some messages while waiting...
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
				{
				DispatchMessage(&msg);
				}
				printf("%s\n", msg.wParam);

				}  // launched process has exited
				*/


			}

			if (glfwGetKey(window, GLFW_KEY_TAB) != GLFW_PRESS) 
			{
				bPressTab = false;
			}


			bFinProgramme = !_continueRead && bEsc;
			if (_erreurRead)
			{
				_continueRead = false;
				_erreurRead = false;
			}

			bEsc = !(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && 
				glfwWindowShouldClose(window) == 0);
			if (bEsc) 
			{
				_continueRead = false;
			};

		} /* Check if the ESC key was pressed or the window was closed */
		  //while (!bFinProgramme);
		while (!bFinProgramme);

		if (readThread) readThread->Join();
		if (serie->_serialPort->IsOpen) {
			serie->_serialPort->Close();
		}

		/* Cleanup VBO and shader */
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &uvbuffer);
		glDeleteProgram(programID);
		glDeleteTextures(1, &TextureID);
		glDeleteVertexArrays(1, &VertexArrayID);

		/* Close OpenGL window and terminate GLFW */
		glfwTerminate();

		delete serie;

		return 0;
	}

	static void Log(System::String^ message, System::String^ titre) 
	{
#if DEBUG
		String^ fileName = "..//X64//DEBUG//Log//";
#else
		String^ fileName = "Log//";
#endif

		fileName = fileName->Concat(fileName,"log", titre, ".log");

		/* 
		* Exemple
		* char text[256];
		* sprintf(
		*	text, 
		*	"%d;%d;%d;%d", 
		*	_quater.x, 
		*	_quater.y, 
		*	_quater.z, 
		*	_quater.w
		* );
		* System::String^ chaine = gcnew System::String(text);
		*/
		try
		{
			StreamWriter^ sw = gcnew StreamWriter(fileName, true);
			try
			{
				message = message->Concat(DateTime::Now, ":", message);
				sw->WriteLine(message);
				// sw->WriteLine(DateTime::Now);
				sw->Close();
			}
			finally
			{
				delete sw;
			}

		}
		catch (const std::exception&)
		{
			/* pas de log d'une erreur log */
		}

	}

	static void ReadQuater()
	{
		String^ delimStr = "_";
		array<Char>^ delimiter = delimStr->ToCharArray();
		structQuater quater;
		while (_continueRead)
		{
			try
			{
				array<String^>^ words;
				String^ message = serie->_serialPort->ReadLine();
				words = message->Split(delimiter);
				//printf("Trame : %s\n", message);

				if (words->Length == 11) 
				{
					if (words[1] != "" && 
						words[2] != "" && 
						words[3] != "" && 
						words[4] != "") 
					{
						try
						{
							std::string b;
							MarshalString(words[1], b);
							//b = "2854472289"; /* provoque l'erreur */
							quater.timeStamp = std::stoi(b);
							MarshalString(words[2], b);
							quater.x = std::stoi(b);
							MarshalString(words[3], b);
							quater.y = std::stoi(b);
							MarshalString(words[4], b);
							quater.z = std::stoi(b);

							if (quater.x > 10000) 
							{ 
								quater.x = quater.x - 65536; 
							}
							if (quater.y > 10000) 
							{ 
								quater.y = quater.y - 65536;
							}
							if (quater.z > 10000) 
							{ 
								quater.z = quater.z - 65536; 
							}

							double w = 1.0 - (double(quater.x) / 10000.0 * 
								double(quater.x) / 10000.0 + 
								double(quater.y) / 
								10000.0*double(quater.y) / 
								10000.0 + double(quater.z) / 
								10000.0*double(quater.z) / 10000.0);
							w = sqrt(w);
							quater.w = (int)(w * 10000.0);
							_quater.x = quater.x;
							_quater.y = quater.y;
							_quater.z = quater.z;
							_quater.w = quater.w;
							_quater.timeStamp = quater.timeStamp;
							printf(
								"Quater : %d %d %d %d %d\n",
								_quater.timeStamp, 
								_quater.x,
								_quater.y,
								_quater.z,
								_quater.w
							);
						}
						catch (
							System::Runtime::InteropServices::SEHException^ e
							)
						{
							System::String^ chaine = gcnew System::String("");
							chaine = chaine->Concat(e->Message);
							Log(chaine, "ReadQuater");
							delete chaine;

						}
					}
				}

			}
			catch (System::IO::IOException ^ ) 
			{
				printf("TimeoutException : Port serie, arret thread\n");
				System::String^ chaine = gcnew System::String(
					"TimeoutException : Port serie, arret thread\n"
				);
				_erreurRead = true;
				Log(
					chaine, 
					"ReadQuaterSerie"
				);
				delete chaine;
			}
			catch (System::TimeoutException ^) 
			{
				printf("TimeoutException : Port serie\n");
				System::String^ chaine = gcnew System::String(
					"TimeoutException : Port serie\n"
				);
				_erreurRead = true;
				Log(chaine, "ReadQuaterSerie");
				delete chaine;
			}
			catch (System::InvalidOperationException ^) 
			{
				printf("InvalidOperationException : Port ferme\n");
				System::String^ chaine = gcnew System::String(
					"InvalidOperationException : Port ferme\n"
				);
				_erreurRead = true;
				Log(chaine, "ReadQuaterSerie");
				delete chaine;
			}
		}
	}

	static void MarshalString(String ^ s, std::string& os) 
	{
		using namespace Runtime::InteropServices;
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
	}

	static void EcrireFichierQuater() 
	{
#if DEBUG
		String^ fileName = "..//X64//DEBUG//Donnees//quatercsvfile.csv";
#else
		String^ fileName = "Donnees//quatercsvfile.csv";
#endif

		char text[256];
		sprintf(
			text, 
			"%d;%d;%d;%d", 
			_quater.x, 
			_quater.y, 
			_quater.z, 
			_quater.w
		);

		try
		{
			System::String^ chaine = gcnew System::String(text);

			StreamWriter^ sw = gcnew StreamWriter(fileName, true);
			try
			{
				sw->WriteLine(chaine);
				sw->Close();
			}
			finally
			{
			delete sw;
			delete chaine;
			}
		}
		catch (Exception^ e)
		{
			System::String^ chaine = gcnew System::String(
				"The process failed:"
			);
			chaine = chaine->Concat(e->Message);
			Log(chaine,"EcrireFichierQuater");
			delete chaine;
		}
	}

	static void AfficheFace(std::string sFace) 
	{
		const char *CstStr = sFace.data();
		printText2D(CstStr, 50, 50, 20);
	}

	static void SupprimeFace(std::string sFace) 
	{
#if DEBUG
		sFace = "..\\QuaterSerieOpenGLClr\\De\\" + sFace;
		const char *CstStr = sFace.data();
#else
		sFace = "De\\" + sFace;
		const char *CstStr = sFace.data();
#endif


		/* Supprimer le fichier */
		std::remove(CstStr);
	}

	static std::string TestPresenceFichier()
	{
		std::string Retour ="NU";
		/* Tester la présence d'un fichier De1.txt, De2.txt.... */
		String^ fileName;
		char text[256];

		WIN32_FIND_DATA File;
		HANDLE hSearch;
#if DEBUG
		//hSearch = FindFirstFile("..\\x64\\Debug\\De\\De*.txt", &File);
		hSearch = FindFirstFile(
			"..\\QuaterSerieOpenGLClr\\De\\De*.txt", 
			&File
		);
#else
		hSearch = FindFirstFile("De\\De*.txt", &File);
#endif

		if (hSearch != INVALID_HANDLE_VALUE)
		{
			do {
				printf("%s\n", File.cFileName);
			} while (FindNextFile(hSearch, &File));
			FindClose(hSearch);
			Retour = File.cFileName;
		}
		/*
		for (int i = 1; i <= 6 ;i++ )
		{
			sprintf(text, "De%d.txt", i);
			//si le fichier existe
			if (is_readable(text))
			{
				printf ("fichier exist %s\n",text);
				Retour = i;

			}
			else
			{
				//printf("Fichier inexistant ou non lisible %s \n.",text);
			}
		}
		*/
		return Retour;
	}

	static void LectureFichierModele(String^ fileName) 
	{
		//String^ fileName = "tst.txt";
		String^ strRead;;
		std::string b;

		StreamReader^ sr = gcnew StreamReader(fileName);
		try
		{
			strRead = sr->ReadLine();
			sr->Close();
			MarshalString(strRead, b);
			const char *CstStr1 = b.data();
			const char *CstStr2 = b.c_str();
			printText2D(CstStr1, 50, 50, 20);
		}
		finally
		{
			delete sr;
		}
	}

	static bool is_readable(const std::string & file)
	{
		std::ifstream fichier(file.c_str());
		return !fichier.fail();
	}


};

/* trouver le chemin (uniquement) de l'application */
void GetChemin(char *chemin, DWORD taille)
{
	char *c;
	c = chemin + GetModuleFileName(NULL, chemin, taille);
	while (*c != '\\')
		c--;
	*c = 0;
}


int main()
{

	char chemin[MAX_PATH];
	GetChemin(chemin, MAX_PATH);

	printf("%s\n",chemin);
	
	QuaterSerieOpenGLClr::Main();

	printf("Au revoir");
}