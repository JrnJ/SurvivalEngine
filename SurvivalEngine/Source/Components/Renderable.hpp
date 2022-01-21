#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

#include "../Renderer/Texture2D.hpp"
#include <glm/glm.hpp>

struct Renderable
{
	glm::vec2 TexCoords;
	glm::vec4 Color;
};

#endif