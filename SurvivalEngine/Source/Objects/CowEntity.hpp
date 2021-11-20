#ifndef COWENTITY_HPP
#define COWENTITY_HPP

#include "Entity.hpp"

class CowEntity : public Entity
{
public:
	// Constructors
	CowEntity();
	CowEntity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f));
};

#endif 



