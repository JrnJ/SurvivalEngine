#include "World.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Random.hpp"
#include "ECS/Coordinator.hpp"
#include "Components/Components.hpp"
#include "ResourceManager.hpp"

extern Coordinator _coordinator;

World::World()
	: WorldVector(this->z, std::vector<std::vector<Entity>>(this->x))
{
	// WorldVector(this->z, std::vector<std::vector<Entity>>(this->x, std::vector<Entity>(this->y)));
}

void World::Generate()
{
	// x: 5
	// y: 3
	// z: 5

	// 0 = air
	// 3 = red dot
	// 2 = grass
	// 1 = dirt

	// Clear Existing
	/*for (auto& entity : this->Blocks)
	{
		_coordinator.DestroyEntity(entity);
	}
	this->Blocks.clear();*/

	//this->WorldVector.clear();
	//std::vector<std::vector<std::vector<int>>> vec3d(10, std::vector<std::vector<int>>(10, std::vector<int>(3)));
	//WorldVector = vec3d;

	std::vector<std::vector<std::vector<int>>> newWorld(this->z, std::vector<std::vector<int>>(this->x, std::vector<int>(this->y)));

	for (int z = 0; z < this->z; ++z)
	{
		for (int x = 0; x < this->x; ++x)
		{
			for (int y = 0; y < this->y; ++y)
			{
				//if (std::round(Random::Float()) == 0)
				//{
				//	WorldBlocks[z][x][y] = y + 1;
				//}
				//else
				//{
				//	WorldBlocks[z][x][y] = 0;
				//}

				//WorldBlocks[z][x][y] = y + 1;
				newWorld[z][x][y] = y + 1;
			}
		}
	}

	//Load3D(newWorld);
}

/// <summary>
/// Loads a world
/// </summary>
/// <param name="world">3D World to load</param>
void World::Load3D(std::vector<std::vector<std::vector<int>>> world)
{
	for (int z = 0; z < this->z; ++z)
	{
		for (int x = 0; x < this->x; ++x)
		{
			for (int y = 0; y < this->y; ++y)
			{
				if (world[z][x][y] > 0)
				{
					glm::vec2 ttl{};
					glm::vec2 trb{};

					switch (world[z][x][y])
					{
					case 1:
						ttl = glm::vec2(0.25f, 0.0f);
						trb = glm::vec2(0.5f, 0.25f);
						break;
					case 2:
						ttl = glm::vec2(0.0f, 0.0f);
						trb = glm::vec2(0.25f, 0.25f);
						break;
					case 3:
						ttl = glm::vec2(0.75f, 0.0f);
						trb = glm::vec2(1.0f, 0.25f);
						break;
					default:
						ttl = glm::vec2(0.25f, 0.25f);
						trb = glm::vec2(0.5f, 0.5f);
						break;
					}

					Entity entity = _coordinator.CreateEntity();
					_coordinator.AddComponent(entity, Transform
						{
							.Position = glm::vec2(z, x),
							.Scale = glm::vec2(1.0f, 1.0f),
							.Rotation = 0.0f
						});
					_coordinator.AddComponent(entity, Renderable
						{
							.TexLeftTop = ttl,
							.TexRightBottom = trb,
							.Color = glm::vec4(1.0f)
						});
					_coordinator.AddComponent(entity, Collider{});

					this->WorldVector[z][x].push_back(entity);
					//this->Blocks.push_back(entity);
				}
			}
		}
	}
}

void World::SetBlock(int x, int y, int z)
{
	//for (auto& entity : this->Blocks)
	//{
	//	_coordinator.DestroyEntity(entity);
	//}
	//this->Blocks.clear();

	//for (int z = 0; z < this->z; ++z)
	//{
	//	for (int x = 0; x < this->x; ++x)
	//	{
	//		for (int y = 0; y < WorldVector[z][x].size(); ++y)
	//		{
	//			_coordinator.DestroyEntity(WorldVector[z][x][y]);
	//		}
	//	}
	//}
	//this->WorldVector.clear();

	//_coordinator.DestroyEntity(WorldVector[z][x][y]);
	//_coordinator.DestroyEntity(35);
	_coordinator.DestroyEntity(WorldVector[z][x][y]);
	this->WorldVector[z][x].pop_back();
}
