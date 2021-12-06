#ifndef GAME_HPP
#define GAME_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "Level.hpp"
#include "KeyInput.hpp"
#include "Renderer/Camera.hpp"

// All Game States
enum class GameState 
{
    GAME_ACTIVE,
    GAME_MENU
};

class Game
{
public:
    // Storage
    //static std::map<GameObject, int> GameObjects;
    static std::vector<GameObject*> GameObjects;
    
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
    void Render();

    // Player
    void ResetPlayer();
    void DoCollision(float dt);

private:
    Camera _camera;
};

#endif