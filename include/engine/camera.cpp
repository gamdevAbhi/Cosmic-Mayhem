#include <engine/camera.hpp>

// get the matrix of camera
glm::mat4 Engine::Camera::getMatrix()
{
    glm::mat4 projection(1.0f);
    glm::mat4 view(1.0f);

    Engine::Transform* transform = getActor()->getComponent<Engine::Transform>();

    std::tuple<int, int> size = gameWindow->getSize();

    float x = (std::get<0>(size) / orthographicSize) / 2.0f;
    float y = (std::get<1>(size) / orthographicSize) / 2.0f;

    projection = glm::ortho(-x, x, -y, y, nearClip, farClip);

    glm::vec3 camPos = transform->getPosition(true);

    view = glm::lookAt(camPos, glm::vec3(camPos.x, camPos.y, 0.0f), transform->getUp(true));

    return projection * view;
}

// get diagonal of camera window
float Engine::Camera::getDiagonal()
{
    return std::sqrt(std::pow(worldToScreenX / orthographicSize, 2) + 
    std::pow(worldToScreenY / orthographicSize, 2));
}

// get the screen pos from the world pos
glm::vec2 Engine::Camera::getWorldToScreenPos(glm::vec3 worldPosition)
{
    glm::vec4 clipSpace = getMatrix() * glm::vec4(worldPosition, 1.0f);
    glm::vec3 ndcSpace = glm::vec3(clipSpace.x, clipSpace.y, clipSpace.z);
    glm::vec2 viewSize = glm::vec2(std::get<0>(gameWindow->getSize()), std::get<1>(gameWindow->getSize()));

    if(clipSpace.w != 0.0) ndcSpace = ndcSpace / clipSpace.w;
    
    glm::vec2 screenSpace = (glm::vec2(ndcSpace.x + 1.0f, ndcSpace.y + 1.0f) / 2.0f) * viewSize;

    return screenSpace;
}

// get the world pos from the screen pos
glm::vec3 Engine::Camera::getScreenToWorldPos(glm::vec2 screenPos)
{
    Engine::Transform* transform = getActor()->getComponent<Engine::Transform>();

    glm::vec3 worldPos;
    worldPos.x = screenPos.x / (screenToWorldX * orthographicSize);
    worldPos.y = screenPos.y / (screenToWorldY * orthographicSize);
    worldPos.z = 0.0f;

    return transform->getPosition(true) + transform->getOrientedVector(worldPos);
}

// get the rendering camera
Engine::Camera* Engine::Camera::getRenderCamera()
{
    return renderCamera;
}