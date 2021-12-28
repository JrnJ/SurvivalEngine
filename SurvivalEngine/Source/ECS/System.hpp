#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Types.hpp"
#include <set>

class System
{
public:
	// mEntities are NOT all the entities
	// Entities that match the filters when creating a system
	std::set<Entity> mEntities;
};

#endif
