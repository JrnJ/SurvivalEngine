#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include "../Items/ItemInstance.hpp"
#include <vector>

class Inventory
{
public:
	// Properties
	int SlotAmount;
	std::vector<ItemInstance*> Slots;

	// Constructor
	Inventory(int slotAmount, std::vector<ItemInstance*> items);

	// Methods
	void AddItem(ItemInstance*);
	void SetItemAt(ItemInstance*);
	void AddAmountToItem(int index, int amount);
	void RemoveAmountFromItem(int index, int amount);
	const void ClearInventory() { Slots.clear(); }

	// UI Methods
	void DisplayInventory();

private:


};

#endif