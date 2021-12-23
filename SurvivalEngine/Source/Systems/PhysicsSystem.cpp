#include "PhysicsSystem.hpp"

#include "../Components/Components.hpp"
#include "../ECS/Coordinator.hpp"

extern Coordinator _coordinator;

void PhysicsSystem::Init()
{
	
}

void PhysicsSystem::Update(float dt)
{
	for (auto const& entity : mEntities)
	{
		_coordinator.GetComponent<Transform>(entity).Position += _coordinator.GetComponent<Rigidbody>(entity).Velocity * dt;
	}
}
