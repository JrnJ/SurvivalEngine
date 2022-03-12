#include "AnimationSystem.hpp"

#include "../ECS/Coordinator.hpp"
#include "../ResourceManager.hpp"

#include "../Math.hpp"

extern Coordinator _coordinator;

AnimationSystem::AnimationSystem()
{

}

AnimationSystem::~AnimationSystem()
{

}



void AnimationSystem::Update(float dt)
{
	time += dt;

	/*if (time > 1.0f)
	{
		time -= 1.0f;

		// Loop through entites with an Animatiable component
		for (auto const& entity : mEntities)
		{
			// Get reference
			Animatable animatable = _coordinator.GetComponent<Animatable>(entity);

			// Get size
			size_t totalSprites = animatable.Sprites.size();
			std::cout << "Total Sprites: " << totalSprites << std::endl;

			// Up currentsprite
			int currentSprite = animatable.CurrentSprite >= totalSprites - 1 ? 0 : animatable.CurrentSprite + 1;
			std::cout << "Current Sprite: " << currentSprite << std::endl;

			// Update it
			_coordinator.GetComponent<Animatable>(entity).CurrentSprite = currentSprite;

			// Set it
			_coordinator.GetComponent<Renderable>(entity) = animatable.Sprites[currentSprite];
		}
	}*/

	for (auto const& entity : mEntities)
	{
		Animatable animatable = _coordinator.GetComponent<Animatable>(entity);

		if (time >= animatable.UpdateAt)
		{
			// Set next time stamp
			_coordinator.GetComponent<Animatable>(entity).UpdateAt = time + animatable.TimeBetweenAnimations;

			// Update Sprite
			// Get TotalSprites
			size_t totalSprites = animatable.Sprites.size();

			// Increment or limit CurrentSprite
			int currentSprite = animatable.CurrentSprite >= totalSprites - 1 ? 0 : animatable.CurrentSprite + 1;

			// Update it
			_coordinator.GetComponent<Animatable>(entity).CurrentSprite = currentSprite;

			// Set it
			_coordinator.GetComponent<Renderable>(entity) = animatable.Sprites[currentSprite];
		}
	}
}
