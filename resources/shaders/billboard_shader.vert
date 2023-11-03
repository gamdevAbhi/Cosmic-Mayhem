#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 coord;

uniform mat4 screen_ortho;
uniform mat4 screen_transform;

void main()
{
    gl_Position = screen_ortho * screen_transform * vec4(aPos, 1.0f);
    coord = aUV;
}