#include "GameObject.hpp"

/// <summary>
/// Default constructor
/// </summary>
GameObject::GameObject()
	: Position(0.0f, 0.0f), Size(1.0f, 1.0f), Sprite(), Color(glm::vec4(1.0f)), Rotation(0.0f), IsSolid(false){ }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec4 color)
	: Position(pos), Size(size), Sprite(sprite), Color(color), Rotation(0.0f), IsSolid(true) { }

/// <summary>
/// Draws the GameObject.Sprite to the screen
/// </summary>
/// <param name="renderer"></param>
void GameObject::Draw(SpriteRenderer& renderer, glm::mat4 projectionMatrix)
{
	renderer.DrawSprite(this->Sprite, this->Position, projectionMatrix, this->Size, this->Rotation, this->Color);
}