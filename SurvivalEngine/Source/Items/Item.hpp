#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>

class Item
{
public:
	// Variables
	std::string Name;
	std::string Id;
	std::string SpritePath; // C:/Dev/Resources/SurvivalEngine/textures/Items/

	int MaxItemStack;

	// Constructor
	Item(std::string name, std::string id, std::string spritePath, int maxItemStack);

	// Methods
	virtual void LeftClick();
};


#endif