#include "ToolItem.hpp"

ToolItem::ToolItem(std::string name, std::string id, std::string spritePath, int maxItemStack,
	int maxDurability, int durability)
	: _maxDurability(maxDurability), _durability(durability),
		Item::Item(name, id, spritePath, maxItemStack)
{

}

// Overrides
void ToolItem::LeftClick()
{
	std::cout << "ToolItem" << std::endl;

	RemoveDurability(1);

	Item::LeftClick();
}


void ToolItem::RemoveDurability(int amount)
{
	_durability -= amount;
	std::cout << Name << " Durability: " << _durability << std::endl;

	if (_durability <= 0)
	{
		// Make the tool break
		std::cout << "Tool broke!" << std::endl;
	}
}
