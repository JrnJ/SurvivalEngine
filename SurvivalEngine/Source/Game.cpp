#include "game.hpp"

#include <iostream>
#include <queue>

#include "ResourceManager.hpp"

#include "Math.hpp"
#include "KeyInput.hpp"

#include "Razer/ChromaConnect.hpp"

#include "Renderer/SpriteRenderer.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/EntityOld.hpp"
#include "Objects/PlayerEntity.hpp"
#include "Objects/CowEntity.hpp"
#include "Components/Components.hpp"

// Also includes all items
#include "Inventory/PlayerInventory.hpp"

SpriteRenderer* Renderer;
PlayerEntity* Player;
Entity NewEntity;
ChromaConnect* Chroma;

GameObject* Turret;
GameObject* TurretBullet;
GameObject* TurretBullet2;
GameObject* TurretBullet3;

Entity Rail1;
Entity Rail2;
Entity Rail3;

// Instantiate static variables
//std::map<GameObject, int> Game::GameObjects;
std::vector<GameObject*> Game::GameObjects;

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

	delete Chroma;

	delete Turret;
	delete TurretBullet;
	delete TurretBullet2;
	delete TurretBullet3;

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
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);

	// set render-specific controls
	Shader shader = ResourceManager::GetShader("sprite");
	Renderer = new SpriteRenderer(shader);

	// Load Textures
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/player.png", "player", true);
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/enemy.png", "enemy", true);

	// Texture loading
	// ID : 0 -> Nothing
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Unknown.png", "", false); // ID : - 
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Blocks/Grass.png", "Grass", false); // ID : 1
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Blocks/Dirt.png", "Dirt", false); // ID : 2
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Blocks/Water.png", "Water", false); // ID : 3

	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Blocks/TurretBullet.png", "TurretBullet", true);

	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Blocks/RailStraight.png", "RailStraight", true);
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/Blocks/RailAngled.png", "RailAngled", true);

	// Load Levels
	Level test; test.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/test.txt", glm::vec2(this->Width, this->Height), BlockSize);

	CurrentLevel = test;

	// Configure GameObjects
	glm::vec2 spawnPos = glm::vec2(this->Width / 2.0f - BlockSize.x / 2.0f, this->Height / 2.0f - BlockSize.y / 2.0f);
	Player = new PlayerEntity(spawnPos, BlockSize, ResourceManager::GetTexture("player"));
	GameObjects.push_back(Player);

	glm::vec2 turretSpawnPos = glm::vec2(this->Width / 2.0f, this->Height - (BlockSize.y * (5.0f + 5.0f)));
	Turret = new GameObject(turretSpawnPos, BlockSize, ResourceManager::GetTexture("Grass"));
	GameObjects.push_back(Turret);

	TurretBullet = new GameObject(turretSpawnPos, BlockSize, ResourceManager::GetTexture("TurretBullet"));
	GameObjects.push_back(TurretBullet);
	TurretBullet2 = new GameObject(turretSpawnPos, BlockSize, ResourceManager::GetTexture("TurretBullet"));
	GameObjects.push_back(TurretBullet2);
	TurretBullet3 = new GameObject(turretSpawnPos, BlockSize, ResourceManager::GetTexture("TurretBullet"));
	GameObjects.push_back(TurretBullet3);

	// // //
	// ESC  
	// // //

	// Initialize coordinator
	_coordinator.Init();

	// Register Components
	_coordinator.RegisterComponent<Transform>();
	_coordinator.RegisterComponent<Rigidbody>();
	_coordinator.RegisterComponent<Renderable>();
	_coordinator.RegisterComponent<Camera2D>();

	// Render System
	_renderSystem = _coordinator.RegisterSystem<RenderSystem>();
	{
		Signature signature;
		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<Renderable>());
		signature.set(_coordinator.GetComponentType<Camera2D>());
		_coordinator.SetSystemSignature<RenderSystem>(signature);
	}
	_renderSystem->Init();

	// Physics System
	_physicsSystem = _coordinator.RegisterSystem<PhysicsSystem>();
	{
		Signature signature;
		signature.set(_coordinator.GetComponentType<Transform>());
		signature.set(_coordinator.GetComponentType<Renderable>());
		signature.set(_coordinator.GetComponentType<Rigidbody>());
		_coordinator.SetSystemSignature<PhysicsSystem>(signature);
	}
	_physicsSystem->Init();

	//std::vector<Entity> entities(MAX_ENTITIES - 1);

	NewEntity = _coordinator.CreateEntity();

	_coordinator.AddComponent(NewEntity, Transform
		{
			.Position = glm::vec2(this->Width / 2.0f, this->Height / 2.0f),
			.Scale = BlockSize,
			.Rotation = 0.0f
		});

	_coordinator.AddComponent(NewEntity, Renderable
		{
			.Sprite = ResourceManager::GetTexture("TurretBullet"),
			.Color = glm::vec4(1.0f)
		});

	// Just 3 fking rails holy fk
	Rail1 = _coordinator.CreateEntity();
	_coordinator.AddComponent(Rail1, Transform
		{
			.Position = glm::vec2(BlockSize.x * 3.0f, BlockSize.y * 5.0f),
			.Scale = BlockSize,
			.Rotation = 0.0f
		});
	_coordinator.AddComponent(Rail1, Renderable
		{
			.Sprite = ResourceManager::GetTexture("RailStraight"),
			.Color = glm::vec4(1.0f)
		});

	Rail2 = _coordinator.CreateEntity();
	_coordinator.AddComponent(Rail2, Transform
		{
			.Position = glm::vec2(BlockSize.x * 3.0f, BlockSize.y * 6.0f),
			.Scale = BlockSize,
			.Rotation = 0.0f
		});
	_coordinator.AddComponent(Rail2, Renderable
		{
			.Sprite = ResourceManager::GetTexture("RailStraight"),
			.Color = glm::vec4(1.0f)
		});

	Rail3 = _coordinator.CreateEntity();
	_coordinator.AddComponent(Rail3, Transform
		{
			.Position = glm::vec2(BlockSize.x * 4.0f, BlockSize.y * 6.0f),
			.Scale = BlockSize,
			.Rotation = 0.0f
		});
	_coordinator.AddComponent(Rail3, Renderable
		{
			.Sprite = ResourceManager::GetTexture("RailStraight"),
			.Color = glm::vec4(1.0f)
		});

	// // //
	// /ESC  
	// // //
}

