#include "Entity.hpp"

Entity::Entity() 
	: Velocity(glm::vec2(0.0f, 0.0f)), Mass(1.0f), MaxHealth(20.0f), Health(20.0f),
	GameObject::GameObject(),
	collider(1)
{

}

Entity::Entity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
	: Velocity(glm::vec2(0.0f, 0.0f)), Mass(1.0f), MaxHealth(20.0f), Health(20.0f),
	GameObject::GameObject(pos, size, sprite, color),
	collider(1)
{

}

void Entity::Kill()
{
	// Yeah uh, good question
}
