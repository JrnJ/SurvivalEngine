#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <queue>

#include <glm/glm.hpp>

#include "Level.hpp"
#include "KeyInput.hpp"
#include "Renderer/Camera.hpp"

#include "ECS/Coordinator.hpp"

// Systems
#include "Systems/RenderSystem.hpp"
#include "Systems/PhysicsSystem.hpp"

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

    // Block Size
    glm::vec2 BlockSize;

    // Constructor & Destructor
    Game(unsigned int width, unsigned int height);
    ~Game();

    // Initialize Game State
    void Init();
    
    // Game Loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render(float dt);

    // Player
    void ResetPlayer();
    void DoCollision(float dt);

private:
    Camera _camera;

    std::shared_ptr<RenderSystem> _renderSystem;
    std::shared_ptr<PhysicsSystem> _physicsSystem;

    std::vector<Entity> _entities;
};

#endif