//#include "KeyInput.hpp"
/// <summary>
/// Take user input each frame
/// </summary>
/// <param name="dt">Deltatime</param>
void Game::ProcessInput(float dt)
{
	// Loop through GameObjects and call their Update function
	for (int i = GameObjects.size() - 1; i > -1; --i)
	{
		GameObjects[i]->Input(dt);
	}

	if (this->State == GameState::GAME_ACTIVE)
	{
		// Load Levels
		if (KeyInput::GetKeyDown(GLFW_KEY_F1))
		{
			this->CurrentLevel.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/test.txt", glm::vec2(this->Width, this->Height), BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		if (KeyInput::GetKeyDown(GLFW_KEY_F2))
		{
			this->CurrentLevel.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/cage.txt", glm::vec2(this->Width, this->Height), BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		if (KeyInput::GetKeyDown(GLFW_KEY_F3))
		{
			this->CurrentLevel.Load("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/levels/world.txt", glm::vec2(this->Width, this->Height), BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
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
	// Loop through GameObjects and call their Update function
	for (int i = GameObjects.size() - 1; i > -1; --i)
	{
		GameObjects[i]->Update(dt);
	}

	// Chroma
	if (Chroma->ChromaEnabled)
	{
		// Clear lights first
		Chroma->Clear();

		Chroma->Test();
		Chroma->Inventory(Player->SelectedHotbarSlot);

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
			std::floor((KeyInput::MouseX + _camera.GetPosition().x) / BlockSize.x) * BlockSize.x,
			std::floor((KeyInput::MouseY + _camera.GetPosition().y) / BlockSize.y) * BlockSize.y
		};

		// Try create a rail
		Entity entity = _coordinator.CreateEntity();
		_coordinator.AddComponent(entity, Transform
			{
				.Position = glm::vec2(newPos),
				.Scale = BlockSize,
				.Rotation = 0.0f
			});
		_coordinator.AddComponent(entity, Renderable
			{
				.Sprite = ResourceManager::GetTexture("RailStraight"),
				.Color = glm::vec4(1.0f)
			});
	}

	if (KeyInput::GetMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
	{
		// Try delete the rail
		
		// TODO
		// Get block info on click
		// Fuck it you need a grid system OOF
	}

	if (KeyInput::GetKeyDown(GLFW_KEY_K))
		_camera.SetRotation(0.0f);

	//if (KeyInput::GetKey(GLFW_KEY_L))
	//	_camera.SetRotation(_camera.GetRotation() + 0.025f * dt);

	// Rotate camera around center insteaf of top left
	_camera.SetRotation(_camera.GetRotation() + KeyInput::GetCustomAxisRaw(GLFW_KEY_J, GLFW_KEY_L) * 0.015 * dt);

	angle -= dt / 2.0f;
	float tdegrees = std::remainder(angle * 360.0f, 360.0f);
	float tradius = BlockSize.x * 1.5f; // Get difference in positions instead
	glm::vec2 newPos = Turret->Position - glm::vec2(tradius * glm::sin(Math::DegToRad(tdegrees)), tradius * glm::cos(Math::DegToRad(tdegrees)));
	TurretBullet->Position = newPos;
	TurretBullet->Rotation = -tdegrees;

	float offset2 = 120.0f;
	float tdegrees2 = std::remainder(angle * 360.0f + offset2, 360.0f);
	glm::vec2 newPos2 = Turret->Position - glm::vec2(tradius * glm::sin(Math::DegToRad(tdegrees2)), tradius * glm::cos(Math::DegToRad(tdegrees2)));
	TurretBullet2->Position = newPos2;
	TurretBullet2->Rotation = -tdegrees2;

	float offset3 = 240.0f;
	float tdegrees3 = std::remainder(angle * 360.0f + offset3, 360.0f);
	glm::vec2 newPos3 = Turret->Position - glm::vec2(tradius * glm::sin(Math::DegToRad(tdegrees3)), tradius * glm::cos(Math::DegToRad(tdegrees3)));
	TurretBullet3->Position = newPos3;
	TurretBullet3->Rotation = -tdegrees3;
	
	DoCollision(dt);

	_camera.SetPosition(glm::vec3(Player->Position.x - (this->Width / 2.0f - BlockSize.x / 2.0f), Player->Position.y - (this->Height / 2.0f - BlockSize.y / 2.0f), 0.0f));

	//std::cout << "velX: " << Player->Velocity.x << " velY: " << Player->Velocity.y << std::endl;
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

		// RenderSystem
		_renderSystem->Update(dt);

		// Draw calls
		// Loop trhough GameObjects and draw them
		for (int i = GameObjects.size() - 1; i > -1; --i)
		{
			GameObjects[i]->Draw(*Renderer);
		}

		// Layer 0 : Background / Skybox - NOW CLEAR COLOR IN Main.cpp
		//Texture2D background = ResourceManager::GetTexture("background");
		//Renderer->DrawSprite(background, glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f, glm::vec4(1.0f));
		
		// Layer 1 : Level Blocks
		CurrentLevel.Draw(*Renderer);
		//Turret->Draw(*Renderer);
		//TurretBullet->Draw(*Renderer);
		//TurretBullet2->Draw(*Renderer);
		//TurretBullet3->Draw(*Renderer);

		// Layer 2
		//Player->Draw(*Renderer);
		//Player2->Draw(*Renderer);

		// ECS temp draw
		Renderer->DrawSprite(
			_coordinator.GetComponent<Renderable>(NewEntity).Sprite,
			_coordinator.GetComponent<Transform>(NewEntity).Position,
			_coordinator.GetComponent<Transform>(NewEntity).Scale,
			_coordinator.GetComponent<Transform>(NewEntity).Rotation,
			_coordinator.GetComponent<Renderable>(NewEntity).Color
			);

		Renderer->DrawSprite(
			_coordinator.GetComponent<Renderable>(Rail1).Sprite,
			_coordinator.GetComponent<Transform>(Rail1).Position,
			_coordinator.GetComponent<Transform>(Rail1).Scale,
			_coordinator.GetComponent<Transform>(Rail1).Rotation,
			_coordinator.GetComponent<Renderable>(Rail1).Color
		);

		Renderer->DrawSprite(
			_coordinator.GetComponent<Renderable>(Rail2).Sprite,
			_coordinator.GetComponent<Transform>(Rail2).Position,
			_coordinator.GetComponent<Transform>(Rail2).Scale,
			_coordinator.GetComponent<Transform>(Rail2).Rotation,
			_coordinator.GetComponent<Renderable>(Rail2).Color
		);

		Renderer->DrawSprite(
			_coordinator.GetComponent<Renderable>(Rail3).Sprite,
			_coordinator.GetComponent<Transform>(Rail3).Position,
			_coordinator.GetComponent<Transform>(Rail3).Scale,
			_coordinator.GetComponent<Transform>(Rail3).Rotation,
			_coordinator.GetComponent<Renderable>(Rail3).Color
		);
	}
}

void Game::ResetPlayer()
{
	// Reset Player
	Player->Size = BlockSize;
	Player->Position = glm::vec2(this->Width / 2.0f - BlockSize.x / 2.0f, this->Height / 2.0f - BlockSize.y / 2.0f);
}

// Move this to a class and than add to stuff
bool CheckCollision(EntityOld& player, GameObject& object)
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