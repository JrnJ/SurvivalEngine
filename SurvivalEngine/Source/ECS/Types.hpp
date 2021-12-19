#ifndef TYPES_HPP
#define TYPES_HPP

#include <bitset>
#include <cstdint>

// ECS - These are aliases, no Entity is a uint32_t but you can call it as a Entity
using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::uint8_t;

const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

#endif
