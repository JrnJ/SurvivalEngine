#include "game.hpp"
#include "ResourceManager.hpp"

#include "Math.hpp"
#include "Razer/ChromaConnect.hpp"

#include "Renderer/SpriteRenderer.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/Entity.hpp"
#include "Objects/PlayerEntity.hpp"
#include "Objects/CowEntity.hpp"

// Also includes all items
#include "Inventory/PlayerInventory.hpp"

#include <iostream>

SpriteRenderer* Renderer;
PlayerEntity* Player;
PlayerEntity* Player2;
ChromaConnect* Chroma;
PlayerInventory* Inventory;

GameObject* Dummy;
GameObject* Dummy2;

glm::vec2 MoveDirection;
int SelectedHotbarSlot = 0;

/// <summary>
/// Constructor for Game class
/// </summary>
Game::Game(unsigned int width, unsigned int height)
	: State(GameState::GAME_ACTIVE), Width(width), Height(height), BlockSize(width / 24.0f, height / 13.5f), 
		_camera(0.0f, width, height, 0.0f)
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
	delete Inventory;

	delete Dummy;
	delete Dummy2;

	std::cout << "Game Deconstrcuted!" << std::endl;
}

/// <summary>
/// Initialize the Game
/// </summary>
void Game::Init()
{
	// Initialize Razer ChromaConnect
	Chroma = new ChromaConnect(false);

	// Load Shaders
	ResourceManager::LoadShader("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/shaders/sprite.vs.glsl", "C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/shaders/sprite.fs.glsl", nullptr, "sprite");

	// Configure Shaders
	//glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
	//	static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	//ResourceManager::GetShader("sprite").SetMatrix4("u_ViewProjection", projection);
	/*ResourceManager::GetShader("sprite").SetMatrix4("u_ViewProjection", _camera.GetViewProjectionMatrix());*/

	// set render-specific controls
	Shader shader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader);

	// Load Textures
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/background.png", "background");
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/player.png", "player");
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/enemy.png", "enemy");

	// Texture loading
	// ID : 0 -> Nothing
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Unknown.png", ""); // ID : - 
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Blocks/Grass.png", "Grass"); // ID : 1
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Blocks/Dirt.png", "Dirt"); // ID : 2
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Blocks/Water.png", "Water"); // ID : 3

	// Load Levels
	Level test; test.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/test.txt", glm::vec2(this->Width, this->Height), BlockSize);

	CurrentLevel = test;

	// Configure GameObjects
	glm::vec2 spawnPos = glm::vec2(this->Width / 2.0f - BlockSize.x / 2.0f, this->Height / 2.0f - BlockSize.y / 2.0f);
	Player = new PlayerEntity(spawnPos, BlockSize, ResourceManager::GetTexture("player"));

	glm::vec2 player2SpawnPos = glm::vec2(this->Width / 2.0f, this->Height - (BlockSize.y * (3.0f + 3.0f)));
	Player2 = new PlayerEntity(player2SpawnPos, BlockSize, ResourceManager::GetTexture("enemy"));

	// Inventory
	Inventory = new PlayerInventory();
}

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
		if (Input.GetKeyDown(GLFW_KEY_F1))
		{
			this->CurrentLevel.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/test.txt", glm::vec2(this->Width, this->Height), BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		if (Input.GetKeyDown(GLFW_KEY_F2))
		{
			this->CurrentLevel.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/cage.txt", glm::vec2(this->Width, this->Height), BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		// Check for Inventory things
		if (Input.GetKeyDown(GLFW_KEY_1))
			SelectedHotbarSlot = 0;
		if (Input.GetKeyDown(GLFW_KEY_2))
			SelectedHotbarSlot = 1;
		if (Input.GetKeyDown(GLFW_KEY_3))
			SelectedHotbarSlot = 2;
		if (Input.GetKeyDown(GLFW_KEY_4))
			SelectedHotbarSlot = 3;
		if (Input.GetKeyDown(GLFW_KEY_5))
			SelectedHotbarSlot = 4;
		if (Input.GetKeyDown(GLFW_KEY_6))
			SelectedHotbarSlot = 5;
		if (Input.GetKeyDown(GLFW_KEY_7))
			SelectedHotbarSlot = 6;
		if (Input.GetKeyDown(GLFW_KEY_8))
			SelectedHotbarSlot = 7;
		if (Input.GetKeyDown(GLFW_KEY_9))
			SelectedHotbarSlot = 8;

		// Got to reset to 0 if not scrolling idk how tbh
		if (Input.GetAxisRaw(Axis::MouseScrollWheel) > 0)
			SelectedHotbarSlot = SelectedHotbarSlot <= 0 ? 8 : SelectedHotbarSlot - 1;
		else if (Input.GetAxisRaw(Axis::MouseScrollWheel) < 0)
			SelectedHotbarSlot = SelectedHotbarSlot >= 8 ? 0 : SelectedHotbarSlot + 1;

		if (Input.GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
			if (Inventory->Slots[SelectedHotbarSlot]->_item != NULL)
				Inventory->Slots[SelectedHotbarSlot]->_item->LeftClick();

		if (Input.GetKeyDown(GLFW_KEY_M))
		{
			Inventory->AddItem(new ItemInstance(new Stone(), 300));
		}
		if (Input.GetKeyDown(GLFW_KEY_N))
		{
			Inventory->AddItem(new ItemInstance(new StoneAxe(), 1));
		}

		if (Input.GetKeyDown(GLFW_KEY_E))
		{
			Inventory->DisplayInventory();
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
		// Clear lights first
		Chroma->Clear();

		Chroma->Test();
		Chroma->Inventory(SelectedHotbarSlot);

		// Draw changes last
		Chroma->Draw();
	}

	// Move Player based on Velocity
	Player->Position += Player->Velocity * dt;
	Player2->Position += Player2->Velocity * dt;
	_camera.SetPosition(glm::vec3(Player->Position.x - this->Width / 2.0f, Player->Position.y - this->Height / 2.0f, 0.0f));

	//DoCollision(dt);
	
	//std::cout << "velX: " << Player->Velocity.x << " velY: " << Player->Velocity.y << std::endl;
}

/// <summary>
/// Render all graphics to screen each frame
/// </summary>
void Game::Render()
{
	if (this->State == GameState::GAME_ACTIVE)
	{
		// Update camera
		ResourceManager::GetShader("sprite").SetMatrix4("u_ViewProjection", _camera.GetViewProjectionMatrix());

		// Draw calls
		
		// Layer 0 : Background / Skybox
		//Texture2D background = ResourceManager::GetTexture("background");
		//Renderer->DrawSprite(background, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
		
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