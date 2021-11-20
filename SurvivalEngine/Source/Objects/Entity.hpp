#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "GameObject.hpp"
#include "../Components/Collider.hpp"

class Entity : public GameObject
{
public:
	// Properties
	glm::vec2 Velocity;
	float Mass;
	float Health;
	float MaxHealth; // GET ONLY!!! - for now :D

	Collider Collision;

	// Constructors
	Entity();
	Entity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f));

	// Components

	// Methods
	void Kill();
};

#endif