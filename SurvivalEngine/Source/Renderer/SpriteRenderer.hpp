#ifndef SPRITERENDERER_HPP
#define SPRITERENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture2D.hpp"
#include "Shader.hpp"
#include "../Components/Renderable.hpp"


class SpriteRenderer
{
public:
    // Constructor & Destructor
    SpriteRenderer(Shader& shader, size_t maxEntites);
    ~SpriteRenderer();

    // Draws a quad based on the sprite
    void DrawSprite(glm::vec2 position, Renderable renderable, glm::vec2 scale, float rotation, Texture2D texture);
    //void DrawBatch();

private:
    const size_t MaxQuadCount;// = 576
    const size_t MaxVertexCount;// = MaxQuadCount * 4;
    const size_t MaxIndexCount;// = MaxQuadCount * 6;

    // Render state
    Shader _shader;
    unsigned int _quadVBO; // Vertex Buffer
    unsigned int _quadVAO; // Vertex Array
    unsigned int _quadIB;  // Indices Buffer

    // Initialize vertex data
    void initRenderData();
};

#endif