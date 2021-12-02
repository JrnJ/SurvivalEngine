#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Objects/GameObject.hpp"
#include "ResourceManager.hpp"
#include "Renderer/SpriteRenderer.hpp"

class Level
{
public:
	// Properties
	std::vector<GameObject> Blocks;

	// Constructor
	Level() {}

	// Functions
	void Load(const char* file, glm::vec2 screenSize, glm::vec2 blockSize);

	void Draw(SpriteRenderer& renderer);

private:
	void Initialize(std::vector<std::vector<unsigned int>> blockData, glm::vec2 screenSize, glm::vec2 blockSize);
};

#endif