#ifndef ANIMATABLE_HPP
#define ANIMATABLE_HPP

#include "../Renderer/Texture2D.hpp"
#include "Renderable.hpp"
#include <glm/glm.hpp>
#include <vector>

struct Animatable
{
	float TimeBetweenAnimations;
	std::vector<Renderable> Sprites;

	float UpdateAt = 0.0f;
	int CurrentSprite = 0;
};

#endif