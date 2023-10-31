#include "collectiblemanager.hpp"

void Cosmic::CollectibleManager::start()
{
    Engine::Actor* ship = Engine::Actor::getActor("Space Ship");
    target = ship->getComponent<Engine::Transform>();
    shiphandler = ship->getComponent<ShipHandler>();
}

void Cosmic::CollectibleManager::update()
{
    while(Cosmic::Coin::getCount() < max)
    {
        Engine::Actor* collectible = Engine::Actor::createActor("collectible");

        glm::vec3 origin(0.f);
        glm::vec2 targetPos = target->getPosition(true);

        origin.x = (targetPos.x - expand) + ((std::rand() % 100) / 100.f) * (expand * 2.f);
        origin.y = (targetPos.y - expand) + ((std::rand() % 100) / 100.f) * (expand * 2.f);

        collectible->getComponent<Engine::Transform>()->setPosition(true, origin);
        collectible->getComponent<Engine::Transform>()->setScale(true, glm::vec3(0.6f, 0.6f, 1.f));
        
        Engine::SpriteRenderer* renderer = collectible->addComponent<Engine::SpriteRenderer>();
        Collectibles* script = nullptr;

        if(std::rand() % 100 <= coinChance)
        {
            script = collectible->addComponent<Coin>();
            renderer->setSprite(SpriteManager::coin);
        }
        else
        {
            script = collectible->addComponent<HealthBooster>();
            renderer->setSprite(SpriteManager::health);
        }

        script->target = target;
        script->maxLength = std::sqrt((std::pow(expand, 2) + std::pow(expand, 2)));
        script->shiphandler = shiphandler;
    }
}