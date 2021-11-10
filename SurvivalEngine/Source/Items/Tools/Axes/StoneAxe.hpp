#ifndef STONEAXE_HPP
#define STONEAXE_HPP

#include "../ToolItem.hpp"

class StoneAxe : public ToolItem
{
public:
	StoneAxe()
		: ToolItem::ToolItem(
			"Stone Axe",
			"stone_axe",
			"C:/Dev/Resources/SurvivalEngine/textures/Items/Tools/Axes/stone_axe.png",
			100,
			100
		) { }

	// Properties
	const float ShatterChance = 1.0f;

	// Overrides
	void LeftClick() override;
};

#endif