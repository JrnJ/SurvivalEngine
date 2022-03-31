#version 430 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TextureVertex;
layout (location = 2) in vec4 a_Color;

out vec2 v_TextureVertex;
out vec4 v_VertexColor;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main() 
{
    v_TextureVertex = a_TextureVertex;
    v_VertexColor = a_Color;
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 0.0, 1.0);
}
                                    