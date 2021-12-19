#include "PlayerEntity.hpp"
#include "../Math.hpp"
#include "../KeyInput.hpp"

PlayerEntity::PlayerEntity(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color)
	: EntityOld::EntityOld(pos, size, sprite, color)
{
	this->Inventory = new PlayerInventory();
}

PlayerEntity::~PlayerEntity()
{
	delete Inventory;
}

void PlayerEntity::Input(float dt)
{
	// Movement
	float horizontal = KeyInput::GetAxisRaw(Axis::Horizontal);
	float vertical = KeyInput::GetAxisRaw(Axis::Vertical);
	this->Velocity = Math::Normalize(glm::vec2(horizontal, vertical)) * 300.0f;

	// Check for Inventory things
	if (KeyInput::GetKeyDown(GLFW_KEY_1))
		this->SelectedHotbarSlot = 0;
	if (KeyInput::GetKeyDown(GLFW_KEY_2))
		this->SelectedHotbarSlot = 1;
	if (KeyInput::GetKeyDown(GLFW_KEY_3))
		this->SelectedHotbarSlot = 2;
	if (KeyInput::GetKeyDown(GLFW_KEY_4))
		this->SelectedHotbarSlot = 3;
	if (KeyInput::GetKeyDown(GLFW_KEY_5))
		this->SelectedHotbarSlot = 4;
	if (KeyInput::GetKeyDown(GLFW_KEY_6))
		this->SelectedHotbarSlot = 5;
	if (KeyInput::GetKeyDown(GLFW_KEY_7))
		this->SelectedHotbarSlot = 6;
	if (KeyInput::GetKeyDown(GLFW_KEY_8))
		this->SelectedHotbarSlot = 7;
	if (KeyInput::GetKeyDown(GLFW_KEY_9))
		this->SelectedHotbarSlot = 8;

	// Got to reset to 0 if not scrolling idk how tbh
	if (KeyInput::GetAxisRaw(Axis::MouseScrollWheel) > 0)
		SelectedHotbarSlot = SelectedHotbarSlot <= 0 ? 8 : SelectedHotbarSlot - 1;
	else if (KeyInput::GetAxisRaw(Axis::MouseScrollWheel) < 0)
		SelectedHotbarSlot = SelectedHotbarSlot >= 8 ? 0 : SelectedHotbarSlot + 1;

	//if (KeyInput::GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
	//	if (this->Inventory->Slots[SelectedHotbarSlot]->_item != NULL)
	//		this->Inventory->Slots[SelectedHotbarSlot]->_item->LeftClick();

	if (KeyInput::GetKeyDown(GLFW_KEY_M))
	{
		this->Inventory->AddItem(new ItemInstance(new Stone(), 300));
	}
	if (KeyInput::GetKeyDown(GLFW_KEY_N))
	{
		this->Inventory->AddItem(new ItemInstance(new StoneAxe(), 1));
	}

	if (KeyInput::GetKeyDown(GLFW_KEY_E))
	{
		this->Inventory->DisplayInventory(SelectedHotbarSlot);
	}
}

void PlayerEntity::Update(float dt)
{
	this->Position += this->Velocity * dt;

	// There is no GameObject::LeftClick(); 
	// here as there is no use for it
}