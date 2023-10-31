#include "bullet.hpp"

void Cosmic::Bullet::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
    desiredTag = Engine::ColliderManager::getTag("Asteroid");
    Engine::CircleCollider* collider = getActor()->addComponent<Engine::CircleCollider>();
    collider->setTag(Engine::ColliderManager::getTag("Bullet"));
    collider->setRadius(0.7f);
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

void Cosmic::Bullet::onCollisionEnter(Engine::Collider* collider)
{
    if(collider->getTag() != desiredTag) return;

    collider->getActor()->setDestroy();
    getActor()->setDestroy();
}