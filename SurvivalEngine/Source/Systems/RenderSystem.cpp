#include "RenderSystem.hpp"

#include "../Components/Components.hpp"
#include "../ECS/Coordinator.hpp"
#include "../Renderer/SpriteRenderer.hpp"
//#include "../ResourceManager.cpp"

extern Coordinator _coordinator;
extern SpriteRenderer* Renderer;

void RenderSystem::Init()
{
	//// Load Shaders
	//ResourceManager::LoadShader("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/shaders/sprite.vs.glsl", "C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/shaders/sprite.fs.glsl", nullptr, "sprite");
	//ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);

	//// set render-specific controls
	//Shader shader = ResourceManager::GetShader("sprite");
	//Renderer = new SpriteRenderer(shader);

	//_camera = _coordinator.CreateEntity();
	//_coordinator.AddComponent(_camera, Transform
	//	{
	//		.Position = glm::vec2(0.0f, 0.0f),
	//		.Scale = glm::vec2(1.0f),
	//		.Rotation = 0.0f
	//	});
	//_coordinator.AddComponent(_camera, Camera2D
	//	{
	//		// nothing atm
	//	});
}

void RenderSystem::Update(float dt)
{
	// Loop through entities
	// get entites from systems
	for (auto const& entity : mEntities)
	{
		Renderer->DrawSprite(
			_coordinator.GetComponent<Renderable>(entity).Sprite,
			_coordinator.GetComponent<Transform>(entity).Position,
			_coordinator.GetComponent<Transform>(entity).Scale,
			_coordinator.GetComponent<Transform>(entity).Rotation,
			_coordinator.GetComponent<Renderable>(entity).Color
			);
	}
}
