
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "../Source/Scenes/StudioProjectScene.h"
#include "../Source/Scenes/SceneMole.h"
#include "../Source/Scenes/SceneMaze.h"
#include "../Source/Scenes/SceneFrog.h"
#include "../Source/Scenes/SceneTank.h"
#include "../Source/Scenes/Results.h"
#include "../Source/Scenes/SheepGame.h"
#include "../Source/Scenes/SceneMainMenu.h"
GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
int m_width, m_height;
int Application::currentScene;
//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


void resize_callback(GLFWwindow* window, int w, int h)
{
	m_width = w;
	m_height = h;
	glViewport(0, 0, w, h);
}

bool Application::Quit = false;

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}
bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}
void Application::GetCursorPos(double *xpos, double *ypos)
{
	glfwGetCursorPos(m_window, xpos, ypos);
}
int Application::GetWindowWidth()
{
	return m_width;
}
int Application::GetWindowHeight()
{
	return m_height;
}

Application::Application()
{
	currentScene = SCENEMAINMENU;
}

Application::~Application()
{
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL

	//Create a window and create its OpenGL context
	// glfwGetPrimaryMonitor()
	m_width = 1920;
	m_height = 1080;
	
	m_window = glfwCreateWindow(m_width, m_height, "Studio Project 3", NULL, NULL);
	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread.
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);
	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

}

void Application::Run()
{
	//Main Loop
	Scene* thisScene[TOTALSCENES];
	thisScene[SCENEMAIN] = new StudioProjectScene;
	thisScene[SCENEMAZE] = new SceneMaze;
	thisScene[SCENEMOLE] = new SceneMole;
	thisScene[SCENETANK] = new SceneTank;
	thisScene[SCENEFROG] = new SceneFrog;
	thisScene[SCENESHEEP] = new SheepGame;
	thisScene[SCENEMAINMENU] = new MainMenu;

	for (int i = 0; i < TOTALSCENES; ++i)
	{
		if (thisScene[i])
		{
			thisScene[i]->Init();
		}
	}
	Scene* currentscene = thisScene[currentScene];
	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !IsKeyPressed(VK_ESCAPE) && !Application::Quit)
	{
		thisScene[currentScene]->Update(m_timer.getElapsedTime());
		thisScene[currentScene]->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.

	} //Check if the ESC key had been pressed or if the window had been closed
	for (int i = 0; i < TOTALSCENES; ++i)
	{
		if (thisScene[i])
		{
			thisScene[i]->Exit();
		}
		delete thisScene[i];
	}
	//delete[] scene;
}
void Application::setScene(int i)
{
	currentScene = i;
}


void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
