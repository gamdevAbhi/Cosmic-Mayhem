#version 330 core

in vec2 coord;

uniform vec4 color;
uniform sampler2D sprite;

out vec4 fragColor;

void main()
{
    fragColor = texture(sprite, coord) * color;
}