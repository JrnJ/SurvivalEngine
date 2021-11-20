#version 330 core

layout(location = 0) out vec4 color;

in vec4 v_Position;
in vec4 v_Color;

uniform sampler2D sprite;
uniform vec4 spriteColor; // Has to be a uniform vec4

void main()
{
    color = spriteColor * texture(sprite, vec2(v_Position.zw));
}