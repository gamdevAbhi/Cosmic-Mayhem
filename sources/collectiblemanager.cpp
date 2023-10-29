#include "collectiblemanager.hpp"

void Cosmic::CollectibleManager::start()
{
    target = Engine::Actor::getActor("Space Ship")->getComponent<Engine::Transform>();
    collectibleSprite = new Engine::Sprite("\\resources\\sprites\\Collectible.png");
}

// need fix
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
        collectible->addComponent<Cosmic::Collectibles>()->target = target;
        collectible->getComponent<Cosmic::Collectibles>()->maxLength = std::sqrt((std::pow(expand, 2) + std::pow(expand, 2)));
        collectible->addComponent<Engine::SpriteRenderer>()->setSprite(collectibleSprite);
    }
}