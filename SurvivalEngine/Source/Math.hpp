#ifndef MATH_HPP
#define MATH_HPP

#include <glm/glm.hpp>

namespace Math 
{
	const float PI = 3.14159265359f;

	const glm::vec2 Normalize(glm::vec2 vec2);

	// Degrees
	const float RadToDeg(float radians);
	const float DegToRad(float degrees);
}

#endif