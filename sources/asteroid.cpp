#include "asteroid.hpp"

int Cosmic::Asteroid::getCount()
{
    return count;
}

void Cosmic::Asteroid::start()
{
    speed = minSpeed + ((std::rand() % 100) / 100.f) * (maxSpeed - minSpeed);
    asteroidTag = Engine::ColliderManager::getTag("Asteroid");
    spaceshipTag = Engine::ColliderManager::getTag("Space Ship");

    transform = getActor()->getComponent<Engine::Transform>();

    Engine::BoxCollider* collider = getActor()->addComponent<Engine::BoxCollider>();
    collider->setBoundary(0.8f, 0.8f, 0.8f, 0.8f);
    collider->setTag(asteroidTag);
    count++;
}

void Cosmic::Asteroid::update()
{
    glm::vec3 targetPos = target->getPosition(true);
    glm::vec3 pos = transform->getPosition(true);

    if(glm::length(targetPos - pos) >= maxDistance) getActor()->setDestroy();
    else
    {
        glm::vec3 offset = direction;
        offset *= Engine::Time::getDeltaTime() * speed;
        
        transform->setPosition(true, transform->getPosition(true) + offset);
    }
}

void Cosmic::Asteroid::onCollisionEnter(Engine::BoxCollider* collider)
{
    if(collider->getTag() == asteroidTag)
    {
        direction = glm::vec3(direction.y, -direction.x, direction.z);
    }
    else if(collider->getTag() == spaceshipTag)
    {
        Engine::Time::timeScale = 0.f;
    }
}

void Cosmic::Asteroid::onDestroy()
{
    count--;
}