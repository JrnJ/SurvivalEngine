#include "Math.hpp"

const glm::vec2 Math::Normalize(glm::vec2 vec2)
{
	float magnitude = glm::sqrt(glm::pow(vec2.x, 2) + glm::pow(vec2.y, 2));
	return magnitude != 0 ? glm::vec2(vec2.x / magnitude, vec2.y / magnitude) : glm::vec2(0.0f, 0.0f);
}

const float Math::RadToDeg(float radians)
{
	return radians * 180.0f / Math::PI;
}

const float Math::DegToRad(float degrees)
{
	return degrees * Math::PI / 180.0f;
}