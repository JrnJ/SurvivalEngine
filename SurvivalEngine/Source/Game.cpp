#include "game.hpp"
#include "resource_manager.hpp"

#include "Math.hpp"
#include "Razer/ChromaConnect.hpp"

#include "Renderer/sprite_renderer.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/Entity.hpp"
#include "Objects/PlayerEntity.hpp"
#include "Objects/CowEntity.hpp"
#include "Inventory/Inventory.hpp"

#include <iostream>

SpriteRenderer* Renderer;
PlayerEntity* Player;
PlayerEntity* Player2;
ChromaConnect* Chroma;
Inventory* PlayerInventory;

glm::vec2 MoveDirection;

/// <summary>
/// Constructor for Game class
/// </summary>
Game::Game(unsigned int width, unsigned int height)
	: State(GameState::GAME_ACTIVE), Width(width), Height(height), BlockSize(width / 24.0f, height / 13.5f), 
		_camera(-1.6f, 1.6f, -0.9f, 0.9f)
{
	
}

/// <summary>
/// Destructor for Game class
/// </summary>
Game::~Game()
{
	delete Renderer;
	delete Player;
	delete Player2;

	delete Chroma;
	delete PlayerInventory;
}

/// <summary>
/// Initialize the Game
/// </summary>
void Game::Init()
{
	// Initialize Razer ChromaConnect
	Chroma = new ChromaConnect(false);

	// Load Shaders
	ResourceManager::LoadShader("C:/Dev/Resources/SurvivalEngine/shaders/sprite.vs", "C:/Dev/Resources/SurvivalEngine/shaders/sprite.fs", nullptr, "sprite");

	// Configure Shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
		static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	//ResourceManager::GetShader("sprite").SetMatrix4("projection", _camera.GetViewProjectionMatrix());

	// set render-specific controls
	Shader shader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader);

	// Load Textures
	ResourceManager::LoadTexture("C:/Dev/Resources/SurvivalEngine/textures/background.png", false, "background");
	ResourceManager::LoadTexture("C:/Dev/Resources/SurvivalEngine/textures/player.png", true, "player");
	ResourceManager::LoadTexture("C:/Dev/Resources/SurvivalEngine/textures/enemy.png", true, "enemy");

	// Texture loading
	// ID : 0 -> Nothing
	ResourceManager::LoadTexture("C:/Dev/Resources/SurvivalEngine/textures/Unknown.png", false, ""); // ID : - 
	ResourceManager::LoadTexture("C:/Dev/Resources/SurvivalEngine/textures/Grass.png", false, "Grass"); // ID : 1
	ResourceManager::LoadTexture("C:/Dev/Resources/SurvivalEngine/textures/Dirt.png", false, "Dirt"); // ID : 2

	// Load Levels
	Level test; test.Load("C:/Dev/Resources/SurvivalEngine/levels/test.txt", glm::vec2(this->Width, this->Height), BlockSize);

	CurrentLevel = test;

	// Configure GameObjects
	glm::vec2 spawnPos = glm::vec2(BlockSize.x * 2, this->Height - (BlockSize.y * (3 + 3)));
	Player = new PlayerEntity(spawnPos, BlockSize, ResourceManager::GetTexture("player"));

	glm::vec2 player2SpawnPos = glm::vec2(this->Width / 2.0f, this->Height - (BlockSize.y * (3 + 3)));
	Player2 = new PlayerEntity(player2SpawnPos, BlockSize, ResourceManager::GetTexture("enemy"));

	// Inventory
	PlayerInventory = new Inventory(3, {1, 2, 3});
}

