#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <queue>

#include <glm/glm.hpp>

#include "Level.hpp"
#include "World.hpp"
#include "KeyInput.hpp"
#include "Renderer/Camera.hpp"

#include "ECS/Coordinator.hpp"

// Systems
#include "Systems/RenderSystem.hpp"
#include "Systems/AnimationSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/ResizeSystem.hpp"

// All Game States
enum class GameState 
{
    GAME_ACTIVE,
    GAME_MENU
};

class Game
{
public:    
    // Game State
    GameState State;
    Level CurrentLevel;

    // Window Dimensions
    unsigned int Width, Height;

    // Constructor & Destructor
    Game(unsigned int width, unsigned int height);
    ~Game();

    // Initialize Game State
    void Init();
    
    // Game Loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render(float dt);

    // Events
    void WindowResized(int width, int height);

    // Player
    void ResetPlayer();

private:
    Camera _camera;

    std::shared_ptr<RenderSystem> _renderSystem;
    std::shared_ptr<AnimationSystem> _animationSystem;
    std::shared_ptr<PhysicsSystem> _physicsSystem;
    std::shared_ptr<ResizeSystem> _resizeSystem;

    std::vector<Entity> _entities;
};

#endif