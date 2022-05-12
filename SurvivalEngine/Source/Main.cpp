#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.hpp"
#include "ResourceManager.hpp"

#include "KeyInput.hpp"

#include <iostream>

// Utility Methods
void write_fps_to_window_title(GLFWwindow* window);

// GL Debugging
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_move_callback(GLFWwindow* window, double cursorX, double cursorY);
void window_size_callback(GLFWwindow* window, int width, int height);

// Aspect ratio = 16:9
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;
//const unsigned int SCREEN_WIDTH = 640;
//const unsigned int SCREEN_HEIGHT = 360;
//const unsigned int SCREEN_WIDTH = 1920;
//const unsigned int SCREEN_HEIGHT = 1080;

Game Survival(SCREEN_WIDTH, SCREEN_HEIGHT);

int nbFrames = 0;
double lastTime = 0.00;

int main(int argc, char* argv[])
{
	std::cout << "Starting Engine..." << std::endl;

	// Initialize Window
	std::cout << "Initializing Window" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, true);
	//glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
	//glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

	// Create Window
	std::cout << "Creating Window..." << std::endl;

	// Normal
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Survival Engine", NULL, NULL);

	// Fullscreen
	int count = 2;
	GLFWmonitor** monitors = glfwGetMonitors(&count);

	//GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Platformer Engine", monitors[1], NULL);
	glfwMakeContextCurrent(window);
	// Disable VSYNC
	//glfwSwapInterval(0);

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
	glfwSetWindowSizeCallback(window, window_size_callback);

	// Configurate OpenGL
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_BLEND);
	glEnable(GL_DEBUG_OUTPUT);

	glDebugMessageCallback(MessageCallback, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClearColor(0.13f, 0.56f, 0.56f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Survival.Render(deltaTime);

		// Reset scrollwheel
		KeyInput::ScrollX = 0;
		KeyInput::ScrollY = 0;

		write_fps_to_window_title(window);
		glfwSwapBuffers(window);
	}

	// When window is closed this will run
	ResourceManager::Clear();
	glfwTerminate();

	std::cout << "Window and Resources Closed" << std::endl;
	return 0;
}

// Utility Methods
void write_fps_to_window_title(GLFWwindow* window)
{
	// Measure Window Speed
	double currentTime = glfwGetTime();
	double delta = currentTime - lastTime;
	nbFrames++;
	if (delta >= 1.0) { // If last cout was more than 1 sec ago
		//std::cout << 1000.0 / double(nbFrames) << std::endl;

		double fps = double(nbFrames) / delta;

		std::string ss = "Survival Engine [ " + std::to_string(fps) + "FPS]";

		glfwSetWindowTitle(window, ss.c_str());

		nbFrames = 0;
		lastTime = currentTime;
	}
}

// GL Debugging
void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cout << "GL CALLBACK: type = " << type << ", severity = " << severity << ", message = " << message << std::endl << std::endl;
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

	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		glfwSetWindowSize(window, 640, 360);
	}	

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

void window_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	Survival.WindowResized(width, height);
}
