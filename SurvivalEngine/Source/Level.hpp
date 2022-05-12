#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "ECS/Types.hpp"

class Level
{
public:
	// Properties
	std::vector<Entity> Blocks;

	// Functions
	void Load(const char* file, glm::vec2 blockSize);
	void Clear();

private:
	void Initialize(std::vector<std::vector<unsigned int>> blockData, glm::vec2 blockSize);
};

#endif