#include <engine/transform.hpp>
#include <iostream>

void Engine::Transform::start()
{
    position = glm::vec3(0.0f);
    rotation = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
}