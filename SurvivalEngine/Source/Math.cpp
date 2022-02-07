#include "Math.hpp"

const glm::vec2 Math::Normalize(glm::vec2 vec2)
{
	float magnitude = glm::sqrt(glm::pow(vec2.x, 2) + glm::pow(vec2.y, 2));
	return magnitude != 0 ? glm::vec2(vec2.x / magnitude, vec2.y / magnitude) : glm::vec2(0.0f, 0.0f);
}

/// <summary>
/// Returns the Clamped value between given min and max
/// </summary>
/// <param name="value">Value to be restricted</param>
/// <param name="min">Minimum value</param>
/// <param name="max">Maximum value</param>
/// <returns></returns>
const float Math::Clamp(float value, float min, float max)
{
	if (value < min)
		return min;

	if (value > max)
		return max;

	return value;
}

const float Math::ClampLerp(float value, float min, float max, float increaseMin, float decreaseMax)
{
	if (value < min)
		return value + increaseMin;

	if (value > max)
		return value - decreaseMax;

	return value;
}

const float Math::RadToDeg(float radians)
{
	return radians * 180.0f / Math::PI;
}

const float Math::DegToRad(float degrees)
{
	return degrees * Math::PI / 180.0f;
}