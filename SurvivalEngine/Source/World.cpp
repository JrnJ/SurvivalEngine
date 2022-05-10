#include "World.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Random.hpp"
#include "ECS/Coordinator.hpp"
#include "Components/Components.hpp"
#include "ResourceManager.hpp"

extern Coordinator _coordinator;

void World::_Load(const char* file, glm::vec2 screenSize, glm::vec2 blockSize)
{
	// Load Level from file
	std::string blockCode;
	//Level level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> blockData;

	// Check if file can be accesed
	if (fstream)
	{
		// Read all lines in file
		while (std::getline(fstream, line))
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;

			// Implement trimmed file thing here
			while (sstream >> blockCode)
			{
				bool xFound = false;
				std::string before;
				std::string after;

				for (int i = 0; i < blockCode.length(); i++)
				{
					if (xFound)
					{
						after += blockCode[i];
					}
					else
					{
						if (blockCode[i] != 'x')
						{
							before += blockCode[i];
						}
						else
						{
							xFound = true;
						}
					}
				}

				if (xFound)
				{
					for (int i = 0; i < stoi(after); i++)
					{
						row.push_back(stoi(before));
					}
				}
				else
					row.push_back(stoi(blockCode));
			}

			// Insert at beggining so we can load at bottom of screen first and then go up
			blockData.insert(blockData.begin(), row);
		}

		// blockData is just a 2D array, so two loops
		for (unsigned int y = 0; y < blockData.size(); ++y)
		{
			for (unsigned int x = 0; x < blockData[y].size(); ++x)
			{
				if (blockData[y][x] > 0)
				{
					glm::vec2 pos(blockSize.x * x, blockSize.y * y);
					std::string texName = "";

					switch (blockData[y][x])
					{
					case 2:
						texName = "RailStraight";
						break;
					case 3:
						texName = "RailAngled";
						break;
					default:
						texName = "";
						break;
					}

					/*Entity entity = _coordinator.CreateEntity();
					_coordinator.AddComponent(entity, Transform
						{
							.Position = pos,
							.Scale = blockSize,
							.Rotation = 0.0f
						});
					_coordinator.AddComponent(entity, Renderable
						{
							.TexCoords = glm::vec2(0.0f, 1.0f),
							.Color = glm::vec4(1.0f)
						});
					this->Blocks.push_back(entity);*/
				}
			}
		}
	}

	//// Create an Entity
	//Entity blockEntity = _coordinator.CreateEntity();
	//_coordinator.AddComponent(blockEntity, Transform
	//	{
	//		.Position = glm::vec2(0.0f),
	//		.Scale = glm::vec2(1.0f),
	//		.Rotation = 0.0f
	//	});
	//_coordinator.AddComponent(blockEntity, Renderable
	//	{
	//		.TexCoords = glm::vec2(0.0f, 1.0f),
	//		.Color = glm::vec4(1.0f)
	//	});

	//// Add Entity to Scene
	//this->Blocks.push_back(blockEntity);
}

void World::_Unload()
{
	// Destroy all Entity's
	for (auto& entity : this->Blocks)
	{
		_coordinator.DestroyEntity(entity);
	}
	this->Blocks.clear();

	for (auto& entity : this->Entities)
	{
		_coordinator.DestroyEntity(entity);
	}
	this->Entities.clear();
}

void World::_Save()
{

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
	
	//int blocks2d[5][5] = {};
	//bool skipLayer2d = false;

	//for (int y = 0; y < 5; ++y)
	//{
	//	for (int x = 0; x < 5; ++x)
	//	{
	//		if (skipLayer2d)
	//		{
	//			blocks2d[y][x] = 2;
	//		}
	//		else
	//		{
	//			blocks2d[y][x] = 1;
	//		}

	//		skipLayer2d = !skipLayer2d;
	//	}
	//}

	//Load2D(blocks2d);
	

	//           x  y  z
	//          [z][x][y]
	int blocks3d[10][10][3];
	bool skipLayer = false;

	for (int z = 0; z < 10; ++z)
	{
		for (int x = 0; x < 10; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				//if (y == 1 && skipLayer)
				//{
				//	blocks3d[z][x][y] = 0;
				//}
				//else
				//{
				//	blocks3d[z][x][y] = y + 1;
				//}

				if (std::round(Random::Float()) == 0)
				{
					blocks3d[z][x][y] = y + 1;
				}
			}
		}
	}

	Load3D(blocks3d);
}

void World::Load2D(int blocks[5][5])
{
	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			// Dont create air blocks, soley for testing here
			Entity entity = _coordinator.CreateEntity();
			_coordinator.AddComponent(entity, Transform
				{
					.Position = glm::vec2(x, y),
					.Scale = glm::vec2(1.0f, 1.0f),
					.Rotation = 0.0f
				});

			switch (blocks[y][x])
			{
				case 0:
					break;
				case 1:
					_coordinator.AddComponent(entity, Renderable
						{
							.TexLeftTop = glm::vec2(0.25f, 0.0f),
							.TexRightBottom = glm::vec2(0.5f, 0.25f),
							.Color = glm::vec4(1.0f)
						});
					break;
				case 2:
					_coordinator.AddComponent(entity, Renderable
						{
							.TexLeftTop = glm::vec2(0.0f, 0.0f),
							.TexRightBottom = glm::vec2(0.25f, 0.25f),
							.Color = glm::vec4(1.0f)
						});
					break;
				case 3:
					_coordinator.AddComponent(entity, Renderable
						{
							.TexLeftTop = glm::vec2(0.75f, 0.0f),
							.TexRightBottom = glm::vec2(1.0f, 0.25f),
							.Color = glm::vec4(1.0f)
						});
					break;
				default:
					break;
			}
		}
	}
}

void World::Load3D(int blocks[10][10][3])
{
	for (int z = 0; z < 10; ++z)
	{
		for (int x = 0; x < 10; ++x)
		{
			for (int y = 0; y < 3; ++y)
			{
				glm::vec2 ttl{};
				glm::vec2 trb{};

				switch (blocks[z][x][y])
				{
					case 0:
						break;
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
						ttl = glm::vec2(0.0f, 0.0f);
						trb = glm::vec2(0.0f, 0.0f);
						break;
				}

				if (blocks[z][x][y] > 0)
				{
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
				}
			}
		}
	}
}
