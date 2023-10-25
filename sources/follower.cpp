#include "follower.hpp"

// ataching the references
void Cosmic::Follower::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
}

// moving the follower to the target
void Cosmic::Follower::lateUpdate()
{
    transform->setParent(target);

    glm::vec3 position = transform->getPosition(false);
    float newY = position.y + (Engine::Time::getDeltaTime() * followSpeed);

    if(newY < -maxDistance) newY = -maxDistance;
    else if(newY > 0.f) newY = 0.f;

    transform->setPosition(false, glm::vec3(0.f, newY, position.z));
    transform->setParent(nullptr);

    transform->setRotation(true, target->getRotation(true));
}