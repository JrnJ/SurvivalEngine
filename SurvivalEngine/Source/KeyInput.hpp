#ifndef KEYINPUT_HPP
#define KEYINPUT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Math.hpp"

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

namespace KeyInput
{
	// Properties
	extern bool Keys[1024];
	extern bool PressedKeys[1024];

	extern bool MouseButtons[1024];
	extern bool PressedMouseButtons[1024];

	extern double ScrollX;
	extern double ScrollY;

	extern double MouseX;
	extern double MouseY;
	extern Math::Vector2 MousePosition;

	// Methods
	// Keyboard
	const bool GetKey(int key);
	const bool GetKeyDown(int key);
	const bool GetKeyUp(int key);

	// Mouse
	const bool GetMouseButton(int button);
	const bool GetMouseButtonDown(int button);
	const bool GetMouseButtonUp(int button);
	const Math::Vector2 MouseToWorldPos();

	// Axis
	const float GetAxis(Axis axis);
	const float GetAxisRaw(Axis axis);
	const float GetCustomAxisRaw(int negative, int positive);
}

#endif