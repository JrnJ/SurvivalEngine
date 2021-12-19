#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include <glm/glm.hpp>
#include "../Renderer/Texture2D.hpp"

struct SpriteRenderer
{
	Texture2D Texture;
	glm::vec4 Color;
	
	// Draw function of some sort
};

#endif