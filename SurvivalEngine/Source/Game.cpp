#include "Game.hpp"

#include <iostream>
#include <queue>
#include <vector>

#include "Math.hpp"
#include "KeyInput.hpp"

#include "Razer/ChromaConnect.hpp"
#include "ResourceManager.hpp"

#include "Components/Components.hpp"

// Also includes all items
#include "Inventory/PlayerInventory.hpp"

ChromaConnect* Chroma;
Coordinator _coordinator;

//GameObject* Turret;
//GameObject* TurretBullet;
//GameObject* TurretBullet2;
//GameObject* TurretBullet3;

// Player things
Entity Player;
PlayerInventory* Inventory;
int SelectedHotbarSlot = 0;

glm::vec2 MoveDirection;

/// <summary>
/// Constructor for Game class
/// </summary>
Game::Game(unsigned int width, unsigned int height)
	: State(GameState::GAME_ACTIVE), Width(width), Height(height), 
		_camera(0.0f, width, height, 0.0f)
{
	
}

/// <summary>
/// Destructor for Game class
/// </summary>
Game::~Game()
{
	delete Chroma;

	delete Inventory;

	std::cout << "Game Deconstrcuted!" << std::endl;
}

const float atlasWidth = 128;
const float atlasHeight = 128;
const float textureWidth = 32;
const float textureHeight = 32;

float atlasCalcWidth = 1.0f / atlasWidth * textureWidth;
float atlasCalcHeight = 1.0f / atlasHeight * textureHeight;

glm::vec2 GetSpriteInAtlas(int x, int y)
{
	return glm::vec2(atlasCalcWidth * (x - 1), atlasCalcHeight * (y - 1));
}

/// <summary>
/// Initialize the Game
/// </summary>
void Game::Init()
{
	// Initialize Razer ChromaConnect
	Chroma = new ChromaConnect(false);

	// Configure GameObjects
	//glm::vec2 turretSpawnPos = glm::vec2(this->Width / 2.0f, this->Height - (BlockSize.y * (5.0f + 5.0f)));
	//Turret = new GameObject(turretSpawnPos, BlockSize, ResourceManager::GetTexture("Grass"));
	//GameObjects.push_back(Turret);
	//TurretBullet = new GameObject(turretSpawnPos, BlockSize, ResourceManager::GetTexture("TurretBullet"));
	//GameObjects.push_back(TurretBullet);
	//TurretBullet2 = new GameObject(turretSpawnPos, BlockSize, ResourceManager::GetTexture("TurretBullet"));
	//GameObjects.push_back(TurretBullet2);
	//TurretBullet3 = new GameObject(turretSpawnPos, BlockSize, ResourceManager::GetTexture("TurretBullet"));
	//GameObjects.push_back(TurretBullet3);

	// Initialize coordinator
	_coordinator.Init();

	// Register Components
	_coordinator.RegisterComponent<Transform>();
	_coordinator.RegisterComponent<Collider>();
	_coordinator.RegisterComponent<Rigidbody>();

	_coordinator.RegisterComponent<Renderable>();

	_coordinator.RegisterComponent<Camera2D>();

	// Render System
	_renderSystem = _coordinator.RegisterSystem<RenderSystem>();
	{
		// Only the Entities with these Components will be in mEntities
		// You will only be able to acces these Components inside the System
		Signature signature;
		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<Renderable>());
		_coordinator.SetSystemSignature<RenderSystem>(signature);
	}
	_renderSystem->Init();

	// Physics System
	_physicsSystem = _coordinator.RegisterSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<Rigidbody>());
		signature.set(_coordinator.GetComponentType<Collider>());
		signature.set(_coordinator.GetComponentType<Renderable>());
		_coordinator.SetSystemSignature<PhysicsSystem>(signature);
	}
	_physicsSystem->Init();

	// Resize System
	_resizeSystem = _coordinator.RegisterSystem<ResizeSystem>();
	{
		Signature signature;
		signature.set(_coordinator.GetComponentType<Transform>());
		_coordinator.SetSystemSignature<ResizeSystem>(signature);
	}
	_resizeSystem->Init(this->Width, this->Height);

	//std::vector<Entity> entities(MAX_ENTITIES - 200);

	//for (auto& entity : entities)
	//{
	//	entity = _coordinator.CreateEntity();

	//	_coordinator.AddComponent(entity, Transform
	//		{
	//			.Position = glm::vec2(1.0f, 12.0f), //this->Width / 2.0f, this->Height / 2.0f
	//			.Scale = _resizeSystem->BlockSize,
	//			.Rotation = 0.0f
	//		});
	//	_coordinator.AddComponent(entity, Renderable
	//		{
	//			.TexLeftTop = GetSpriteInAtlas(1, 2),
	//			.TexRightBottom = GetSpriteInAtlas(2, 3),
	//			.Color = glm::vec4(1.0f)
	//		});
	//}

	Player = _coordinator.CreateEntity();
	_coordinator.AddComponent(Player, Transform
		{
			.Position = glm::vec2(1.0f, 12.0f), //this->Width / 2.0f, this->Height / 2.0f
			.Scale = _resizeSystem->BlockSize,
			.Rotation = 0.0f
		});
	_coordinator.AddComponent(Player, Collider{});
	_coordinator.AddComponent(Player, Rigidbody
		{
			.Velocity = glm::vec2(0.0f)
		});
	_coordinator.AddComponent(Player, Renderable
		{
			.TexLeftTop = GetSpriteInAtlas(4, 1),
			.TexRightBottom = GetSpriteInAtlas(5, 2),
			.Color = glm::vec4(1.0f)
		});

	// Load Level
	Level test; test.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/cage.txt", glm::vec2(this->Width, this->Height), _resizeSystem->BlockSize);

	CurrentLevel = test;
}

