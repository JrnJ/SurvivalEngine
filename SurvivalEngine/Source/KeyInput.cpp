#include "KeyInput.hpp"

// Instantiate Extern variables
bool KeyInput::Keys[1024];
bool KeyInput::PressedKeys[1024];

bool KeyInput::MouseButtons[1024];
bool KeyInput::PressedMouseButtons[1024];

double KeyInput::ScrollX = 0;
double KeyInput::ScrollY = 0;

double KeyInput::MouseX = 0;
double KeyInput::MouseY = 0;

/// <summary>
/// Returns the state of pressed key
/// </summary>
/// <param name="key">Key to check for</param>
/// <returns></returns>
const bool KeyInput::GetKey(int key)
{
	return KeyInput::Keys[key];
}

/// <summary>
/// Returns the state of the pressed key, if true the key has to be released to return true again
/// </summary>
/// <param name="key">Key to check for</param>
/// <returns></returns>
const bool KeyInput::GetKeyDown(int key)
{
	if (KeyInput::Keys[key] && !PressedKeys[key])
	{
		PressedKeys[key] = true;
		return true;
	} return false;
}

const bool KeyInput::GetKeyUp(int key)
{
	std::cout << "Not Working!" << std::endl;
	return false;
}



const bool KeyInput::GetMouseButton(int button)
{
	return KeyInput::MouseButtons[button];
}

const bool KeyInput::GetMouseButtonDown(int button)
{
	if (KeyInput::MouseButtons[button] && !PressedMouseButtons[button])
	{
		PressedMouseButtons[button] = true;
		return true;
	} return false;
}

const bool KeyInput::GetMouseButtonUp(int button)
{
	std::cout << "Not Working!" << std::endl;
	return false;
}

//const Math::Vector2 KeyInput::MouseToWorldPos()
//{
//	std::cout << "Function not working due to camera now accesible by any object, see comments for info" << std::endl;
//	// Calculation:
//	// return Math::Vector2(KeyInput::MouseX + _camera.GetPosition().x, KeyInput::MouseY + _camera.GetPosition().y); 
//
//	// Camera has to become a namespace in which everything can acces it in order to allow the getting of the camera position
//	// Or create a reference to here from the camera :)
//
//	return { 0.0f, 0.0f };
//}

// Mouse //
const float KeyInput::GetAxis(Axis axis)
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

const float KeyInput::GetAxisRaw(Axis axis)
{
	switch (axis)
	{
	case Axis::Horizontal:
		return
			(float)std::max((int)GetKey(GLFW_KEY_A), (int)GetKey(GLFW_KEY_LEFT)) -
			(float)std::max((int)GetKey(GLFW_KEY_D), (int)GetKey(GLFW_KEY_RIGHT));
	case Axis::Vertical:
		return
			(float)std::max((int)GetKey(GLFW_KEY_W), (int)GetKey(GLFW_KEY_UP)) -
			(float)std::max((int)GetKey(GLFW_KEY_S), (int)GetKey(GLFW_KEY_DOWN));
	case Axis::MouseScrollWheel:
		return (float)ScrollY;
	default:
		std::cout << "Axis not added" << std::endl;
		break;
	}

	return 0.0f;
}

const float KeyInput::GetCustomAxisRaw(int negative, int positive)
{
	return (float)((int)GetKey(positive) - (int)GetKey(negative));
}