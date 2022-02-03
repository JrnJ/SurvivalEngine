#include "PhysicsSystem.hpp"

#include "../Components/Components.hpp"
#include "../ECS/Coordinator.hpp"

extern Coordinator _coordinator;

void PhysicsSystem::Init()
{
	// Collider System
	_colliderSystem = _coordinator.RegisterSystem<ColliderSystem>();
	{
		Signature signature;
		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<Collider>());
		signature.set(_coordinator.GetComponentType<Renderable>());
		_coordinator.SetSystemSignature<ColliderSystem>(signature);
	}
}

/// <summary>
/// Updates the Physics system
/// </summary>
/// <param name="dt">Deltatime</param>
void PhysicsSystem::Update(float dt)
{
	// Loop through entities
	for (auto const& entity : mEntities)
	{
		// Apply Physics
		_coordinator.GetComponent<Transform>(entity).Position += _coordinator.GetComponent<Rigidbody>(entity).Velocity * dt;

		// Apply Collision
		this->DoCollision(entity);
	}
}

void PhysicsSystem::DoCollision(Entity rigidbody)
{
	for (auto const& entity : _colliderSystem->mEntities)
	{
		if (entity != rigidbody)
		{
			float push = 0.0f;

			float deltaX = _coordinator.GetComponent<Transform>(entity).Position.x - _coordinator.GetComponent<Transform>(rigidbody).Position.x;
			float deltaY = _coordinator.GetComponent<Transform>(entity).Position.y - _coordinator.GetComponent<Transform>(rigidbody).Position.y;

			// Something wrong with these calculations because of the new positioning system
			//float intersectX2 = abs(deltaX) - (_coordinator.GetComponent<Transform>(entity).Scale.x / 2.0f + _coordinator.GetComponent<Transform>(rigidbody).Scale.x / 2.0f);
			//float intersectY2 = abs(deltaY) - (_coordinator.GetComponent<Transform>(entity).Scale.y / 2.0f + _coordinator.GetComponent<Transform>(rigidbody).Scale.y / 2.0f);
			float intersectX = abs(deltaX) - 1.0f;// - (_coordinator.GetComponent<Transform>(entity).Scale.x / 2.0f + _coordinator.GetComponent<Transform>(rigidbody).Scale.x / 2.0f);
			float intersectY = abs(deltaY) - 1.0f;// -(_coordinator.GetComponent<Transform>(entity).Scale.y / 2.0f + _coordinator.GetComponent<Transform>(rigidbody).Scale.y / 2.0f);

			if (intersectX < 0.0f && intersectY < 0.0f)
			{
				// This is a clamp
				push = std::min(std::max(push, 0.0f), 1.0f);

				if (intersectX > intersectY)
				{
					if (deltaX > 0.0f)
					{
						_coordinator.GetComponent<Transform>(rigidbody).Position += glm::vec2(intersectX * (1.0f - push), 0.0f);
					}
					else
					{
						_coordinator.GetComponent<Transform>(rigidbody).Position += glm::vec2(-intersectX * (1.0f - push), 0.0f);
					}
				}
				else
				{
					if (deltaY > 0.0f)
					{
						_coordinator.GetComponent<Transform>(rigidbody).Position += glm::vec2(0.0f, intersectY * (1.0f - push));
					}
					else
					{
						_coordinator.GetComponent<Transform>(rigidbody).Position += glm::vec2(0.0f, -intersectY * (1.0f - push));
					}
				}
			}
		}
	}
}
