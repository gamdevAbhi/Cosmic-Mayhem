#include "follower.hpp"

void Cosmic::Follower::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
}

void Cosmic::Follower::lateUpdate()
{
    move();
}

void Cosmic::Follower::move()
{
    glm::vec3 difference = target->getPosition(true) - transform->getPosition(true);
    glm::vec3 direction = glm::normalize(difference);
    direction.z = 0.0f;

    glm::vec3 move = direction;
    move *= Engine::Time::getDeltaTime() * followSpeed;

    glm::vec3 finalPosition = transform->getPosition(true) + move;
    float length = glm::length(target->getPosition(true) - finalPosition);

    if(length > maxLength)
    {
        float diff = length - maxLength;
        finalPosition = transform->getPosition(true) + glm::vec3(direction.x * diff,
        direction.y * diff, 0.0f);
    }

    transform->setPosition(true, finalPosition);
}