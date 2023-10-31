#include "collectibles.hpp"

int Cosmic::Collectibles::getCount()
{
    return counts;
}

void Cosmic::Collectibles::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
    Engine::CircleCollider* collider  = getActor()->addComponent<Engine::CircleCollider>();
    collider->setRadius(0.7f);
    collider->setTag(Engine::ColliderManager::getTag("Collectibles"));
    collider->setTrigger(true);
    desiredTag = Engine::ColliderManager::getTag("Space Ship");
    value = 25 + (std::rand() % 100);
    counts++;
}

void Cosmic::Collectibles::update()
{
    glm::vec2 targetPos = target->getPosition(true);
    glm::vec2 pos = transform->getPosition(true);

    if(glm::length(targetPos - pos) >= maxLength) getActor()->setDestroy();
}

void Cosmic::Collectibles::onTriggerEnter(Engine::Collider* collider)
{
    if(collider->getTag() != desiredTag) return;

    shiphandler->addScore(value);

    getActor()->setDestroy(); 
}

void Cosmic::Collectibles::onDestroy()
{
    counts--;
}