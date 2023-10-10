#include <engine/camera.hpp>

// get the matrix of camera
glm::mat4 Engine::Camera::getMatrix()
{
    glm::mat4 projection(1.0f);
    glm::mat4 view(1.0f);

    Engine::Transform* transform = getActor()->getComponent<Engine::Transform>();

    if(projectionMode == orthographic)
    {
        std::tuple<int, int> size = gameWindow->getSize();

        float x = (std::get<0>(size) / orthographicSize) / 2.0f;
        float y = (std::get<1>(size) / orthographicSize) / 2.0f;

        projection = glm::ortho(-x, x, -y, y, nearClip, farClip);

        glm::vec3 camPos = transform->position;

        view = glm::lookAt(camPos, glm::vec3(camPos.x, camPos.y, 0.0f), transform->up);
    }
    else
    {
        std::tuple<int, int> size = gameWindow->getSize();

        float x = std::get<0>(size);
        float y = std::get<1>(size);

        projection = glm::perspective(fov, x / y, nearClip, farClip);
        view = glm::lookAt(transform->position, transform->position + transform->forward, transform->up);
    }

    return projection * view;
}

// get the rendering camera
Engine::Camera* Engine::Camera::getRenderCamera()
{
    return renderCamera;
}