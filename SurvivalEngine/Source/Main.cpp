#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.hpp"
#include "ResourceManager.hpp"

#include "KeyInput.hpp"

#include <iostream>

// GL Debugging
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);

	std::cout << std::endl;
}

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_move_callback(GLFWwindow* window, double cursorX, double cursorY);

const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;
//const unsigned int SCREEN_WIDTH = 1920;
//const unsigned int SCREEN_HEIGHT = 1080;

Game Survival(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
	std::cout << "Starting Engine..." << std::endl;

	// Initialize Window
	std::cout << "Initializing Window" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, false);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

	// Create Window
	std::cout << "Creating Window..." << std::endl;

	// Normal
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Survival Engine", NULL, NULL);

	// Fullscreen
	int count = 2;
	GLFWmonitor** monitors = glfwGetMonitors(&count);

	//GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Platformer Engine", monitors[1], NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	// Load Glad with OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	std::cout << "Window created succesfully" << std::endl;

	// Set GLFW callbacks
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, cursor_move_callback);

	// Configurate OpenGL
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_BLEND);
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize Game
	Survival.Init();
	std::cout << "Initialized Game" << std::endl;

	// deltaTime variables
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	// Game Loop
	while (!glfwWindowShouldClose(window))
	{
		// Calculate deltaTime
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// Logical Game Loop == Input -> Update -> Render
		// Input
		Survival.ProcessInput(deltaTime);

		// Update
		Survival.Update(deltaTime);

		// Render
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClearColor(0.13f, 0.56f, 0.56f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Survival.Render();

		// Reset scrollwheel
		KeyInput::ScrollX = 0;
		KeyInput::ScrollY = 0;

		glfwSwapBuffers(window);
	}

	// When window is closed this will run
	ResourceManager::Clear();
	glfwTerminate();

	std::cout << "Window and Resources Closed" << std::endl;
	return 0;
}

// GLFW Callbacks
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Close window on escape press
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Keyboard
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			KeyInput::Keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			KeyInput::Keys[key] = false;
			KeyInput::PressedKeys[key] = false;
		}
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button >= 0 && button < 1024)
	{
		if (action == GLFW_PRESS)
		{
			KeyInput::MouseButtons[button] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			KeyInput::MouseButtons[button] = false;
			KeyInput::PressedMouseButtons[button] = false;
		}
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Mouse Scrollwheel
	KeyInput::ScrollX = xoffset;
	KeyInput::ScrollY = yoffset;
}

void cursor_move_callback(GLFWwindow* window, double cursorX, double cursorY)
{
	KeyInput::MouseX = cursorX;
	KeyInput::MouseY = cursorY;
}
