#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include "../ECS/System.hpp"
#include <memory>

class RenderSystem : public System
{
public:
	void Init();

	void Update(float dt);

private:
	//Entity _camera;
};

#endif
