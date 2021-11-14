#ifndef STONE_HPP
#define STONE_HPP

#include "../MaterialItem.hpp"

class Stone : public MaterialItem
{
public:
	Stone()
		: MaterialItem::MaterialItem(
			"Stone",
			"stone",
			"C:/Dev/Resources/SurvivalEngine/Textures/"
		) {}
};

#endif