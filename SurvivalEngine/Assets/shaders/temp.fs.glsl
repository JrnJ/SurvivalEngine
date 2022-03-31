#version 430 core

layout (location = 0) out vec4 color;

in vec2 v_TextureVertex;
in vec4 v_VertexColor;

uniform sampler2D sprite;

void main()
{
    color = v_VertexColor * texture(sprite, v_TextureVertex);
}