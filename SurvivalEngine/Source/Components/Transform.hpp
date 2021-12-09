#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <iostream>

#include <glm/glm.hpp>

#include "Component.hpp"
#include "../Math.hpp"

// Handles super basic object data
// Every GameObject has a Transform
class Transform : public Component
{
public:
	glm::vec2 Position;
	float Rotation;
	glm::vec2 Scale;

private:


};

#endif