//#include "KeyInput.hpp"
/// <summary>
/// Take user input each frame
/// </summary>
/// <param name="dt">Deltatime</param>
void Game::ProcessInput(float dt)
{
	if (this->State == GameState::GAME_ACTIVE)
	{
		// Player Movement
		float horizontal = KeyInput::GetAxisRaw(Axis::Horizontal);
		float vertical = KeyInput::GetAxisRaw(Axis::Vertical);
		_coordinator.GetComponent<Rigidbody>(Player).Velocity = Math::Normalize(glm::vec2(horizontal, vertical)) * 4.0f;

		// Load Levels
		if (KeyInput::GetKeyDown(GLFW_KEY_F1))
		{
			this->CurrentLevel.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/test.txt", glm::vec2(this->Width, this->Height), _resizeSystem->BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		if (KeyInput::GetKeyDown(GLFW_KEY_F2))
		{
			this->CurrentLevel.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/cage.txt", glm::vec2(this->Width, this->Height), _resizeSystem->BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		if (KeyInput::GetKeyDown(GLFW_KEY_F3))
		{
			this->CurrentLevel.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/world.txt", glm::vec2(this->Width, this->Height), _resizeSystem->BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		// Check for Inventory things
		if (KeyInput::GetKeyDown(GLFW_KEY_1))
			SelectedHotbarSlot = 0;
		if (KeyInput::GetKeyDown(GLFW_KEY_2))
			SelectedHotbarSlot = 1;
		if (KeyInput::GetKeyDown(GLFW_KEY_3))
			SelectedHotbarSlot = 2;
		if (KeyInput::GetKeyDown(GLFW_KEY_4))
			SelectedHotbarSlot = 3;
		if (KeyInput::GetKeyDown(GLFW_KEY_5))
			SelectedHotbarSlot = 4;
		if (KeyInput::GetKeyDown(GLFW_KEY_6))
			SelectedHotbarSlot = 5;
		if (KeyInput::GetKeyDown(GLFW_KEY_7))
			SelectedHotbarSlot = 6;
		if (KeyInput::GetKeyDown(GLFW_KEY_8))
			SelectedHotbarSlot = 7;
		if (KeyInput::GetKeyDown(GLFW_KEY_9))
			SelectedHotbarSlot = 8;

		// Got to reset to 0 if not scrolling idk how tbh
		if (KeyInput::GetAxisRaw(Axis::MouseScrollWheel) > 0)
			SelectedHotbarSlot = SelectedHotbarSlot <= 0 ? 8 : SelectedHotbarSlot - 1;
		else if (KeyInput::GetAxisRaw(Axis::MouseScrollWheel) < 0)
			SelectedHotbarSlot = SelectedHotbarSlot >= 8 ? 0 : SelectedHotbarSlot + 1;

		if (KeyInput::GetKeyDown(GLFW_KEY_M))
		{
			Inventory->AddItem(new ItemInstance(new Stone(), 300));
		}
		if (KeyInput::GetKeyDown(GLFW_KEY_N))
		{
			Inventory->AddItem(new ItemInstance(new StoneAxe(), 1));
		}

		if (KeyInput::GetKeyDown(GLFW_KEY_E))
		{
			Inventory->DisplayInventory(SelectedHotbarSlot);
		}

		if (KeyInput::GetKeyDown(GLFW_KEY_O))
		{
			glm::vec2 pos = _coordinator.GetComponent<Transform>(Player).Position;
			std::cout << "PlayerPosition: X: " << pos.x << " Y: " << pos.y << std::endl;
		}
	}
}

float angle = 0.0f;
/// <summary>
/// Each frame this void is called
/// </summary>
/// <param name="dt">Deltatime</param>
void Game::Update(float dt)
{
	// Player Movement -> Replace with the physics system at some point
	//_coordinator.GetComponent<Transform>(Player).Position += _coordinator.GetComponent<Rigidbody>(Player).Velocity * dt;

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

	// Mouse to world pos MAKE THIS A FUNCTION OR ELSE
	if (KeyInput::GetMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
	{
		//std::cout << "Mouse : X: " << KeyInput::MouseX << " Y: " << KeyInput::MouseY << std::endl;
		//std::cout << "Mouse Grid Snapped: X: " << std::floor(KeyInput::MouseX / BlockSize.x) << " Y: " << std::floor(KeyInput::MouseY / BlockSize.y) << std::endl;
		//std::cout << "Camera: X: " << _camera.GetPosition().x << " Y: " << _camera.GetPosition().y << std::endl;

		// On mouse
		/*Turret->Position = { 
			KeyInput::MouseX + _camera.GetPosition().x - Turret->Size.x / 2.0f,
			KeyInput::MouseY + _camera.GetPosition().y - Turret->Size.x / 2.0f
		};*/

		// Grid Snapped
		//Turret->Position = {
		//	std::floor((KeyInput::MouseX + _camera.GetPosition().x) / BlockSize.x) * BlockSize.x,
		//	std::floor((KeyInput::MouseY + _camera.GetPosition().y) / BlockSize.y) * BlockSize.y
		//};

		glm::vec2 newPos = {
			std::floor((KeyInput::MouseX + _camera.GetPosition().x) / _resizeSystem->BlockSize.x),
			std::floor((KeyInput::MouseY + _camera.GetPosition().y) / _resizeSystem->BlockSize.y)
		};

		// Try create a rail
		Entity entity = _coordinator.CreateEntity();
		_coordinator.AddComponent(entity, Transform
			{
				.Position = glm::vec2(newPos),
				.Scale = _resizeSystem->BlockSize,
				.Rotation = 0.0f
			});
		_coordinator.AddComponent(entity, Renderable
			{
				.TexLeftTop = GetSpriteInAtlas(3, 2),
				.TexRightBottom = GetSpriteInAtlas(4, 3),
				.Color = glm::vec4(1.0f)
			});
	}

	// Camera Controls
	// Reset Rotation
	if (KeyInput::GetKeyDown(GLFW_KEY_K))
		_camera.SetRotation(0.0f);

	// Rotate
	_camera.SetRotation(_camera.GetRotation() + KeyInput::GetCustomAxisRaw(GLFW_KEY_J, GLFW_KEY_L) * 0.015 * dt);

	//angle -= dt / 2.0f;
	//float tdegrees = std::remainder(angle * 360.0f, 360.0f);
	//float tradius = BlockSize.x * 1.5f; // Get difference in positions instead
	//glm::vec2 newPos = Turret->Position - glm::vec2(tradius * glm::sin(Math::DegToRad(tdegrees)), tradius * glm::cos(Math::DegToRad(tdegrees)));
	//TurretBullet->Position = newPos;
	//TurretBullet->Rotation = -tdegrees;

	//float offset2 = 120.0f;
	//float tdegrees2 = std::remainder(angle * 360.0f + offset2, 360.0f);
	//glm::vec2 newPos2 = Turret->Position - glm::vec2(tradius * glm::sin(Math::DegToRad(tdegrees2)), tradius * glm::cos(Math::DegToRad(tdegrees2)));
	//TurretBullet2->Position = newPos2;
	//TurretBullet2->Rotation = -tdegrees2;

	//float offset3 = 240.0f;
	//float tdegrees3 = std::remainder(angle * 360.0f + offset3, 360.0f);
	//glm::vec2 newPos3 = Turret->Position - glm::vec2(tradius * glm::sin(Math::DegToRad(tdegrees3)), tradius * glm::cos(Math::DegToRad(tdegrees3)));
	//TurretBullet3->Position = newPos3;
	//TurretBullet3->Rotation = -tdegrees3;

	// Physics
	_physicsSystem->Update(dt);

	// Update Camera
	_camera.SetPosition(glm::vec2(
		_coordinator.GetComponent<Transform>(Player).Position.x * _resizeSystem->BlockSize.x - this->Width / 2.0f + _resizeSystem->BlockSize.x / 2.0f,
		_coordinator.GetComponent<Transform>(Player).Position.y * _resizeSystem->BlockSize.y - this->Height / 2.0f + _resizeSystem->BlockSize.y / 2.0f
	));
}

/// <summary>
/// Render all graphics to screen each frame
/// </summary>
void Game::Render(float dt)
{
	if (this->State == GameState::GAME_ACTIVE)
	{
		// Update Camera
		ResourceManager::GetShader("sprite").SetMatrix4("u_ViewProjection", _camera.GetViewProjectionMatrix());
		//std::cout << "X: " << _camera.GetPosition().x << " Y: " << _camera.GetPosition().y << std::endl;

		// RenderSystem
		_renderSystem->Update(dt);

		// Layer 0 : Background / Skybox - NOW CLEAR COLOR IN Main.cpp
		//Texture2D background = ResourceManager::GetTexture("background");
		//Renderer->DrawSprite(background, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f, glm::vec4(1.0f));
	}
}

void Game::WindowResized(int width, int height)
{
	this->Width = width;
	this->Height = height;

	_resizeSystem->WindowResized(width, height);
	_camera.SetProjectionMatrix(0.0f, width, height, 0.0f);

	// Load Levels
	this->CurrentLevel.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/cage.txt", glm::vec2(this->Width, this->Height), _resizeSystem->BlockSize);
	this->ResetPlayer();
	std::cout << "Level Loaded!" << std::endl;
}

void Game::ResetPlayer()
{
	// Reset Player
	//_coordinator.GetComponent<Transform>(Player).Position = glm::vec2(this->Width / 2.0f - BlockSize.x / 2.0f, this->Height / 2.0f - BlockSize.y / 2.0f);
	//_coordinator.GetComponent<Transform>(Player).Position = glm::vec2(this->Width / 2.0f, this->Height / 2.0f);
}