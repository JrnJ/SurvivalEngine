#include "KeyInput.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

			break;
		case Axis::Vertical:

			break;
	}

	std::cout << "FUNCTION NOT WORKING! Use GetAxisRaw instead!" << std::endl;

	return 0.0f;
}

float KeyInput::GetAxisRaw(Axis axis)
{
	switch (axis)
	{
		case Axis::Horizontal:
			return 
				(float)std::max((int)GetKeyDown(GLFW_KEY_D), (int)GetKeyDown(GLFW_KEY_RIGHT)) - 
				(float)std::max((int)GetKeyDown(GLFW_KEY_A), (int)GetKeyDown(GLFW_KEY_LEFT));
		case Axis::Vertical:
			return
				(float)std::max((int)GetKeyDown(GLFW_KEY_S), (int)GetKeyDown(GLFW_KEY_DOWN)) -
				(float)std::max((int)GetKeyDown(GLFW_KEY_W), (int)GetKeyDown(GLFW_KEY_UP));
		default:
			std::cout << "Axis not added" << std::endl;
			break;
	}

	return 0.0f;
}

float KeyInput::GetCustomAxisRaw(int negative, int positive)
{
	return (float)((int)GetKeyDown(negative) - (int)GetKeyDown(positive));
}