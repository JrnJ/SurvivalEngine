#include "Inventory.hpp"

#include <iostream>

Inventory::Inventory(int slotAmount, std::vector<ItemInstance*> slots)
	: SlotAmount(slotAmount), Slots(slots)
{
	
}

/// <summary>
/// Adds an Item to the Inventory
/// </summary>
/// <param name="item">Item to add</param>
/// <param name="amount">Amount of item</param>
void Inventory::AddItem(ItemInstance* itemInstance)
{
	for (int i = 0; i < SlotAmount; i++)
	{
		if (Slots[i] == NULL)
		{
			Slots[i] = itemInstance;
			return;
		}
	}
}

/// <summary>
/// Sets an Item at an index in the Inventory
/// </summary>
/// <param name="item">Item to set</param>
/// <param name="amount">Amount of item</param>
void Inventory::SetItemAt(ItemInstance* itemInstance)
{

}

/// <summary>
/// Adds an amount to an Item at an index
/// </summary>
/// <param name="index">Where to add</param>
/// <param name="amount">Amount to add</param>
void Inventory::AddAmountToItem(int index, int amount)
{
}

/// <summary>
/// Removes an amount from an Item at an index
/// </summary>
/// <param name="index">Where to remove</param>
/// <param name="amount">Amount to remove</param>
void Inventory::RemoveAmountFromItem(int index, int amount)
{

}

void Inventory::DisplayInventory()
{
	std::cout << "==[ Inventory ]==" << std::endl;
	for (int i = 0; i < SlotAmount; i++)
	{
		if (Slots[i] != NULL)
		{
			std::cout << "Slot " << i << ": " << Slots[i]->_amount << "x " << Slots[i]->_item->Name << std::endl;
		}
	}
	std::cout << "==[ /Inventory ]==" << std::endl;
}
