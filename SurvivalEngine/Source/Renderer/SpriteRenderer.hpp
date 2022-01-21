#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.hpp"
#include "shader.hpp"


class SpriteRenderer
{
public:
    // Constructor & Destructor
    SpriteRenderer(Shader& shader);
    ~SpriteRenderer();

    // Draws a quad based on the sprite
    void DrawSprite(glm::vec2 position, glm::vec2 scale, float rotation, Texture2D texture);

private:
    // Render state
    Shader _shader;
    unsigned int _quadVBO; // Vertex Buffer
    unsigned int _quadVAO; // Vertex Array
    unsigned int _quadIB;  // Indices Buffer

    // Initialize vertex data
    void initRenderData();
};

#endif