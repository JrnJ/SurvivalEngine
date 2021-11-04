#include "Math.h"

glm::vec2 Math::Normalize(glm::vec2 vec2)
{
	float magnitude = glm::sqrt(glm::pow(vec2.x, 2) + glm::pow(vec2.y, 2));
	return magnitude != 0 ? glm::vec2(vec2.x / magnitude, vec2.y / magnitude) : glm::vec2(0.0f, 0.0f);
}

float Math::Dot(glm::vec2 vec2)
{
	// {VAB} * n = (V^vec2.y - V^vec2.x) * n
	return 0.0f;
}