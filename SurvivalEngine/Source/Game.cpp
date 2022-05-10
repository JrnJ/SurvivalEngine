#include "Game.hpp"

#include <iostream>
#include <queue>
#include <vector>

#include "Math.hpp"
#include "Random.hpp"
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

// Player Animations
const float atlasWidth = 128;
const float atlasHeight = 128;
const float textureWidth = 32;
const float textureHeight = 32;

float atlasCalcWidth = 1.0f / atlasWidth * textureWidth;
float atlasCalcHeight = 1.0f / atlasHeight * textureHeight;

glm::vec2 GetSpriteInAtlas(int x, int y)
{
	return glm::vec2(atlasCalcWidth * x, atlasCalcHeight * y);
}

std::string animationState = "normal";

Animatable playerAnimationNormal {
	.TimeBetweenAnimations = 0.5f,
	.Sprites = {
		{ GetSpriteInAtlas(0, 2), GetSpriteInAtlas(1, 3), glm::vec4(1.0f) },
		{ GetSpriteInAtlas(1, 2), GetSpriteInAtlas(2, 3), glm::vec4(1.0f) }
	}
};

Animatable playerAnimationLeft {
	.TimeBetweenAnimations = 0.5f,
	.Sprites = {
		{ GetSpriteInAtlas(2, 2), GetSpriteInAtlas(3, 3), glm::vec4(1.0f) },
		{ GetSpriteInAtlas(3, 2), GetSpriteInAtlas(4, 3), glm::vec4(1.0f) }
	}
};

Animatable playerAnimationRight {
	.TimeBetweenAnimations = 0.5f,
	.Sprites = {
		{ GetSpriteInAtlas(3, 2), GetSpriteInAtlas(2, 3), glm::vec4(1.0f) },
		{ GetSpriteInAtlas(4, 2), GetSpriteInAtlas(3, 3), glm::vec4(1.0f) }
	}
};


// Player Animations

/// <summary>
/// Constructor for Game class
/// </summary>
Game::Game(unsigned int width, unsigned int height)
	: State(GameState::GAME_ACTIVE), Width(width), Height(height), 
		_camera(0.0f, width, height, 0.0f)
{
	Random::Init();
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
	_coordinator.RegisterComponent<Animatable>();

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

	_animationSystem = _coordinator.RegisterSystem<AnimationSystem>();
	{
		Signature signature;
		signature.set(_coordinator.GetComponentType<Renderable>());
		signature.set(_coordinator.GetComponentType<Animatable>());
		_coordinator.SetSystemSignature<AnimationSystem>(signature);
	}
	// init doesnt exist here bc no use atm

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
	_renderSystem->SetScale(_resizeSystem->BlockSize.x);

	std::vector<Entity> entities(MAX_ENTITIES - 200);

	//for (auto& entity : entities)
	//{
	//	entity = _coordinator.CreateEntity();

	//	_coordinator.AddComponent(entity, Transform
	//		{
	//			.Position = glm::vec2(1.0f, 12.0f), //this->Width / 2.0f, this->Height / 2.0f
	//			.Scale = glm::vec2(1.0f, 1.0f), //_resizeSystem->BlockSize,
	//			.Rotation = 0.0f
	//		});
	//	_coordinator.AddComponent(entity, Renderable
	//		{
	//			.TexLeftTop = GetSpriteInAtlas(1, 2),
	//			.TexRightBottom = GetSpriteInAtlas(2, 3),
	//			.Color = glm::vec4(1.0f)
	//		});
	//}

		// Load World
	World world;
	world.Generate();

	GameWorld = world;

	Player = _coordinator.CreateEntity();
	_coordinator.AddComponent(Player, Transform
		{
			.Position = glm::vec2(9.0f, 5.0f), //this->Width / 2.0f, this->Height / 2.0f
			.Scale = glm::vec2(1.0f, 1.0f), //_resizeSystem->BlockSize,
			.Rotation = 0.0f
		});
	_coordinator.AddComponent(Player, Collider{});
	_coordinator.AddComponent(Player, Rigidbody
		{
			.Velocity = glm::vec2(0.0f)
		});
	_coordinator.AddComponent(Player, Renderable{});
	_coordinator.AddComponent(Player, playerAnimationNormal);
	//_coordinator.AddComponent(Player, Animatable
	//	{
	//		.TimeBetweenAnimations = 0.5f,
	//		.Sprites = { 
	//			{ GetSpriteInAtlas(3, 0), GetSpriteInAtlas(4, 1), glm::vec4(1.0f) }, 
	//			{ GetSpriteInAtlas(0, 1), GetSpriteInAtlas(1, 2), glm::vec4(1.0f) }
	//		}
	//	});

	// Load Level
	//Level test; test.Load("./Assets/levels/test.txt", glm::vec2(this->Width, this->Height), glm::vec2(1.0f, 1.0f)/*_resizeSystem->BlockSize*/);

	//CurrentLevel = test;
}

