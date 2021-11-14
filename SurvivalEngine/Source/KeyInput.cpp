#include "KeyInput.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

KeyInput::KeyInput()
	: Keys(), PressedKeys(), ScrollX(0), ScrollY(0), MouseButtons(), PressedMouseButtons()
{

}

/// <summary>
/// Returns the state of pressed key
/// </summary>
/// <param name="key">Key to check for</param>
/// <returns></returns>
bool KeyInput::GetKey(int key)
{
	return this->Keys[key];
}

/// <summary>
/// Returns the state of the pressed key, if true the key has to be released to return true again
/// </summary>
/// <param name="key">Key to check for</param>
/// <returns></returns>
bool KeyInput::GetKeyDown(int key)
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



bool KeyInput::GetMouseButton(int button)
{
	return this->MouseButtons[button];
}

bool KeyInput::GetMouseButtonDown(int button)
{
	if (this->MouseButtons[button] && !PressedMouseButtons[button])
	{
		PressedMouseButtons[button] = true;
		return true;
	} return false;
}

bool KeyInput::GetMouseButtonUp(int button)
{
	std::cout << "Not Working!" << std::endl;
	return false;
}
// Mouse //

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
				(float)std::max((int)GetKey(GLFW_KEY_D), (int)GetKey(GLFW_KEY_RIGHT)) -
				(float)std::max((int)GetKey(GLFW_KEY_A), (int)GetKey(GLFW_KEY_LEFT));
		case Axis::Vertical:
			return
				(float)std::max((int)GetKey(GLFW_KEY_S), (int)GetKey(GLFW_KEY_DOWN)) - 
				(float)std::max((int)GetKey(GLFW_KEY_W), (int)GetKey(GLFW_KEY_UP));
		case Axis::MouseScrollWheel:
			return (float)ScrollY;
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