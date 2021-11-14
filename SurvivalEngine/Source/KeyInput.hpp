#ifndef INPUT_HPP
#define INPUT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

enum class KeyCode 
{
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	Alpha0, Alpha1, Alpha2, Alpha3, Alpha4, Alpha5, Alpha6, Alpha7, Alpha8, Alpha9,
	Escape, Tab, Backspace, Enter, CapsLock, Space, 
	LeftShift, RightShift, LeftCtrl, RightCtrl, LeftAlt, RightAlt,
	ArrowUp, ArrowDown, ArrowLeft, ArrowRight,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
};

enum class Axis
{
	Horizontal, 
	Vertical,
	MouseScrollWheel
};

class KeyInput
{
public:
	// Properties
	bool Keys[1024];
	bool PressedKeys[1024];

	bool MouseButtons[1024];
	bool PressedMouseButtons[1024];

	double ScrollX;
	double ScrollY;

	// Constructor
	KeyInput();

	// Methods
	// Keyboard
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);

	// Mouse
	bool GetMouseButton(int button);
	bool GetMouseButtonDown(int button);
	bool GetMouseButtonUp(int button);

	// Axis
	float GetAxis(Axis axis);
	float GetAxisRaw(Axis axis);
	float GetCustomAxisRaw(int negative, int positive);
};

#endif