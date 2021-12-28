#ifndef SCENE_HPP
#define SCENE_HPP

#include "World.hpp"

class Scene
{
public:
	World GameWorld;

	Scene();
	~Scene();

	void Load();
	void Save();
};

#endif