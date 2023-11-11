#include "follower.hpp"

// ataching the references
void Cosmic::Follower::initialize(Engine::Transform* target)
{
    transform = getActor()->getComponent<Engine::Transform>();
    this->target = target;

    glm::vec3 pos = target->getWorldPosition();
    pos.z = 3.f;

    transform->setWorldPosition(pos);
}

// moving the follower to the target
void Cosmic::Follower::lateUpdate()
{
    transform->setParent(target);

    glm::vec3 position = transform->getLocalPosition();
    float newY = 0.0f;

    if(position.y < 0.f) 
    {
        newY = position.y + (Engine::Time::getDeltaTime() * followSpeed);
        if(newY > 0.f) newY = 0.f;
    }
    else if(position.y > 0.f) 
    {
        newY = position.y - (Engine::Time::getDeltaTime() * followSpeed);
        if(newY < 0.f) newY = 0.f;
    }

    if(newY < -maxDistance) newY = -maxDistance;
    else if(newY > maxDistance) newY = maxDistance;

    transform->setLocalPosition(glm::vec3(0.f, newY, position.z));
    transform->setParent(nullptr);

    transform->setWorldRotation(target->getWorldRotation());
}