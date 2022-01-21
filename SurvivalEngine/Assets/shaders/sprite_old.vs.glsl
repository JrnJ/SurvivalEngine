#version 430 core

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Color;

out vec3 v_Position;
out vec4 v_VertexColor;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

void main() 
{
    v_Position = vec3(a_Position, 0.0);
    v_VertexColor = vec4(a_Color.rgb, 1.0);
    gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 0.0, 1.0);
}
                                    