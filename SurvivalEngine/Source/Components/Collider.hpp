#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <iostream>
#include "../Objects/GameObject.hpp"

class Collider
{
public:
	// Properties
	//GameObject Self;

	// Constructor
	Collider();

	// Methods
	void DoCollision(GameObject& target);
};

#endif