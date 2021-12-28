#ifndef PHYSICSSYSTEM_HPP
#define PHYSICSSYSTEM_HPP

#include <memory>

#include "../ECS/System.hpp"
#include "../ECS/EntityManager.hpp"
#include "ColliderSystem.hpp"

class PhysicsSystem : public System
{
public:
	void Init();
	
	void Update(float dt);

private:
	std::shared_ptr<ColliderSystem> _colliderSystem;

	void DoCollision(Entity entity);
};

#endif
