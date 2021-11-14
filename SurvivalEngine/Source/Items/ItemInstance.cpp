#include "ItemInstance.hpp"

ItemInstance::ItemInstance(Item* item, int amount)
	: _item(item), _amount(amount)
{

}

void ItemInstance::SetInstance(ItemInstance itemInstance)
{
	this->_item = itemInstance._item;
	this->_amount = itemInstance._amount;
}

void ItemInstance::ClearInstance()
{
	this->_item = NULL;
	this->_amount = 0;
}

void ItemInstance::SetAmount(int amount)
{
	this->_amount = amount;
}
