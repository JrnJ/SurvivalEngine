#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

#include "../ECS/System.hpp"
#include "../Components/Components.hpp"
#include "../Renderer/Texture2D.hpp"
#include "../Renderer/Shader.hpp"

struct Vertex
{
    glm::vec2 Position;
    glm::vec2 TexCoords;
    glm::vec4 Color;
};

class RenderSystem : public System
{
public:
    RenderSystem();
    ~RenderSystem();

	void Init();

	void Update(float dt);
    void DrawSprite(glm::vec2 position, Renderable renderable, glm::vec2 scale, float rotation, Texture2D texture);

    void DrawBatch(std::vector<Vertex> vertices, uint32_t indexCount, Shader* shader, Texture2D* texture);

    const float GetScale() const { return _scale; }
    void SetScale(const float scale) { _scale = scale; }

private:
    // 
    float _scale = 0.0f;

    // Textures
    Texture2D _mainAtlasTexture;

	//Entity _camera;
    const size_t MaxQuadCount;// = 576
    const size_t MaxVertexCount;// = MaxQuadCount * 4;
    const size_t MaxIndexCount;// = MaxQuadCount * 6;

    // Render state
    Shader _spriteShader;
    Shader _texturelessShader;
    Shader _lineShader;
    unsigned int _quadVBO; // Vertex Buffer
    unsigned int _quadVAO; // Vertex Array
    unsigned int _quadIB;  // Indices Buffer

    // Initialize vertex data
    void initRenderData();
};

#endif
