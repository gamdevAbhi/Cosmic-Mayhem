#include "healthbooster.hpp"

void Cosmic::HealthBooster::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
    Engine::CircleCollider* collider  = getActor()->addComponent<Engine::CircleCollider>();
    collider->setRadius(0.7f);
    collider->setTag(Engine::ColliderManager::getTag("Collectibles"));
    collider->setTrigger(true);
    desiredTag = Engine::ColliderManager::getTag("Space Ship");
    healthBooster = minHealthBooster + (((std::rand() % 100) / 100.f) * (maxHealthBooster - minHealthBooster));
    counts++;
}

void Cosmic::HealthBooster::onTriggerEnter(Engine::Collider* collider)
{
    if(collider->getTag() != desiredTag) return;

    shiphandler->getActor()->getComponent<Health>()->addHealth(healthBooster);

    getActor()->setDestroy(); 
}