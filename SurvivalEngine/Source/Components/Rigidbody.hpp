#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

#include <iostream>

#include <glm/glm.hpp>

#include "Component.hpp"
#include "../Math.hpp"

// Handles more advanced data
// Only objects that move have an Rigidbody
class Rigidbody : public Component
{
public:
	glm::vec2 Velocity;

private:
	// Velocity combined
	float _speed;
};

#endif