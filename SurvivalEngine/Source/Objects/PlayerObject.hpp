#ifndef PLAYEROBJECT_HPP
#define PLAYEROBJECT_HPP

#include "GameObject.hpp"

class PlayerObject : public GameObject
{
public:
	glm::vec2 Velocity;
	// Bounciness
	float Restitution;
	bool CanJump;

	// Constrcutors
	PlayerObject();
	PlayerObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity = glm::vec2(0.0f, 0.0f), glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

	// Methods
	void Jump();
};

#endif