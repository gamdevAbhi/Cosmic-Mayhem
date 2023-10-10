#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 camera_transform;
uniform mat4 world_transform;

void main()
{
    gl_Position = camera_transform * world_transform * vec4(aPos, 1.0f);
}