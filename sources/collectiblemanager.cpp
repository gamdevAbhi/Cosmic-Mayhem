#include "collectiblemanager.hpp"

void Cosmic::CollectibleManager::start()
{
    Engine::Actor* ship = Engine::Actor::getActor("Space Ship");
    target = ship->getComponent<Engine::Transform>();
    shiphandler = ship->getComponent<ShipHandler>();
}

void Cosmic::CollectibleManager::update()
{
    while(Cosmic::Collectibles::getCount() < max)
    {
        Engine::Actor* collectible = Engine::Actor::createActor("collectible");

        glm::vec3 origin(0.f);
        glm::vec2 targetPos = target->getPosition(true);

        origin.x = (targetPos.x - expand) + ((std::rand() % 100) / 100.f) * (expand * 2.f);
        origin.y = (targetPos.y - expand) + ((std::rand() % 100) / 100.f) * (expand * 2.f);

        collectible->getComponent<Engine::Transform>()->setPosition(true, origin);
        collectible->getComponent<Engine::Transform>()->setScale(true, glm::vec3(0.6f, 0.6f, 1.f));
        collectible->addComponent<Collectibles>()->target = target;
        collectible->getComponent<Collectibles>()->maxLength = std::sqrt((std::pow(expand, 2) + std::pow(expand, 2)));
        collectible->getComponent<Collectibles>()->shiphandler = shiphandler;
        collectible->addComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::collectible);
    }
}