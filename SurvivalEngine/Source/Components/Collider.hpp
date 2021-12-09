#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include <iostream>
#include "Component.hpp"
#include "../Objects/GameObject.hpp"

class Collider : public Component
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