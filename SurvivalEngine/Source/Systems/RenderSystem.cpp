#include "RenderSystem.hpp"

#include "../ECS/Coordinator.hpp"
#include "../ResourceManager.hpp"
#include "../Renderer/SpriteRenderer.hpp"

extern Coordinator _coordinator;

struct Vertex
{
    glm::vec2 Position;
    glm::vec2 TexCoords;
    glm::vec4 Color;
};

static Vertex* CreateSprite(Vertex* target, float x, float y, Renderable renderable)
{
    // Left Bottom
    target->Position = { x, y + 1.0f };
    target->TexCoords = { renderable.TexLeftTop.x, renderable.TexRightBottom.y }; // { 0.5f, 0.5f };
    target->Color = renderable.Color; // { 0.0f, 0.0f, 1.0f, 1.0f };
    target++;

    // Right Bottom
    target->Position = { x + 1.0f, y + 1.0f };
    target->TexCoords = { renderable.TexRightBottom.x, renderable.TexRightBottom.y }; // { 0.75f, 0.5f };
    target->Color = renderable.Color; // { 0.0f, 1.0f, 1.0f, 1.0f };
    target++;

    // Right Top
    target->Position = { x + 1.0f, y + 0.0f };
    target->TexCoords = { renderable.TexRightBottom.x, renderable.TexLeftTop.y }; // { 0.75f, 0.25f };
    target->Color = renderable.Color; // { 0.0f, 1.0f, 0.0f, 1.0f };
    target++;

    // Left Top
    target->Position = { x, y };
    target->TexCoords = { renderable.TexLeftTop.x, renderable.TexLeftTop.y }; // { 0.5f, 0.25f };
    target->Color = renderable.Color; // { 1.0f, 0.0f, 0.0f, 1.0f };
    target++;

    return target;
}

const size_t maxBatch = 100; // 800+ is the max

RenderSystem::RenderSystem()
	: MaxQuadCount(maxBatch * 4), MaxVertexCount(maxBatch * 4 * 4), MaxIndexCount(maxBatch * 4 * 6)
{
	// Load Shaders
	ResourceManager::LoadShader("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/shaders/sprite.vs.glsl", "C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/shaders/sprite.fs.glsl", nullptr, "sprite");
    ResourceManager::GetShader("sprite").Use();// .SetInteger("image", 0);Tot 
    this->_shader = ResourceManager::GetShader("sprite");

    // Initialize Render Data
    this->initRenderData();

	// Load Sprite Sheet / Atlas
	ResourceManager::LoadTexture("C:/Dev/cpp/SurvivalEngine/SurvivalEngine/SurvivalEngine/Assets/textures/atlas.png", "Atlas", true);
}

RenderSystem::~RenderSystem()
{
    glDeleteVertexArrays(1, &this->_quadVAO);
}

/// <summary>
/// Use constructor if posible
/// </summary>
void RenderSystem::Init()
{

}

void RenderSystem::Update(float dt)
{
	// Loop through entities
	// get entites from systems
	// changing for loop after debugging :D lol
    uint32_t indexCount = 0;
    std::vector<Vertex> vertices(MaxQuadCount);
    Vertex* buffer = vertices.data();
    Texture2D texture = ResourceManager::GetTexture("Atlas");

    for (auto const& entity : mEntities)
    {
        glm::vec2 position = _coordinator.GetComponent<Transform>(entity).Position;
        Renderable renderable = _coordinator.GetComponent<Renderable>(entity);

        buffer = CreateSprite(buffer, position.x, position.y, renderable);
        indexCount += 6;

        if (indexCount == maxBatch * 6 || entity == mEntities.size() - 1)
        {
            float scale = _coordinator.GetComponent<Transform>(entity).Scale.x;

            glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

            this->_shader.Use();

            // Model
            glm::mat4 model = glm::mat4(1.0f);

            // Calculate Model
            // Transformation order: scale, rotation, final translation happens; reversed order)
            // Set Position
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));

            // Move origin of rotation to center of the quad
            model = glm::translate(model, glm::vec3(0.5f * scale, 0.5f * scale, 0.0f));

            // Rotate quad
            model = glm::rotate(model, glm::radians(0.0f /* Rotation */), glm::vec3(0.0f, 0.0f, 1.0f));

            // Move origin back
            model = glm::translate(model, glm::vec3(-0.5f * scale, -0.5f * scale, 0.0f));

            // Apply scaling
            model = glm::scale(model, glm::vec3(scale, scale, 1.0f));

            // Apply model to Shader
            this->_shader.SetMatrix4("u_Model", model);

            // Bind Texture
            glActiveTexture(GL_TEXTURE0);
            texture.Bind();

            glBindVertexArray(this->_quadVAO);
            glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

            // Reset Some Things
            indexCount = 0;
            vertices.empty();
            buffer = vertices.data();
        }
    }
}

void RenderSystem::DrawSprite(glm::vec2 position, Renderable renderable, glm::vec2 scale, float rotation, Texture2D texture)
{
    uint32_t indexCount = 0;
    std::vector<Vertex> vertices(MaxQuadCount);
    Vertex* buffer = vertices.data();

    buffer = CreateSprite(buffer, position.x, position.y, renderable);
    indexCount += 6;

    glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    this->_shader.Use();

    // Model
    glm::mat4 model = glm::mat4(1.0f);

    // Calculate Model
    // Transformation order: scale, rotation, final translation happens; reversed order)
    // Set Position
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));

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

    // Bind Texture
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->_quadVAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

void RenderSystem::DrawBatch()
{
    //uint32_t indexCount = 0;
    //std::vector<Vertex> vertices(MaxQuadCount);
    //Vertex* buffer = vertices.data();

    //buffer = CreateSprite(buffer, position.x, position.y, renderable);
    //indexCount += 6;

    //glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

    //this->_shader.Use();

    //// Model
    //glm::mat4 model = glm::mat4(1.0f);

    //// Calculate Model
    //// Transformation order: scale, rotation, final translation happens; reversed order)
    //// Set Position
    //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));

    //// Move origin of rotation to center of the quad
    //model = glm::translate(model, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));

    //// Rotate quad
    //model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));

    //// Move origin back
    //model = glm::translate(model, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));

    //// Apply scaling
    //model = glm::scale(model, glm::vec3(scale, 1.0f));

    //// Apply model to Shader
    //this->_shader.SetMatrix4("u_Model", model);

    //// Bind Texture
    //glActiveTexture(GL_TEXTURE0);
    //texture.Bind();

    //glBindVertexArray(this->_quadVAO);
    //glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
}

/// <summary>
/// Inititializes the render data
/// </summary>
void RenderSystem::initRenderData()
{
    glGenVertexArrays(1, &this->_quadVAO);

    glGenBuffers(1, &_quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, _quadVBO);
    glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    glBindVertexArray(this->_quadVAO);

    // Vertex
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    // Texture
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(1);

    // Color
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));
    glEnableVertexAttribArray(2);

    // Generate Indices Buffer
    std::vector<uint32_t> indices(MaxIndexCount);
    uint32_t offset = 0;
    for (size_t i = 0; i < MaxIndexCount; i += 6)
    {
        // Order of vertex points
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;

        offset += 4;
    }

    glGenBuffers(1, &_quadIB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _quadIB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Vertex), &indices[0], GL_STATIC_DRAW);

    // Draw Mode - Optional
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Fill
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe

    // Unbind VBO/VAO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
