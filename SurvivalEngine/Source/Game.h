#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Level.h"
#include "KeyInput.h"

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
    KeyInput Input;

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
    void Render();

    // Player
    void ResetPlayer();
    void DoCollision(float dt);
};

#endif