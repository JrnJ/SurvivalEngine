#ifndef COWENTITY_HPP
#define COWENTITY_HPP

#include "Entity.hpp"

class CowEntity : public Entity
{
public:
	// Constructors
	CowEntity();
	CowEntity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
};

#endif 



