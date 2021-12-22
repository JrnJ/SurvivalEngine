#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <array>
#include <cassert>
#include <queue>

#include "Types.hpp"

class EntityManager
{
public:
	EntityManager()
	{
		// Initialize the queue with all possible entity ID's
		for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
		{
			mAvailableEntities.push(entity);
		}
	}

	Entity CreateEntity()
	{
		// If the argument expression of this macro with functional form compares equal to 
		// zero (i.e., the expression is false), a message is written to the standard error 
		// device and abort is called, terminating the program execution.
		// https://www.cplusplus.com/reference/cassert/assert/
		assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

		// Take an ID from the newest of the queue
		Entity id = mAvailableEntities.front();
		mAvailableEntities.pop(); // Removes the next element in the queue
		++mLivingEntityCount;

		return id;
	}

	void DestroyEntity(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Invalidate the destroyed entity's siganture
		mSignatures[entity].reset(); // ?

		// Put the destroyed ID at the back of the queue
		mAvailableEntities.push(entity);
		--mLivingEntityCount;
	}

	void SetSignature(Entity entity, Signature signature)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Put this entity's signature into the array
		mSignatures[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
		assert(entity < MAX_ENTITIES && "Entity out of range.");

		// Get this entity's signature from the array
		return mSignatures[entity];
	}

	// Queue of unused entity IDs
	std::queue<Entity> mAvailableEntities{};

	// Array of signatures where the index corresponds to the entity ID
	std::array<Signature, MAX_ENTITIES> mSignatures{};

	// Total living entities - used to keep limits on how many exist
	uint32_t mLivingEntityCount{};

private:
	
};

#endif