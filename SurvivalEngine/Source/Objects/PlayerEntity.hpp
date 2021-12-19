#ifndef PLAYERENTITY_HPP
#define PLAYERENTITY_HPP

#include "EntityOld.hpp"
#include "../Inventory/PlayerInventory.hpp"

class PlayerEntity : public EntityOld
{
private:
	const float _maxHealth = 20.0f;
public:
	// Variables
	int SelectedHotbarSlot = 0;
	PlayerInventory* Inventory;
	
	// Constrcutors
	PlayerEntity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color = glm::vec4(1.0f));
	~PlayerEntity();

	// Overrides
	virtual void Input(float dt);
	virtual void Update(float dt);
};

#endif