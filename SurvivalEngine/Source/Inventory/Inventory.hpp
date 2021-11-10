#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "../Items/Item.hpp"
#include <vector>

class Inventory
{
public:
	// Properties
	int SlotAmount;
	std::vector<Item*> Slots;

	// Constructor
	Inventory(int slotAmount, std::vector<Item*> items);

	// Methods
	void AddItem(Item item, int amount);
	void SetItemAt(Item item, int amount);
	void AddAmountToItem(int index, int amount);
	void RemoveAmountFromItem(int index, int amount);
	const void ClearInventory() { Slots.clear(); }

	// UI Methods
	void DisplayInventory();

private:


};

#endif