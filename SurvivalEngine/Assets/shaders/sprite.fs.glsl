#version 430 core

layout(location = 0) out vec4 color;

in vec3 v_Position;

uniform sampler2D sprite;
uniform vec4 spriteColor;

void main()
{
    color = spriteColor * texture(sprite, vec2(v_Position.xy));
}