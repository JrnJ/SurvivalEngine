#include "Inventory.hpp"

#include <iostream>

Inventory::Inventory(int slotAmount, std::vector<ItemInstance*> slots)
	: SlotAmount(slotAmount), Slots(slots)
{

}

/// <summary>
/// Adds an Item to the Inventory
/// </summary>
/// <param name="itemInstance">Item to add</param>
void Inventory::AddItem(ItemInstance* itemInstance)
{
	for (int i = 0; i < SlotAmount; i++)
	{
		// If MaxItemStack is 1, dont look for same item
		if (itemInstance->_item->MaxItemStack > 1)
		{
			// Firstly, check if the item is already present
			if (Slots[i]->_item != NULL)
			{
				if (itemInstance->_item->Id == Slots[i]->_item->Id)
				{
					// Later on, check for names and stuff to make sure its the same thing
					itemInstance->SetAmount(FillItemStack(i, itemInstance->_amount));
				}
			}
		}
		else
		{
			if (Slots[i]->_item == NULL)
			{
				Slots[i]->SetInstance(itemInstance);
				return;
			}
		}
	}

	// Check if amount is greater than 0
	if (itemInstance->_amount > 0)
	{
		for (int i = 0; i < SlotAmount; i++)
		{
			// Check if slot is free
			if (Slots[i]->_item == NULL)
			{
				// Calculate max amount to add
				int maxAmountToAdd = itemInstance->_item->MaxItemStack;

				// Check if amount can fit in the slot
				if (itemInstance->_amount <= maxAmountToAdd)
				{
					Slots[i]->SetInstance(itemInstance);
					itemInstance->SetAmount(0);
					break;
				}
				else
				{
					// Calculate leftover
					int leftover = itemInstance->_amount - maxAmountToAdd;
					Slots[i]->SetInstance(itemInstance);
					itemInstance->SetAmount(leftover);
				}
			}
		}

		// Check if there are leftovers
		if (itemInstance->_amount > 0)
		{
			// Drop these items
			std::cout << "Dropped " << itemInstance->_amount << " of ItemType: " << itemInstance->_item->Name << std::endl;
		}
	}
}

/// <summary>
/// Sets an Item at an index in the Inventory
/// </summary>
/// <param name="itemInstance">Item to set</param>
/// <param name="index">Items to set at</param>
void Inventory::SetItemAt(ItemInstance* itemInstance, int index)
{
	Slots[index]->SetInstance(itemInstance);
}

/// <summary>
/// Adds an amount to an Item at an index
/// </summary>
/// <param name="index">Where to add</param>
/// <param name="amount">Amount to add</param>
void Inventory::AddAmountToItem(int index, int amount)
{
	Slots[index]->AddAmount(amount);
}

/// <summary>
/// Removes an amount from an Item at an index
/// </summary>
/// <param name="index">Where to remove</param>
/// <param name="amount">Amount to remove</param>
void Inventory::RemoveAmountFromItem(int index, int amount)
{
	Slots[index]->RemoveAmount(amount);
}

void Inventory::DisplayInventory(int selectedSlot)
{
	std::cout << "==[ Inventory ]==" << std::endl;
	for (int i = 0; i < SlotAmount; i++)
	{
		if (i == selectedSlot)
			std::cout << "SELECTED => ";

		if (Slots[i]->_item != NULL)
		{
			std::cout << "Slot " << i << ": " << Slots[i]->_amount << "x " << Slots[i]->_item->Name << std::endl;
		}
		else
		{
			std::cout << "Slot " << i << ": " << std::endl;
		}
	}
	std::cout << "==[ /Inventory ]==" << std::endl;
}

// Private methods

/// <summary>
/// Fills an Item to its maximum stack
/// </summary>
/// <param name="index">Index in Inventory</param>
/// <param name="amount">Given amount</param>
/// <returns>Amount leftover</returns>
int Inventory::FillItemStack(int index, int amount)
{
	// Calculate max amount to add
	int maxAmountToAdd = Slots[index]->_item->MaxItemStack - Slots[index]->_amount;

	// If 0, return with amount
	if (maxAmountToAdd == 0)
		return amount;

	// Check if amount can fit in the slot
	if (amount <= maxAmountToAdd)
	{
		// Add amount and return 0
		Slots[index]->AddAmount(amount);

		return 0;
	}
	else
	{
		// Calculate leftover
		int leftover = Slots[index]->_amount + amount - Slots[index]->_item->MaxItemStack;
		// Fill stack
		Slots[index]->SetAmount(Slots[index]->_item->MaxItemStack);

		return leftover;
	}
}
