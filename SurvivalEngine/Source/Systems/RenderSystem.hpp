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

class RenderSystem : public System
{
public:
    RenderSystem();
    ~RenderSystem();

	void Init();

	void Update(float dt, float scale);
    void DrawSprite(glm::vec2 position, Renderable renderable, glm::vec2 scale, float rotation, Texture2D texture);

    void DrawBatch();

private:
	//Entity _camera;
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
