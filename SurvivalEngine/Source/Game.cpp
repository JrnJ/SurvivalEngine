#include "game.hpp"
#include "resource_manager.hpp"

#include "Math.hpp"
#include "Razer/ChromaConnect.hpp"

#include "Renderer/sprite_renderer.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/Entity.hpp"
#include "Objects/PlayerEntity.hpp"
#include "Objects/CowEntity.hpp"

#include <iostream>

SpriteRenderer* Renderer;
PlayerEntity* Player;
CowEntity* Cow;
ChromaConnect* Chroma;

glm::vec2 MoveDirection;

/// <summary>
/// Constructor for Game class
/// </summary>
Game::Game(unsigned int width, unsigned int height)
	: State(GameState::GAME_ACTIVE), Width(width), Height(height), BlockSize(width / 24.0f, height / 13.5f)
{
	
}

/// <summary>
/// Destructor for Game class
/// </summary>
Game::~Game()
{
	delete Renderer;
	delete Player;

	//delete Input;
	delete Chroma;
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

	glm::vec2 cowSpawnPos = glm::vec2(this->Width / 2.0f, this->Height - (BlockSize.y * (3 + 3)));
	Cow = new CowEntity(cowSpawnPos, BlockSize, ResourceManager::GetTexture("enemy"));
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
		Cow->Velocity = Math::Normalize(glm::vec2(horizontal2, vertical2)) * 300.0f;

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
	}
}

/// <summary>
/// Each frame this void is called
/// </summary>
/// <param name="dt">Deltatime</param>
void Game::Update(float dt)
{
	// Chroma
	Chroma->SingleColor();

	// Move Player based on Velocity
	Player->Position += Player->Velocity * dt;
	Cow->Position += Cow->Velocity * dt;

	DoCollision(dt);
	//Player->Collision.Test("Test");
	
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
		Cow->Draw(*Renderer);
	}
}

void Game::ResetPlayer()
{
	// Reset Player
	Player->Size = BlockSize;
	Player->Position = glm::vec2(BlockSize.x * 2, this->Height - (BlockSize.y * (3 + 3)));
}

bool RayVsRect(const glm::vec2& rayOrigin, const glm::vec2& rayDirection, const GameObject& target,
	glm::vec2& contactPoint, glm::vec2& contactNormal, const float& time_hit_near)
{
	glm::vec2 t_near = (target.Position - rayOrigin) / rayDirection;
	glm::vec2 t_far = (target.Position + target.Size - rayOrigin) / rayDirection;

	if (t_near.x > t_far.x)
		std::swap(t_near.x, t_far.x);
	if (t_near.y > t_far.y)
		std::swap(t_near.y, t_far.y);

	if (t_near.x > t_far.y || t_near.y > t_far.x)
		return false;

	float t_hit_near = std::max(t_near.x, t_near.y);
	float t_hit_far = std::min(t_far.x, t_far.y);

	if (t_hit_far < 0.0f)
		return false;

	contactPoint = rayOrigin + time_hit_near * rayDirection;

	if (t_near.x > t_near.y)
	{
		if (rayDirection.x < 0.0f)
			contactNormal = glm::vec2(1.0f, 0.0f);
		else
			contactNormal = glm::vec2(-1.0f, 0.0f);

		//contactNormal = rayDirection.x < 0.0f ? glm::vec2(1.0f, 0.0f) : glm::vec2(-1.0f, 0.0f);
	}
	else if (t_near.x < t_near.y)
	{
		if (rayDirection.y < 0.0f)
			contactNormal = glm::vec2(0.0f, 1.0f);
		else
			contactNormal = glm::vec2(0.0f, -1.0f);
	}

	return true;
}

// Static?
bool RectVsRect(GameObject& one, GameObject& two) // Axis Aligned Bounding Box(AABB) both ways
{
	// Check for collision
	bool isCollidingX = one.Position.x + one.Size.x >= two.Position.x && two.Position.x + two.Size.x >= one.Position.x;
	bool isCollidingY = one.Position.y + one.Size.y >= two.Position.y && two.Position.y + two.Size.x >= one.Position.y;

	// Return true if both are true
	return isCollidingX && isCollidingY;
}

bool DynamicRectVsRect(const Entity& in, const GameObject& target,
	glm::vec2& contactPoint, glm::vec2& contactNormal, float& contactTime, const float dt)
{
	if (in.Velocity == glm::vec2(0.0f, 0.0f))
		return false;

	GameObject expanded_target;
	expanded_target.Position = target.Position - in.Size / 2.0f;
	expanded_target.Size = target.Size + in.Size;

	if (RayVsRect(in.Position + in.Size / 2.0f, in.Velocity * dt, expanded_target, contactPoint, contactNormal, contactTime))
	{
		return (contactTime >= 0.0f && contactTime < 1.0f);
	}

	return false;
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
				Player->Position += glm::vec2(intersectX* (1.0f - push), 0.0f);
			}
			else
			{
				Player->Position += glm::vec2(-intersectX * (1.0f - push), 0.0f);
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				Player->Position += glm::vec2(0.0f, intersectY * (1.0f - push));
			}
			else
			{
				Player->Position += glm::vec2(0.0f, -intersectY * (1.0f - push));
			}
		}

		return true;
	}

	return false;
}

void Game::DoCollision(float dt)
{
	int i = 0;

	/*glm::vec2 cp = glm::vec2(0.0f, 0.0f);
	glm::vec2 cn = glm::vec2(0.0f, 0.0f);
	float ct = 0.0f;*/

	for (GameObject& block : CurrentLevel.Blocks)
	{
		CheckCollision(*Player, block);
		//if (DynamicRectVsRect(*Player, block, cp, cn, ct, dt))
		//{
		//	//std::cout << "Collision" << std::endl;
		//	
		//	Player->Velocity += cn * glm::vec2(std::abs(Player->Velocity.x), std::abs(Player->Velocity.y)) * (1.0f - ct);
		//	// 43:50 => Collision not working properly
		//	i++;
		//}

		//Player->Position += Player->Velocity * dt;
	}

	if (i > 0)
	{
		Player->Color = glm::vec3(1.0f, 0.0f, 0.0f);
	}
	else
	{
		Player->Color = glm::vec3(1.0f, 1.0f, 1.0f);
	}
}