#ifndef RESIZESYSTEM_HPP
#define RESIZESYSTEM_HPP

#include <glm/glm.hpp>

#include "../ECS/System.hpp"
#include <memory>

class ResizeSystem : public System
{
public:
	glm::vec2 BlockSize;

	void Init(int width, int height);
	void WindowResized(int width, int height);

private:

};

#endif 
