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

	void _Load(const char* file, glm::vec2 screenSize, glm::vec2 blockSize);
	void _Unload();
	void _Save();

	void Generate();
	void Load2D(int blocks[5][5]);
	void Load3D(int blocks[10][10][3]);
};

#endif