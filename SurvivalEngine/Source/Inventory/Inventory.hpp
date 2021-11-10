#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "../Items/Item.hpp"
#include <vector>

class Inventory
{
public:
	// Properties
	int SlotAmount;
	std::vector<int> Slots;

	// Constructor
	Inventory(int slotAmount, std::vector<int> items);

	// Methods
	void DisplayInventory();

	// beta:
	void Test();

private:


};

#endif