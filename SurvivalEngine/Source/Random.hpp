#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

// This random is from TheCherno's 1hour game
// Github:
// https://github.com/TheCherno/Hazel1HourGame/blob/92ac3d2ab87d261daf6b1f76e8b2971f67d9c2df/Sandbox/src/Random.h
class Random
{
public:
	static void Init()
	{
		s_RandomEngine.seed(std::random_device()());
	}

	static float Float()
	{
		return (float)s_Distribution(s_RandomEngine) / (float)std::numeric_limits<uint32_t>::max();
	}
private:
	static std::mt19937 s_RandomEngine;
	static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};

#endif