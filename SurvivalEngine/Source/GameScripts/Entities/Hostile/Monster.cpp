#include "Monster.hpp"

Monster::Monster()
	: _hp(100)
{

}

Monster::~Monster()
{

}

void Monster::RemoveHP(int amount)
{
	_hp -= amount;

	if (_hp <= 0)
	{
		// Kill enemy
	}
}
