#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "ECS/Types.hpp"

class World
{
public:
	// Entities without a Rigidbody
	std::vector<Entity> Blocks;

	// Entities with a Rigidbody
	std::vector<Entity> Entities;

	// Players in the World
	Entity Player;

	void Load(const char* file, glm::vec2 screenSize, glm::vec2 blockSize);
	void Unload();
	void Save();
};

#endif