#include "CowEntity.hpp"

CowEntity::CowEntity()
	: Entity::Entity()
{

}

CowEntity::CowEntity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color)
	: Entity::Entity(pos, size, sprite, color)
{

}
