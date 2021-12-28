#include "ResizeSystem.hpp"

#include "../ECS/Coordinator.hpp"
#include "../Components/Transform.hpp"

extern Coordinator _coordinator;

void ResizeSystem::Init(int width, int height)
{
	BlockSize = glm::vec2(width / 24.0f, height / 13.5f);
}

void ResizeSystem::WindowResized(int width, int height)
{
	float x;
	float y;

	if (width < height)
	{
		// Width is smaller, so calculate heigth
		x = (float)width;
		y = width * (9.0f / 16.0f);
	}
	else
	{
		// Heigth is smaller, so calculate screensize with height
		x = height * (16.0f / 9.0f);
		y = (float)height;
	}

	BlockSize = glm::vec2(x / 24.0f, y / 13.5f);

	for (auto const& entity : mEntities)
	{
		_coordinator.GetComponent<Transform>(entity).Scale = BlockSize;
	}
}
