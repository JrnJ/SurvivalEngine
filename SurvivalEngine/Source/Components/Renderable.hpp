#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include <glm/glm.hpp>
#include "../Renderer/Texture2D.hpp"

struct Renderable
{
	Texture2D Texture;
	glm::vec4 Color;
	
	// Draw function of some sort
};

#endif