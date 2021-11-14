#ifndef TOOLITEM_HPP
#define TOOLITEM_HPP

#include "../Item.hpp"

class ToolItem : public Item
{
public:
	// Constructor
	ToolItem(std::string name, std::string id, std::string spritePath, int maxItemStack, 
		int maxDurability, int durability);

	// Overrides
	virtual void LeftClick() override;

	// Methods
	void RemoveDurability(int amount);

private:
	// Properties
	int _maxDurability;
	int _durability;
};

#endif