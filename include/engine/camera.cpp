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

// get the screen pos from the world pos
glm::vec2 Engine::Camera::getWorldToScreenPos(glm::vec3 worldPosition)
{
    Engine::Transform* transform = getActor()->getComponent<Engine::Transform>();
    glm::vec3 distance = worldPosition - transform->getPosition(true);

    glm::vec2 screenPos;
    screenPos.x = distance.x * screenToWorldX * orthographicSize;
    screenPos.y = distance.y * screenToWorldY * orthographicSize;

    return screenPos;
}

// get the world pos from the screen pos
glm::vec3 Engine::Camera::getScreenToWorldPos(glm::vec2 screenPos)
{
    Engine::Transform* transform = getActor()->getComponent<Engine::Transform>();

    glm::vec3 worldPos;
    worldPos.x = screenPos.x / (screenToWorldX * orthographicSize);
    worldPos.y = screenPos.y / (screenToWorldY * orthographicSize);
    worldPos.z = 0.0f;

    return transform->getPosition(true) + worldPos;
}

// get if the transform visible in screen
bool Engine::Camera::isOnScreen(Engine::Transform* transform)
{
    int width = std::get<0>(gameWindow->getSize());
    int height = std::get<1>(gameWindow->getSize());

    glm::vec3 scale = transform->getScale(true);
    
    std::vector<glm::vec3> vertices;
    
    vertices.push_back(transform->getWorldPosAt(glm::vec3(-scale.x, scale.y, 0.0f)));
    vertices.push_back(transform->getWorldPosAt(glm::vec3(scale.x, scale.y, 0.0f)));
    vertices.push_back(transform->getWorldPosAt(glm::vec3(-scale.x, -scale.y, 0.0f)));
    vertices.push_back(transform->getWorldPosAt(glm::vec3(scale.x, -scale.y, 0.0f)));

    for(int i = 0; i < vertices.size(); i++)
    {
        glm::vec2 screenPos = getWorldToScreenPos(vertices[i]);

        if(-width <= screenPos.x && screenPos.x <= width && 
        -height <= screenPos.y && screenPos.y < height) return true;
    }

    return false;
}

// get the rendering camera
Engine::Camera* Engine::Camera::getRenderCamera()
{
    return renderCamera;
}