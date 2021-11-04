#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../Renderer/texture.hpp"
#include "../Renderer/sprite_renderer.hpp"

class GameObject
{
public:
	// Properties
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec3 Color;
	float Rotation;
	bool IsSolid;
	bool Destroyed;

	// Rendering
	Texture2D Sprite;

	// Structs
	GameObject(); // Default
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, 
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

	// Draw Sprite
	virtual void Draw(SpriteRenderer& renderer);
};

#endif