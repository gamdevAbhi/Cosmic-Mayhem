#include <engine/transform.hpp>

void Engine::Transform::start()
{
    localPosition = glm::vec3(0.0f);
    localRotation = glm::vec3(0.0f);
    localScale = glm::vec3(1.0f);
}

// get the local or world right direction
glm::vec3 Engine::Transform::getRight(bool isWorld)
{
    if(isWorld) return glm::vec3(1.0f, 0.0f, 0.0f);
    else
    {
        glm::mat4 world_matrix = getMatrix();
        glm::vec3 local_right;

        local_right.x = world_matrix[0][0];
        local_right.y = world_matrix[0][1];
        local_right.z = world_matrix[0][2];

        return local_right;
    }
}

// get the local or world up direction
glm::vec3 Engine::Transform::getUp(bool isWorld)
{
    if(isWorld) return glm::vec3(0.0f, 1.0f, 0.0f);
    else
    {
        glm::mat4 world_matrix = getMatrix();
        glm::vec3 local_up;

        local_up.x = world_matrix[1][0];
        local_up.y = world_matrix[1][1];
        local_up.z = world_matrix[1][2];

        return local_up;
    }
}

// get the local or world forward direction
glm::vec3 Engine::Transform::getForward(bool isWorld)
{
    if(isWorld) return glm::vec3(0.0f, 0.0f, -1.0f);
    else
    {
        glm::mat4 world_matrix = getMatrix();
        glm::vec3 local_forward;

        local_forward.x = world_matrix[2][0];
        local_forward.y = world_matrix[2][1];
        local_forward.z = world_matrix[2][2];

        return local_forward;
    }
}

// get the local or world position of the transform
glm::vec3 Engine::Transform::getPosition(bool isWorld)
{
    if(isWorld == false) return localPosition;
    else
    {
        glm::vec3 worldPosition;
        glm::mat4 worldMatrix = getMatrix();
        
        worldPosition.x = worldMatrix[3][0];
        worldPosition.y = worldMatrix[3][1];
        worldPosition.z = worldMatrix[3][2];

        return worldPosition;
    }
}

// get the local or world rotation of the transform
glm::vec3 Engine::Transform::getRotation(bool isWorld)
{
    if(isWorld == false) return localRotation;
    else
    {
        glm::vec3 worldRotation;
        glm::vec3 worldScale = getScale(true);
        glm::mat4 worldMatrix = getMatrix();
        glm::mat3 rotationMatrix;

        rotationMatrix[0] = worldMatrix[0] / worldScale.x;
        rotationMatrix[1] = worldMatrix[1] / worldScale.y;
        rotationMatrix[2] = worldMatrix[2] / worldScale.z;
        
        float roll = 0;
        float pitch = 0;
        float yaw = 0;

        if(rotationMatrix[0][2] != -1 && rotationMatrix[0][2] != 1)
        {
            pitch = -1 * glm::asin(rotationMatrix[0][2]);
            roll = glm::atan2(rotationMatrix[1][2] / glm::cos(pitch), 
            rotationMatrix[2][2] / glm::cos(pitch));
            yaw = glm::atan2(rotationMatrix[0][1] / glm::cos(pitch), 
            rotationMatrix[0][0] / glm::cos(pitch));
        }
        else
        {
            if(rotationMatrix[0][2] == -1)
            {
                pitch = glm::pi<float>() / 2.0f;
                roll = yaw + glm::atan2(rotationMatrix[1][0], rotationMatrix[2][0]);
            }
            else
            {
                pitch = -glm::pi<float>() / 2.0f;
                roll = -1.0f * yaw + glm::atan2(-1.0f * rotationMatrix[1][0], -1.0f * rotationMatrix[2][0]);
            }
        }

        worldRotation = glm::vec3(roll * 180.0f / glm::pi<float>(), pitch * 180.0f / glm::pi<float>(), 
        yaw * 180.0f / glm::pi<float>());

        return worldRotation;
    }
}

// get the local or world scale of the transform
glm::vec3 Engine::Transform::getScale(bool isWorld)
{
    if(isWorld == false) return localScale;
    else
    {
        glm::vec3 worldScale;
        glm::mat4 worldMatrix = getMatrix();

        worldScale.x = glm::sqrt(worldMatrix[0][0] * worldMatrix[0][0] + worldMatrix[0][1] * worldMatrix[0][1] 
        + worldMatrix[0][2] * worldMatrix[0][2]);
        worldScale.y = glm::sqrt(worldMatrix[1][0] * worldMatrix[1][0] + worldMatrix[1][1] * worldMatrix[1][1] 
        + worldMatrix[1][2] * worldMatrix[1][2]);
        worldScale.z = glm::sqrt(worldMatrix[2][0] * worldMatrix[2][0] + worldMatrix[2][1] * worldMatrix[2][1] 
        + worldMatrix[2][2] * worldMatrix[2][2]);

        return worldScale;
    }
}

// get the world matrix of the transform
glm::mat4 Engine::Transform::getMatrix()
{
    glm::mat4 translate(1.0f);
    glm::mat4 rotation(1.0f);
    glm::mat4 scale(1.0f);

    translate = glm::translate(translate, localPosition);
    rotation = glm::mat4_cast(glm::quat(localRotation));
    scale = glm::scale(scale, localScale);

    glm::mat4 local_transform = translate * rotation * scale;
    glm::mat4 world_transform = (parent != nullptr)? parent->getMatrix() * local_transform : local_transform;

    return world_transform;
}

// set the local or world position of the transform
void Engine::Transform::setPosition(bool isWorld, glm::vec3 position)
{
    if(isWorld == false) localPosition = position;
    else
    {
        glm::vec3 world_position = getPosition(true);
        localPosition += position - world_position;
    }
}

// set the local or world rotation of the transform
void Engine::Transform::setRotation(bool isWorld, glm::vec3 rotation)
{
    if(isWorld == false) localRotation = rotation;
    else
    {
        glm::vec3 world_rotation = getRotation(true);
        localRotation += rotation - world_rotation;
    }
}

// set the local or world scale of the transform
void Engine::Transform::setScale(bool isWorld, glm::vec3 scale)
{
    if(isWorld == false) localScale = scale;
    else
    {
        glm::vec3 world_scale = getScale(true);
        localScale += scale - world_scale;
    }
}

// set the parent transform
void Engine::Transform::setParent(Engine::Transform* transform)
{
    parent = transform;
}

// get the parent transform
Engine::Transform* Engine::Transform::getParent()
{
    return parent;
}