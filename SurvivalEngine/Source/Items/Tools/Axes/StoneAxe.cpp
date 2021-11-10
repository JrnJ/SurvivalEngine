#include "StoneAxe.hpp"

// Overrides
void StoneAxe::LeftClick()
{
	std::cout << "StoneAxe" << std::endl;

	// Call void below
	ToolItem::LeftClick();
}