#include "PlayerEntity.hpp"

PlayerEntity::PlayerEntity()
	: Entity::Entity()
{

}

PlayerEntity::PlayerEntity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
	: Entity::Entity(pos, size, sprite, color)
{

}