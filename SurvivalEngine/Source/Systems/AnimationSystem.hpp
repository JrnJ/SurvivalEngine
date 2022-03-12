#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

#include "../ECS/System.hpp"
#include "../Components/Components.hpp"

class AnimationSystem : public System
{
public:
    AnimationSystem();
    ~AnimationSystem();

    void Update(float dt);
    float time = 0;
private:

};

#endif
