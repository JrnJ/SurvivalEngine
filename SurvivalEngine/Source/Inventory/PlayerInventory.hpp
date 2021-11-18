#ifndef PLAYERINVENTORY_HPP
#define PLAYERINVENTORY_HPP

#include "Inventory.hpp"
#include "../Items/Tools/Axes/StoneAxe.hpp"

class PlayerInventory : public Inventory
{
public:
	// Instance
	PlayerInventory()
		: Inventory::Inventory(
			9,
			{ 
				new ItemInstance(new StoneAxe(), 1), 
				new ItemInstance(new Stone(), 33), 
				new ItemInstance(new StoneAxe(), 1),
				new ItemInstance(NULL, 0), 
				new ItemInstance(NULL, 0), 
				new ItemInstance(NULL, 0), 
				new ItemInstance(NULL, 0), 
				new ItemInstance(NULL, 0), 
				new ItemInstance(NULL, 0)
			}
		) {}
};

#endif