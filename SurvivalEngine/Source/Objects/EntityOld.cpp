#include "EntityOld.hpp"

EntityOld::EntityOld()
	: Velocity(glm::vec2(0.0f, 0.0f)), Mass(1.0f), MaxHealth(20.0f), Health(20.0f), 
	GameObject::GameObject()
{

}

EntityOld::EntityOld(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color)
	: Velocity(glm::vec2(0.0f, 0.0f)), Mass(1.0f), MaxHealth(20.0f), Health(20.0f),
	GameObject::GameObject(pos, size, sprite, color) 
{

}

void EntityOld::Kill()
{
	// Yeah uh, good question
	delete this;
}
