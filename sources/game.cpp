#include <engine/gameloop.hpp>

#include "shiphandler.hpp"
#include "follower.hpp"
#include "starmanager.hpp"
#include "collectiblemanager.hpp"
#include "asteroidmanager.hpp"

int main()
{
    Engine::GameLoop::initialize("game");

    Engine::ColliderManager::addTag("Space Ship", false);
    Engine::ColliderManager::addTag("Bullet", false);
    Engine::ColliderManager::addTag("Collectibles", false);
    Engine::ColliderManager::addTag("Asteroid", true);

    Engine::ColliderManager::addRelation(Engine::ColliderManager::getTag("Space Ship"), 
    Engine::ColliderManager::getTag("Collectibles"));
    Engine::ColliderManager::addRelation(Engine::ColliderManager::getTag("Space Ship"),
    Engine::ColliderManager::getTag("Asteroid"));
    Engine::ColliderManager::addRelation(Engine::ColliderManager::getTag("Bullet"),
    Engine::ColliderManager::getTag("Asteroid"));

    Engine::Actor* spaceShip = Engine::Actor::createActor("Space Ship");
    spaceShip->addComponent<Cosmic::ShipHandler>();
    spaceShip->getComponent<Engine::Transform>()->setScale(true, glm::vec3(2.0f, 2.0f, 1.0f));

    Engine::Actor* starManager = Engine::Actor::createActor("Star Manager");
    starManager->addComponent<Cosmic::StarManager>();

    Engine::Actor* collectibleManager = Engine::Actor::createActor("Collectible Manager");
    collectibleManager->addComponent<Cosmic::CollectibleManager>();

    Engine::Actor* asteroidManager = Engine::Actor::createActor("Asteroid Manager");
    asteroidManager->addComponent<Cosmic::AsteroidManager>();

    Engine::Camera* camera = Engine::Camera::getRenderCamera();
    camera->orthographicSize = 15.5f;
    camera->getActor()->addComponent<Cosmic::Follower>();

    Engine::GameLoop::begin();

    std::cout << std::endl << "Succesfully Close ..." << std::endl;
    
    return 0;
}