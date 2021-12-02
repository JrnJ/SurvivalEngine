#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(Shader& shader)
{
    this->_shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->_quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 scale, float rotation, glm::vec4 color)
{
    this->_shader.Use();

    // Model
    glm::mat4 model = glm::mat4(1.0f);

    // Calculate Model
    // Transformation order: scale, rotation, final translation happens; reversed order)
    // Set Position
    model = glm::translate(model, glm::vec3(position, 1.0f));

    // Move origin of rotation to center of the quad
    model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));

    // Rotate quad
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    // Move origin back
    model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

    // Apply scaling
    model = glm::scale(model, glm::vec3(scale, 1.0f));

    // Apply model to Shader
    this->_shader.SetMatrix4("u_Model", model);

    // render textured quad
    this->_shader.SetVector4f("spriteColor", color);

    // Bind Texture
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    // Configure VAO/VBO
    unsigned int VBO;

    float vertices[] = {
        // pos       // tex       // color
        0.0f, 1.0f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f, // top left
        1.0f, 0.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f, // top right
        0.0f, 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f, // bottom left

        0.0f, 1.0f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f, // top right
        1.0f, 1.0f,  1.0f, 1.0f,  0.0f, 1.0f, 1.0f, // bottom right
        1.0f, 0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f, // bottom left
    };

    glGenVertexArrays(1, &this->_quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->_quadVAO);

    // Vertex
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Draw Mode - Optional
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Fill
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe

    // Unbind VBO/VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}