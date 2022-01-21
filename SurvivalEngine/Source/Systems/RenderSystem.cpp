#include "RenderSystem.hpp"

#include "../Components/Components.hpp"
#include "../ECS/Coordinator.hpp"
#include "../ResourceManager.hpp"
#include "../Renderer/SpriteRenderer.hpp"

extern Coordinator _coordinator;
SpriteRenderer* Renderer;

void RenderSystem::Init()
{
	// Load Shaders
	ResourceManager::LoadShader("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/shaders/sprite.vs.glsl", "C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/shaders/sprite.fs.glsl", nullptr, "sprite");
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);

	// set render-specific controls
	Shader shader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader);

	// Load Sprite Sheet / Atlas
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/atlas.png", "Atlas", true);
}

void RenderSystem::Update(float dt)
{
	// Loop through entities
	// get entites from systems
	for (auto const& entity : mEntities)
	{
		/*Renderer->DrawSprite(
			_coordinator.GetComponent<Renderable>(entity).Sprite,
			_coordinator.GetComponent<Transform>(entity).Position,
			_coordinator.GetComponent<Transform>(entity).Scale,
			_coordinator.GetComponent<Transform>(entity).Rotation,
			_coordinator.GetComponent<Renderable>(entity).Color
			);*/

		Renderer->DrawSprite(
			_coordinator.GetComponent<Transform>(entity).Position,
			_coordinator.GetComponent<Transform>(entity).Scale,
			0.0f,
			ResourceManager::GetTexture("Atlas")
		);
	}

	//Renderer->DrawSprite(
	//	glm::vec2(1.0f, 1.0f),
	//	glm::vec2(1000.0f, 1000.0f),
	//	0.0f,
	//	ResourceManager::GetTexture("Atlas")
	//);
}
