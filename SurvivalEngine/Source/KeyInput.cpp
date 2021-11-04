#include "KeyInput.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

KeyInput::KeyInput()
	: Keys(), PressedKeys()
{

}

bool KeyInput::GetKey(int key)
{
	if (this->Keys[key] && !PressedKeys[key])
	{
		PressedKeys[key] = true;
		return true;
	} return false;
}

bool KeyInput::GetKeyUp(int key)
{
	std::cout << "Not Working!" << std::endl;
	return false;
}

bool KeyInput::GetKeyDown(int key)
{
	return this->Keys[key];
}

float KeyInput::GetAxis(Axis axis)
{
	switch (axis)
	{
		case Axis::Horizontal:
			return (float)((int)GetKeyDown(GLFW_KEY_D) - (int)GetKeyDown(GLFW_KEY_A));
		case Axis::Vertical:
			return (float)((int)GetKeyDown(GLFW_KEY_S) - (int)GetKeyDown(GLFW_KEY_W));
		default:
			std::cout << "Axis not added" << std::endl;
			break;
	}

	return 0.0f;
}