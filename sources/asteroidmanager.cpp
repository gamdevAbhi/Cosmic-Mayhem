#include "asteroidmanager.hpp"

void Cosmic::AsteroidManager::start()
{
    target = Engine::Actor::getActor("Space Ship")->getComponent<Engine::Transform>();
    resetTime();
    for(int i = 0; i < 5; i++) createAsteroid();
}

void Cosmic::AsteroidManager::update()
{
    if(Cosmic::Asteroid::getCount() >= max) return;

    currentTime += Engine::Time::getDeltaTime();

    if(currentTime >= newTime)
    {
        resetTime();
        createAsteroid();
    }
}

void Cosmic::AsteroidManager::resetTime()
{
    currentTime = 0.f;
    newTime = minTime + ((std::rand() % 100) / 100.f) * (maxTime - minTime);
}

void Cosmic::AsteroidManager::createAsteroid()
{
    glm::vec3 distance(0.f);
    glm::vec3 origin(0.f);
    glm::vec3 targetPos = target->getWorldPosition();

    distance.x = (targetPos.x - box) + ((std::rand() % 100) / 100.f) * (box * 2.f);
    distance.y = (targetPos.y - box) + ((std::rand() % 100) / 100.f) * (box * 2.f);

    int random = std::rand() % 100;

    if(random <= 25)
    {
        origin.x = (targetPos.x - offset) + ((std::rand() % 100) / 100.f) * (offset * 2.f);
        origin.y = targetPos.y + offset;
    }
    else if(random <= 50)
    {
        origin.x = (targetPos.x - offset) + ((std::rand() % 100) / 100.f) * (offset * 2.f);
        origin.y = targetPos.y - offset;
    }
    else if(random <= 75)
    {
        origin.x = targetPos.x + offset;
        origin.y = (targetPos.y - offset) + ((std::rand() % 100) / 100.f) * (offset * 2.f);
    }
    else
    {
        origin.x = targetPos.x - offset;
        origin.y = (targetPos.y - offset) + ((std::rand() % 100) / 100.f) * (offset * 2.f);
    }

    float scaleFactor = .5f + (std::rand() % 50) / 50.f;
    glm::vec3 scale(1.f);
    scale.x = scaleFactor;
    scale.y = scaleFactor;

    Engine::Actor* asteroid = Engine::Actor::createActor("Asteroid");
    
    asteroid->addComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::asteroid);
    asteroid->addComponent<Health>()->setHealth(10 * ((scale.x * 10.f) - 4.f) + 20);
    asteroid->getComponent<Engine::Transform>()->setWorldPosition(origin);
    asteroid->getComponent<Engine::Transform>()->setWorldScale(scale);

    Asteroid* script = asteroid->addComponent<Asteroid>();
    script->target = target;
    script->direction = glm::normalize(distance - origin);
    script->calculateDamage();
}