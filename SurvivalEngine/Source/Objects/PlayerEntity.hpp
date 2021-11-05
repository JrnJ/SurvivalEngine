#ifndef PLAYERENTITY_HPP
#define PLAYERENTITY_HPP

#include "Entity.hpp"

class PlayerEntity : public Entity
{
private:
	const float _maxHealth = 20.0f;
public:
	// Constrcutors
	PlayerEntity();
	PlayerEntity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
};

#endif