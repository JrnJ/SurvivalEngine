#include "Level.hpp"

#include <fstream>
#include <sstream>
#include "ECS/Coordinator.hpp"
#include "Components/Components.hpp"

extern Coordinator _coordinator;

void Level::Load(const char* file, glm::vec2 blockSize)
{
	this->Clear();

	// Load Level from file
	std::string blockCode;
	Level level;
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

		if (blockData.size() > 0)
			this->Initialize(blockData, blockSize);
	}
}

void Level::Clear()
{
	// Clear old Level data
	for (auto& entity : this->Blocks)
	{
		_coordinator.DestroyEntity(entity);
	}
	this->Blocks.clear();
}

void Level::Initialize(std::vector<std::vector<unsigned int>> blockData, glm::vec2 blockSize)
{
	// blockData is just a 2D array, so two loops
	for (unsigned int y = 0; y < blockData.size(); ++y)
	{
		for (unsigned int x = 0; x < blockData[y].size(); ++x)
		{
			if (blockData[y][x] > 0)
			{
				glm::vec2 pos(x, y);
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

				Entity entity = _coordinator.CreateEntity();
				_coordinator.AddComponent(entity, Transform
					{
						.Position = pos,
						.Scale = blockSize,
						.Rotation = 0.0f
					});
				_coordinator.AddComponent(entity, Collider{});
				_coordinator.AddComponent(entity, Renderable
					{
						.TexLeftTop = glm::vec2(0.25f, 0.0f),
						.TexRightBottom = glm::vec2(0.5f, 0.25f),
						.Color = glm::vec4(1.0f)
					});
				this->Blocks.push_back(entity);
			}
		}
	}
}