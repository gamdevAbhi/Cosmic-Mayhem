#include "coin.hpp"

void Cosmic::Coin::start()
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

void Cosmic::Coin::onTriggerEnter(Engine::Collider* collider)
{
    if(collider->getTag() != desiredTag) return;

    shiphandler->addScore(value);

    getActor()->setDestroy(); 
}