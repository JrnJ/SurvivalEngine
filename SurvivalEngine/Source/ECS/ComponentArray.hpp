#ifndef COMPONENTARRAY_HPP
#define COMPONENTARRAY_HPP

#include <iostream>
#include <array>
#include <cassert>
#include <unordered_map>

#include "Types.hpp"

class IComponentArray
{
public:
	virtual ~IComponentArray() = default; // ?
	virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T> // ?
class ComponentArray : public IComponentArray
{
public:
	void InsertData(Entity entity, T component)
	{
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

		// Put new entry at end and update the maps
		size_t newIndex = mSize;
		mEntityToIndexMap[entity] = newIndex;
		mIndexToEntityMap[newIndex] = entity;
		mComponentArray[newIndex] = component;
		++mSize;

		//if (mEntityToIndexMap.find(entity) == mEntityToIndexMap.end())
		//{
		//	std::cout << "Component " << typeid(component).name() << " already present on Entity with id " << entity << std::endl;
		//}
		//else
		//{
		//	// Put new entry at end and update the maps
		//	size_t newIndex = mSize;
		//	mEntityToIndexMap[entity] = newIndex;
		//	mIndexToEntityMap[newIndex] = entity;
		//	mComponentArray[newIndex] = component;
		//	++mSize;
		//}
	}

	void RemoveData(Entity entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
		size_t indexOfLastElement = mSize - 1;
		mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

		// Update map to point moved spot
		Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		// Erease removed data/entity
		mEntityToIndexMap.erase(entity);
		mIndexToEntityMap.erase(indexOfLastElement);

		// Reduce entity size by 1
		--mSize;
	}

	/// <summary>
	/// Get data of an Entity
	/// </summary>
	/// <param name="entity">Entity's data to return</param>
	/// <returns>Reference to the entity's component</returns>
	T& GetData(Entity entity)
	{
		// This is not the way
		// We have to do this like unity, where if the component doesnt exist, just return null
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

		return mComponentArray[mEntityToIndexMap[entity]];
	}

	void EntityDestroyed(Entity entity) override
	{
		if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
		{
			RemoveData(entity);
		}
	}

private:
	// The packed array of components (of generic type T),
	// set to a specified maximum amount, matching the maximum number
	// of entities allowed to exist simultaneously, so that each entity
	// has a unique spot.
	std::array<T, MAX_ENTITIES> mComponentArray;

	// Map from an entity ID to an array index.
	std::unordered_map<Entity, size_t> mEntityToIndexMap;

	// Map from an array index to an entity ID.
	std::unordered_map<size_t, Entity> mIndexToEntityMap;

	// Total size of valid entries in the array.
	size_t mSize;
};

#endif
