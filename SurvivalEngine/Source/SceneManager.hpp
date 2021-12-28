#ifndef SCENEMANAGER_HPP
#define SCENENMANAGER_HPP

#include "Scene.hpp"

class SceneManager
{
public:
	Scene CurrentScene;

	void LoadScene();
	void SaveScene();
	void DestroyScene();
};

#endif