bool idkk = false;
/// <summary>
/// Take user input each frame
/// </summary>
/// <param name="dt">Deltatime</param>
void Game::ProcessInput(float dt)
{
	if (this->State == GameState::GAME_ACTIVE)
	{
		float horizontal = Input.GetAxisRaw(Axis::Horizontal);
		float vertical = Input.GetAxisRaw(Axis::Vertical);
		Player->Velocity = Math::Normalize(glm::vec2(horizontal, vertical)) * 300.0f;

		float horizontal2 = Input.GetCustomAxisRaw(GLFW_KEY_L, GLFW_KEY_J);
		float vertical2 = Input.GetCustomAxisRaw(GLFW_KEY_K, GLFW_KEY_I);
		Player2->Velocity = Math::Normalize(glm::vec2(horizontal2, vertical2)) * 300.0f;

		// Reset Down
		if (Input.GetKey(GLFW_KEY_1))
		{
			this->CurrentLevel.Load("C:/Dev/Resources/SurvivalEngine/levels/test.txt", glm::vec2(this->Width, this->Height), BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		if (Input.GetKey(GLFW_KEY_2))
		{
			this->CurrentLevel.Load("C:/Dev/Resources/SurvivalEngine/levels/line.txt", glm::vec2(this->Width, this->Height), BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		if (Input.GetKey(GLFW_KEY_3))
		{
			this->CurrentLevel.Load("C:/Dev/Resources/SurvivalEngine/levels/cage.txt", glm::vec2(this->Width, this->Height), BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		if (Input.GetKey(GLFW_KEY_R))
		{
			PlayerInventory->DisplayInventory();
		}
	}
}

/// <summary>
/// Each frame this void is called
/// </summary>
/// <param name="dt">Deltatime</param>
void Game::Update(float dt)
{
	// Chroma
	if (Chroma->ChromaEnabled)
	{
		Chroma->Test();
	}

	// Move Player based on Velocity
	Player->Position += Player->Velocity * dt;
	Player2->Position += Player2->Velocity * dt;

	DoCollision(dt);
	
	//std::cout << "velX: " << Player->Velocity.x << " velY: " << Player->Velocity.y << std::endl;
}

/// <summary>
/// Render all graphics to screen each frame
/// </summary>
void Game::Render()
{
	if (this->State == GameState::GAME_ACTIVE)
	{
		// Draw calls
		
		// Layer 0 : Background / Skybox
		Texture2D background = ResourceManager::GetTexture("background");
		Renderer->DrawSprite(background, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
		
		// Layer 1 : Level Blocks
		CurrentLevel.Draw(*Renderer);

		// Layer 2
		Player->Draw(*Renderer);
		Player2->Draw(*Renderer);
	}
}

void Game::ResetPlayer()
{
	// Reset Player
	Player->Size = BlockSize;
	Player->Position = glm::vec2(BlockSize.x * 2, this->Height - (BlockSize.y * (3 + 3)));
}

// Move this to a class and than add to stuff
bool CheckCollision(Entity& player, GameObject& object)
{
	float push = 0.0f;

	float deltaX = object.Position.x - player.Position.x;
	float deltaY = object.Position.y - player.Position.y;

	float intersectX = abs(deltaX) - (object.Size.x / 2.0f + player.Size.x / 2.0f);
	float intersectY = abs(deltaY) - (object.Size.y / 2.0f + player.Size.y / 2.0f);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		// This is a clamp
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				player.Position += glm::vec2(intersectX* (1.0f - push), 0.0f);
			}
			else
			{
				player.Position += glm::vec2(-intersectX * (1.0f - push), 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				player.Position += glm::vec2(0.0f, intersectY * (1.0f - push));
			}
			else
			{
				player.Position += glm::vec2(0.0f, -intersectY * (1.0f - push));
			}
		}

		return true;
	}

	return false;
}

void Game::DoCollision(float dt)
{
	int i = 0;

	for (GameObject& block : CurrentLevel.Blocks)
	{
		/*Player->Collision.DoCollision(block);
		Player2->Collision.DoCollision(block);*/

		CheckCollision(*Player, block);
		CheckCollision(*Player2, block);
	}

	/*if (i > 0)
	{
		Player->Color = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	else
	{
		Player->Color = glm::vec3(1.0f, 1.0f, 1.0f);
	}*/
}