#include "PlayerObject.hpp"

PlayerObject::PlayerObject()
	: Velocity(glm::vec2(0.0f, 0.0f)), Restitution(0.0f), CanJump(false),
	GameObject::GameObject()
{

}

PlayerObject::PlayerObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec2 velocity, glm::vec3 color)
	: Velocity(velocity), Restitution(0.0f), CanJump(false),
	GameObject::GameObject(pos, size, sprite, color)
{

}

void PlayerObject::Jump()
{
	if (CanJump)
	{
		// Jump Logic
		this->Velocity.y -= 10000.0f;
	}
}