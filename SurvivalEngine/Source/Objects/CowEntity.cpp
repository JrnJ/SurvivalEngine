#include "CowEntity.hpp"

CowEntity::CowEntity()
	: EntityOld::EntityOld()
{

}

CowEntity::CowEntity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color)
	: EntityOld::EntityOld(pos, size, sprite, color)
{

}
