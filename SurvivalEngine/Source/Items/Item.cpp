#include "Item.hpp"

Item::Item(std::string name, std::string id, std::string spritePath, int maxItemStack)
	: Name(name), Id(id), SpritePath(spritePath), MaxItemStack(maxItemStack)
{

}

void Item::LeftClick()
{
	std::cout << "Item" << std::endl;
}
