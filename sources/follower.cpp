#include "follower.hpp"

void Cosmic::Follower::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
}

void Cosmic::Follower::lateUpdate()
{
    glm::vec3 difference = target->getPosition(true) - transform->getPosition(true);
    double length = glm::sqrt(difference.x * difference.x + difference.y * difference.y + difference.z * difference.z);
    glm::vec3 direction = glm::vec3(difference.x / length, difference.y / length, difference.z / length);
    direction *= Engine::Time::getDeltaTime() * followSpeed;
    direction.z = 0.f;
    
    transform->setPosition(true, transform->getPosition(true) + direction);
}