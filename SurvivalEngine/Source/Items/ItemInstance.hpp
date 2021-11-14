#ifndef ITEMINSTANCE_HPP
#define ITEMINSTANCE_HPP

#include "Items.hpp"

class ItemInstance
{
public:
	// Variables
	Item* _item;
	int _amount;

	// Constructor
	ItemInstance(Item* item, int amount);

	// Methods
	void SetInstance(ItemInstance itemInstance);
	void ClearInstance();
	void SetAmount(int amount);

	// Getters

private:
	
};

#endif