// Speed of car in m/s
float carSpeed = 0.0f;

// New or Moved
glm::vec2 carVelocity = glm::vec2(0.0f, 0.0f); // carSpeed
float carMinSpeed = -3.5f;
float carMaxSpeed = 11.1f;
float carMaxSteerSpeed = 3.8f;
float carAcceleration = 8.0f;  // 40 / 2 / 3.6
float carDecceleration = 8.0f; // 40 / 2 / 3.6

// Others
float carBreakAcceleration = 10.1f;
float carReverseAcceleration = 6.6f;
float carMaxReverseSpeed = 3.5f;

float steerSpeed = 180.0f; // Idea: 1second for 90 degrees

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
		_coordinator.GetComponent<Rigidbody>(Player).Velocity = Math::Normalize(glm::vec2(horizontal, vertical)) * 4.0f * dt;
		
		// Apply animation :: NEED A PLAYER CLASS ....
		if (horizontal == 1.0f)
		{
			if (animationState != "left")
			{
				_coordinator.GetComponent<Animatable>(Player) = playerAnimationLeft;
				animationState = "left";
			}
		}
		else if (horizontal == -1.0f)
		{
			if (animationState != "right")
			{
				_coordinator.GetComponent<Animatable>(Player) = playerAnimationRight;
				animationState = "right";
			}
		}
		else
		{
			if (animationState != "normal")
			{
				_coordinator.GetComponent<Animatable>(Player) = playerAnimationNormal;
				animationState = "normal";
			}
		}

		/*// Car Physics
		float horizontal = KeyInput::GetAxisRaw(Axis::Horizontal);
		float vertical = KeyInput::GetAxisRaw(Axis::Vertical);
		float rotation = _coordinator.GetComponent<Transform>(Player).Rotation;
		//std::cout << _coordinator.GetComponent<Transform>(Player).Rotation << std::endl;

		// Steer Car
		if (std::abs(carSpeed) > 0.25f)
		{
			_coordinator.GetComponent<Transform>(Player).Rotation += horizontal * -1.0f * steerSpeed * dt;
		}

		bool isSteering = horizontal != 0;

		glm::vec2 carAxisSpeedDevider = Math::Normalize(glm::vec2(
			-std::sin(Math::DegToRad(rotation)),
			std::cos(Math::DegToRad(rotation))
		));
			 
		if (!KeyInput::GetKey(GLFW_KEY_SPACE))
		{
			if (vertical == 1)
			{
				// Move forward
				// Check if user is steering
				if (isSteering)
				{
					//carSpeed = Math::ClampLerp(carSpeed + carAcceleration * dt, carMinSpeed, carMaxSteerSpeed, 0.0f, dt);
					carSpeed = Math::Clamp(carSpeed + carAcceleration * dt, carMinSpeed, carMaxSpeed); // carMaxSteerSpeed
				}
				else
				{
					carSpeed = Math::Clamp(carSpeed + carAcceleration * dt, carMinSpeed, carMaxSpeed);
				}	
			}
			else if (vertical == 0)
			{
				// Deccelerate
				if (std::round(carSpeed) == 0.0f)
				{
					carSpeed = 0.0f;
				}
				else
				{
					if (carSpeed > 0.0f)
					{
						// Deccelerate car
						carSpeed = Math::Clamp(carSpeed - carDecceleration * dt, carMinSpeed, carMaxSpeed);
					}
					else
					{
						// Accelerate car lol
						carSpeed = Math::Clamp(carSpeed + carDecceleration * dt, carMinSpeed, carMaxSpeed);
					}
				}
			}
			else // if vertical == -1
			{
				// Move backwards
				if (carSpeed > 0)
				{
					// Break if Car is having speed
					carSpeed = Math::Clamp(carSpeed - carAcceleration * dt, carMinSpeed, carMaxSpeed);
				}
				else
				{
					// Reverse if car if speed is below 0
					carSpeed = Math::Clamp(carSpeed - carReverseAcceleration * dt, carMinSpeed, carMaxSpeed);
				}
			}
		}
		else
		{
			// Brake
			if (std::round(carSpeed) == 0.0f)
			{
				carSpeed = 0.0f;
			}
			else 
			{
				if (carSpeed > 0.0f)
				{
					carSpeed = Math::Clamp(carSpeed - carBreakAcceleration * dt, carMinSpeed, carMaxSpeed);
				}
				else
				{
					carSpeed = Math::Clamp(carSpeed + carBreakAcceleration * dt, carMinSpeed, carMaxSpeed);
				}
			}
		}

		carVelocity = carAxisSpeedDevider * carSpeed;
		_coordinator.GetComponent<Rigidbody>(Player).Velocity = carVelocity * dt;*/

		// Click TP
		if (KeyInput::GetMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
		{
			glm::vec2 newPos = {
				std::floor((KeyInput::MouseX + _camera.GetPosition().x) / _resizeSystem->BlockSize.x),
				std::floor((KeyInput::MouseY + _camera.GetPosition().y) / _resizeSystem->BlockSize.y)
			};

			_coordinator.GetComponent<Transform>(Player).Position = newPos;
		}

		// Load Levels
		/*if (KeyInput::GetKeyDown(GLFW_KEY_F1))
		{
			this->CurrentLevel.Load("./Assets/levels/test.txt", glm::vec2(this->Width, this->Height), _resizeSystem->BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		if (KeyInput::GetKeyDown(GLFW_KEY_F2))
		{
			this->CurrentLevel.Load("./Assets/levels/cage.txt", glm::vec2(this->Width, this->Height), _resizeSystem->BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}

		if (KeyInput::GetKeyDown(GLFW_KEY_F3))
		{
			this->CurrentLevel.Load("./Assets/levels/world.txt", glm::vec2(this->Width, this->Height), _resizeSystem->BlockSize);
			this->ResetPlayer();
			std::cout << "Level Loaded!" << std::endl;
		}*/

		// Check for Inventory things
		//if (KeyInput::GetKeyDown(GLFW_KEY_1))
		//	SelectedHotbarSlot = 0;
		//if (KeyInput::GetKeyDown(GLFW_KEY_2))
		//	SelectedHotbarSlot = 1;
		//if (KeyInput::GetKeyDown(GLFW_KEY_3))
		//	SelectedHotbarSlot = 2;
		//if (KeyInput::GetKeyDown(GLFW_KEY_4))
		//	SelectedHotbarSlot = 3;
		//if (KeyInput::GetKeyDown(GLFW_KEY_5))
		//	SelectedHotbarSlot = 4;
		//if (KeyInput::GetKeyDown(GLFW_KEY_6))
		//	SelectedHotbarSlot = 5;
		//if (KeyInput::GetKeyDown(GLFW_KEY_7))
		//	SelectedHotbarSlot = 6;
		//if (KeyInput::GetKeyDown(GLFW_KEY_8))
		//	SelectedHotbarSlot = 7;
		//if (KeyInput::GetKeyDown(GLFW_KEY_9))
		//	SelectedHotbarSlot = 8;
		//
		//// Got to reset to 0 if not scrolling idk how tbh
		//if (KeyInput::GetAxisRaw(Axis::MouseScrollWheel) > 0)
		//	SelectedHotbarSlot = SelectedHotbarSlot <= 0 ? 8 : SelectedHotbarSlot - 1;
		//else if (KeyInput::GetAxisRaw(Axis::MouseScrollWheel) < 0)
		//	SelectedHotbarSlot = SelectedHotbarSlot >= 8 ? 0 : SelectedHotbarSlot + 1;

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
				.Scale = glm::vec2(1.0f, 1.0f), //_resizeSystem->BlockSize,
				.Rotation = 0.0f
			});
		_coordinator.AddComponent(entity, Renderable
			{
				.TexLeftTop = GetSpriteInAtlas(2, 1),
				.TexRightBottom = GetSpriteInAtlas(3, 2),
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

		// AnimationSystem, this is called before the RenderSystem!
		_animationSystem->Update(dt);

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
	_renderSystem->SetScale(_resizeSystem->BlockSize.x);
	_camera.SetProjectionMatrix(0.0f, width, height, 0.0f);

	// Load Levels
	//this->CurrentLevel.Load("./Assets/levels/cage.txt", glm::vec2(this->Width, this->Height), glm::vec2(1.0f, 1.0f));
	this->ResetPlayer();
	std::cout << "Level Loaded!" << std::endl;
}

void Game::ResetPlayer()
{
	// Reset Player
	//_coordinator.GetComponent<Transform>(Player).Position = glm::vec2(this->Width / 2.0f - BlockSize.x / 2.0f, this->Height / 2.0f - BlockSize.y / 2.0f);
	//_coordinator.GetComponent<Transform>(Player).Position = glm::vec2(this->Width / 2.0f, this->Height / 2.0f);
}