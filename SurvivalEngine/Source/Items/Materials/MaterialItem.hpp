#ifndef MATERIALITEM_HPP
#define MATERIALITEM_HPP

#include "../Item.hpp"

class MaterialItem : public Item
{
public:
	// Constructor
	MaterialItem(std::string name, std::string id, std::string spritePath, int maxItemStack);
};

#endif