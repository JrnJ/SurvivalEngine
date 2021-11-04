#include "Level.h"

#include <fstream>
#include <sstream>

void Level::Load(const char* file, glm::vec2 screenSize, glm::vec2 blockSize)
{
	// Clear old Level data
	this->Blocks.clear();

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
			this->Initialize(blockData, screenSize, blockSize);
	}
}

void Level::Draw(SpriteRenderer& renderer)
{
	// Draw level
	for (GameObject& block : this->Blocks)
		block.Draw(renderer);
}

void Level::Initialize(std::vector<std::vector<unsigned int>> blockData, glm::vec2 screenSize, glm::vec2 blockSize)
{
	// blockData is just a 2D array, so two loops
	for (unsigned int y = 0; y < blockData.size(); ++y)
	{
		for (unsigned int x = 0; x < blockData[y].size(); ++x)
		{
			if (blockData[y][x] > 0)
			{
				// glm::vec2 pos(blockSize.x * x, blockSize.y * y);
				glm::vec2 pos(blockSize.x * x, (-blockSize.y * y) + screenSize.y - blockSize.y);
				std::string block = "";

				switch (blockData[y][x])
				{
					case 1:
						block = "";
						break;
				}

				this->Blocks.push_back(GameObject(pos, blockSize, ResourceManager::GetTexture(block)));
			}
		}
	}
}