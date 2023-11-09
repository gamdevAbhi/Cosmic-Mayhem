#include <engine/camera.hpp>

// get the ortho of the camera
glm::mat4 Engine::Camera::getOrtho()
{
    return ortho;
}

// get the boundary of the camera
glm::vec2 Engine::Camera::getBoundary()
{
    glm::vec2 boundary;
    std::tuple<int, int> size = gameWindow->getSize();
    
    boundary.x = (std::get<0>(size) / orthographicSize) / 2.0f;
    boundary.y = (std::get<1>(size) / orthographicSize) / 2.0f;

    return boundary;
}

// get the per world to screen difference
glm::vec2 Engine::Camera::getPerWorldToScreen()
{
    std::tuple<int, int> size = gameWindow->getSize();
    glm::vec2 world_boundary = getBoundary();
    glm::vec2 screen_size = glm::vec2(std::get<0>(size), std::get<1>(size));

    return glm::vec2(screen_size.x / world_boundary.x, screen_size.y / world_boundary.y);
}

// get the screen pos from the world pos
glm::vec2 Engine::Camera::getWorldToScreenPos(glm::vec3 worldPosition)
{
    glm::vec4 clipSpace = getOrtho() * glm::vec4(worldPosition, 1.0f);
    glm::vec3 ndcSpace = glm::vec3(clipSpace.x, clipSpace.y, clipSpace.z);
    glm::vec2 viewSize = glm::vec2(std::get<0>(gameWindow->getSize()), std::get<1>(gameWindow->getSize()));

    if(clipSpace.w != 0.0) ndcSpace = ndcSpace / clipSpace.w;
    
    glm::vec2 screenSpace = (glm::vec2(ndcSpace.x + 1.0f, ndcSpace.y + 1.0f) / 2.0f) * viewSize;

    return screenSpace;
}

// get the world pos from the screen pos
glm::vec3 Engine::Camera::getScreenToWorldPos(glm::vec2 screenPos)
{
    std::tuple<int, int> size = gameWindow->getSize();

    float x = (std::get<0>(size) / orthographicSize) / 2.0f;
    float y = (std::get<1>(size) / orthographicSize) / 2.0f;

    glm::vec3 worldPos;
    glm::vec3 localPos;

    localPos.x = (screenPos.x / std::get<0>(size)) * x;
    localPos.y = (screenPos.y / std::get<1>(size)) * y;
    localPos.z = 0.0f;

    worldPos = transform->getWorldPosAt(localPos);

    return worldPos;
}

// get the orthographic size
float Engine::Camera::getOrthographicSize()
{
    return orthographicSize;
}

// get diagonal of camera window
float Engine::Camera::getDiagonal()
{
    std::tuple<int, int> size = gameWindow->getSize();

    float x = (std::get<0>(size) / orthographicSize) / 2.0f;
    float y = (std::get<1>(size) / orthographicSize) / 2.0f;

    return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
}

// set the orthographic size
void Engine::Camera::setOrthographicSize(float orthographicSize)
{
    this->orthographicSize = orthographicSize;
    updateOrtho();
}

// get the rendering camera
Engine::Camera* Engine::Camera::getRenderCamera()
{
    return renderCamera;
}

// start function
void Engine::Camera::start()
{
    renderCamera = this;
    updateOrtho();
}

// on transform changed function
void Engine::Camera::onTransformChanged()
{
    updateOrtho();
}

// set destroy
void Engine::Camera::setDestroy()
{
    Handler::debug("can't destroy camera Component", "Camera");
}

// update the ortho of the camera
void Engine::Camera::updateOrtho()
{
    glm::mat4 projection(1.0f);
    glm::mat4 view(1.0f);

    std::tuple<int, int> size = gameWindow->getSize();

    float x = (std::get<0>(size) / orthographicSize) / 2.0f;
    float y = (std::get<1>(size) / orthographicSize) / 2.0f;

    projection = glm::ortho(-x, x, -y, y, nearClip, farClip);
    
    glm::vec3 camPos = transform->getWorldPosition();

    view = transform->getMatrix();
    view = glm::inverse(view);

    ortho = projection * view;
}