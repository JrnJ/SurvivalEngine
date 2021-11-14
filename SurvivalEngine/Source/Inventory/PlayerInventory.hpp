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
				new StoneAxe(), new Stone(), new StoneAxe(),
				NULL, NULL, NULL, NULL, NULL, NULL 
			}
		) {}
};

#endif