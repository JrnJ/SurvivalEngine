#ifndef MATH_H
#define MATH_H

#include <glm/glm.hpp>

class Math
{
public:
	// Methods
	static glm::vec2 Normalize(glm::vec2 vec2);
	static float Dot(glm::vec2 vec2);
};

#endif