#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

#include "../Items.hpp"

class Spellbook : public Item
{
public:
	// Constructor
	Spellbook()
		: Item::Item(
			"Spellbook",
			"spellbook",
			"C:/Dev/Resources/SurvivalEngine/textures/Items/Tools/Axes/stone_axe.png",
			1
		) { }

	// Overrides
	virtual void LeftClick() override;

};

#endif
