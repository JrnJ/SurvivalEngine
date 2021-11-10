#include "Item.hpp"

Item::Item(std::string name, std::string id, std::string spritePath)
	: Name(name), Id(id), SpritePath(spritePath)
{

}

void Item::LeftClick()
{
	std::cout << "Item" << std::endl;
}
