#include "RenderSystem.hpp"

#include "../Components/Components.hpp"
#include "../ECS/Coordinator.hpp"

extern Coordinator _coordinator;

void RenderSystem::Init()
{
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
	/*for (auto const& entity : _coordinator.mSystemManager->mSystems)
	{
		
	}*/

}
