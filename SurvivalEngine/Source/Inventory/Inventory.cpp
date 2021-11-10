#include "Inventory.hpp"

#include <iostream>

Inventory::Inventory(int slotAmount, std::vector<int> slots)
	: SlotAmount(slotAmount), Slots(slots)
{
	
}

void Inventory::Test()
{

}

void Inventory::DisplayInventory()
{
	std::cout << "==[ Inventory ]==" << std::endl;
	for (int i = 0; i < Slots.size(); i++)
	{
		std::cout << "Slot " << i << ": " << Slots[i] << std::endl;
	}
	std::cout << "==[ /Inventory ]==" << std::endl;
}
