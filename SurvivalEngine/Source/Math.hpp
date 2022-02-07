#ifndef MATH_HPP
#define MATH_HPP

#include <glm/glm.hpp>

namespace Math 
{
	const float PI = 3.14159265359f;

	const glm::vec2 Normalize(glm::vec2 vec2);
	const float Clamp(float value, float min, float max);
	const float ClampLerp(float value, float min, float max, float increaseMin, float decreaseMax);

	// Degrees
	const float RadToDeg(float radians);
	const float DegToRad(float degrees);

	// Types
	struct Vector2
	{
		float x;
		float y;
	};

	struct Vector3
	{
		float x;
		float y;
		float z;
	};
}

#endif