#include <engine/transform.hpp>

// start function
void Engine::Transform::start()
{
    localPosition = glm::vec3(0.0f);
    localRotation = glm::vec3(0.0f);
    localScale = glm::vec3(1.0f);

    updateWorldMatrix();
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

// get oriented vector from the current orientation
glm::vec3 Engine::Transform::getOrientedVector(glm::vec3 vector)
{
    glm::vec3 orientedVector(0.0f);
    orientedVector += vector.x * getRight(false);
    orientedVector += vector.y * getUp(false);
    orientedVector += vector.z * getForward(true);
    return orientedVector;
}

// get the world position respective to the local transform
glm::vec3 Engine::Transform::getWorldPosAt(glm::vec3 localOffset)
{
    glm::mat4 translate(1.0f);
    glm::mat4 rotation(1.0f);
    glm::mat4 scale(1.0f);

    translate = glm::translate(translate, localPosition + getOrientedVector(localOffset));
    rotation = glm::mat4_cast(glm::quat(localRotation));
    scale = glm::scale(scale, localScale);

    glm::mat4 matrix = translate * rotation * scale;
    glm::mat4 worldMatrix = (parent != nullptr)? parent->getMatrix() * matrix : matrix;

    return glm::vec3(worldMatrix[3][0], worldMatrix[3][1], worldMatrix[3][2]);
}

// get the local or world position of the transform
glm::vec3 Engine::Transform::getPosition(bool isWorld)
{
    if(isWorld == false) return localPosition;
    else return worldPosition;
}

// get the local or world rotation of the transform
glm::vec3 Engine::Transform::getRotation(bool isWorld)
{
    if(isWorld == false) return localRotation;
    else return worldRotation;
}

// get the local or world scale of the transform
glm::vec3 Engine::Transform::getScale(bool isWorld)
{
    if(isWorld == false) return localScale;
    else return worldScale;
}

// calculate the position from the matrix
glm::vec3 Engine::Transform::calculatePosition(glm::mat4 matrix)
{
    glm::vec3 position;
    
    position.x = matrix[3][0];
    position.y = matrix[3][1];
    position.z = matrix[3][2];
    
    return position;
}

// calculating the rotation from the matrix
glm::vec3 Engine::Transform::calculateRotation(glm::mat4 matrix)
{
    glm::mat3 rotationMatrix;
    glm::vec3 scale = calculateScale(matrix);

    rotationMatrix[0] = matrix[0] / scale.x;
    rotationMatrix[1] = matrix[1] / scale.y;
    rotationMatrix[2] = matrix[2] / scale.z;
    
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

    glm::vec3 rotation = glm::vec3(roll * 180.0f / glm::pi<float>(), pitch * 180.0f / glm::pi<float>(), 
    yaw * 180.0f / glm::pi<float>());
    
    return rotation;
}

// for calculating the scale from the matrix
glm::vec3 Engine::Transform::calculateScale(glm::mat4 matrix)
{
    glm::vec3 scale;

    scale.x = glm::sqrt(matrix[0][0] * matrix[0][0] + matrix[0][1] * matrix[0][1] 
    + matrix[0][2] * matrix[0][2]);
    scale.y = glm::sqrt(matrix[1][0] * matrix[1][0] + matrix[1][1] * matrix[1][1] 
    + matrix[1][2] * matrix[1][2]);
    scale.z = glm::sqrt(matrix[2][0] * matrix[2][0] + matrix[2][1] * matrix[2][1] 
    + matrix[2][2] * matrix[2][2]);

    return scale;
}

glm::vec3 Engine::Transform::fixRotation(glm::vec3 rotation)
{
    glm::vec3 fixRotation;

    fixRotation.x = (rotation.x - (int)rotation.x) + (int)rotation.x % 360;
    fixRotation.y = (rotation.y - (int)rotation.y) + (int)rotation.y % 360;
    fixRotation.z = (rotation.z - (int)rotation.z) + (int)rotation.z % 360;

    if(fixRotation.x < 0) fixRotation.x = 360.f + fixRotation.x;
    if(fixRotation.y < 0) fixRotation.y = 360.f + fixRotation.y;
    if(fixRotation.z < 0) fixRotation.z = 360.f + fixRotation.z;

    return fixRotation;
}

// update the world matrix of the transform
void Engine::Transform::updateWorldMatrix()
{
    glm::mat4 translate(1.0f);
    glm::mat4 rotation(1.0f);
    glm::mat4 scale(1.0f);

    translate = glm::translate(translate, localPosition);
    rotation = glm::mat4_cast(glm::quat(localRotation));
    scale = glm::scale(scale, localScale);

    localMatrix = translate * rotation * scale;
    worldMatrix = (parent != nullptr)? parent->getMatrix() * localMatrix : localMatrix;

    worldPosition = calculatePosition(worldMatrix);
    worldRotation = calculateRotation(worldMatrix);
    worldScale = calculateScale(worldMatrix);

    for(int i = 0; i < childs.size(); i++) childs[i]->updateWorldMatrix();

    for(int i = 0; i < refSiblings->size(); i++) (*refSiblings)[i]->onTransformChanged();
}

// update the local matrix of the transform
void Engine::Transform::updateLocalMatrix()
{
    glm::mat4 translate(1.0f);
    glm::mat4 rotation(1.0f);
    glm::mat4 scale(1.0f);

    translate = glm::translate(translate, worldPosition);
    rotation = glm::mat4_cast(glm::quat(worldRotation));
    scale = glm::scale(scale, worldScale);

    worldMatrix = translate * rotation * scale;
    localMatrix = (parent != nullptr)? glm::inverse(parent->getMatrix()) * worldMatrix : worldMatrix;

    localPosition = calculatePosition(localMatrix);
    localRotation = calculateRotation(localMatrix);
    localScale = calculateScale(localMatrix);

    for(int i = 0; i < childs.size(); i++) childs[i]->updateWorldMatrix();

    for(int i = 0; i < refSiblings->size(); i++) (*refSiblings)[i]->onTransformChanged();
}

// get the world matrix of the transform
glm::mat4 Engine::Transform::getMatrix()
{
    return worldMatrix;
}

// set the local or world position of the transform
void Engine::Transform::setPosition(bool isWorld, glm::vec3 position)
{
    if(isWorld == false) 
    {
        localPosition = position;
        updateWorldMatrix();
    }
    else
    {
        worldPosition = position;
        updateLocalMatrix();
    }
}

// set the local or world rotation of the transform
void Engine::Transform::setRotation(bool isWorld, glm::vec3 rotation)
{
    if(isWorld == false)
    {
        localRotation = fixRotation(rotation);
        updateWorldMatrix();
    }
    else
    {
        worldRotation = fixRotation(rotation);
        updateLocalMatrix();
    }
}

// set the local or world scale of the transform
void Engine::Transform::setScale(bool isWorld, glm::vec3 scale)
{
    if(isWorld == false)
    {
        localScale = scale;
        updateWorldMatrix();
    } 
    else
    {
        worldScale = scale;
        updateLocalMatrix();
    }
}

// set the parent transform
void Engine::Transform::setParent(Engine::Transform* transform)
{
    if(transform == this) 
    {
        Handler::debug("can't make parent of own transform", "transform");
        return;
    }

    for(int i = 0; i < childs.size(); i++)
    {
        if(childs[i] != transform) continue;
        Handler::debug("can't make parent of his own child", "transform");
        return;
    }

    if(parent != nullptr) parent->removeChild(this);
    if(transform != nullptr) transform->addChild(this);
    
    parent = transform;

    updateLocalMatrix();
}

// get the parent transform
Engine::Transform* Engine::Transform::getParent()
{
    return parent;
}

// get the child
Engine::Transform* Engine::Transform::getChild(int index)
{
    if(childs.size() <= index) Handler::error("child index is out of bound", "");
    return childs[index];
}

// get total childs size
int Engine::Transform::getChildsSize()
{
    return childs.size();
}

// set destroy
void Engine::Transform::setDestroy()
{
    Handler::error("can't destroy transform", "transform");
}

// add the child
void Engine::Transform::addChild(Transform* transform)
{
    childs.push_back(transform);
}

// remove the child from the transform
void Engine::Transform::removeChild(Transform* transform)
{
    for(int i = 0; i < childs.size(); i++)
    {
        if(childs[i] != transform) continue;
        childs.erase(childs.begin() + i);
        break;
    }
}