#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "ECS/Types.hpp"

class World
{
public:
	// Entities with a Rigidbody
	//std::vector<Entity> Entities;

	// Players in the World
	//Entity Player;

	//              z  x  y
	//             [z] [x] [y]
	//int WorldBlocks[10][10][3];
	const int x = 10;
	const int y = 3;
	const int z = 10;

	std::vector<std::vector<std::vector<Entity>>> WorldVector;

	World();

	void Generate();
	void Load3D(std::vector<std::vector<std::vector<int>>> world);

	void SetBlock(int x, int y, int z);
};

#endif