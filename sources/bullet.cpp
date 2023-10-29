#include "bullet.hpp"

void Cosmic::Bullet::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
    desiredTag = Engine::ColliderManager::getTag("Asteroid");
    Engine::BoxCollider* collider = getActor()->addComponent<Engine::BoxCollider>();
    collider->setTag(Engine::ColliderManager::getTag("Bullet"));
    collider->setBoundary(0.3f, 0.3f, 0.8f, 0.8f);
}

void Cosmic::Bullet::update()
{
    glm::vec3 targetPos = target->getPosition(true);
    glm::vec3 pos = transform->getPosition(true);

    if(glm::length(targetPos - pos) >= maxLength) getActor()->setDestroy();
    else
    {
        glm::vec3 offset = direction;
        offset *= Engine::Time::getDeltaTime() * speed;
        pos += offset;

        transform->setPosition(true, pos);
    }
}

void Cosmic::Bullet::onCollisionEnter(Engine::BoxCollider* collider)
{
    if(collider->getTag() != desiredTag) return;

    collider->getActor()->setDestroy();
    getActor()->setDestroy();
}