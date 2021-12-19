#ifndef COWENTITY_HPP
#define COWENTITY_HPP

#include "EntityOld.hpp"

class CowEntity : public EntityOld
{
public:
	// Constructors
	CowEntity();
	CowEntity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f));
};

#endif 



