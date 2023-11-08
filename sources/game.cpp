#include <engine/gameloop.hpp>

#include "shiphandler.hpp"
#include "follower.hpp"
#include "starmanager.hpp"
#include "collectiblemanager.hpp"
#include "asteroidmanager.hpp"
#include "spritemanager.hpp"
#include "buttonclicker.hpp"

void initTag()
{
    int spaceship = Engine::ColliderManager::addTag("Space Ship", false);
    int bullet = Engine::ColliderManager::addTag("Bullet", false);
    int collectibles = Engine::ColliderManager::addTag("Collectibles", false);
    int asteroid = Engine::ColliderManager::addTag("Asteroid", true);

    Engine::ColliderManager::addRelation(spaceship, collectibles);
    Engine::ColliderManager::addRelation(spaceship, asteroid);
    Engine::ColliderManager::addRelation(bullet, asteroid);
}

void readyCamera()
{
    Engine::Camera* camera = Engine::Camera::getRenderCamera();
    camera->setOrthographicSize(15.5f);
}

void loadActors()
{
    Engine::Actor* spaceShip = Engine::Actor::createActor("Space Ship");
    spaceShip->addComponent<Cosmic::ShipHandler>();
    spaceShip->getComponent<Engine::Transform>()->setWorldScale(glm::vec3(2.0f, 2.0f, 1.0f));

    Engine::Actor* starManager = Engine::Actor::createActor("Star Manager");
    starManager->addComponent<Cosmic::StarManager>();

    Engine::Actor* collectibleManager = Engine::Actor::createActor("Collectible Manager");
    collectibleManager->addComponent<Cosmic::CollectibleManager>();

    Engine::Actor* asteroidManager = Engine::Actor::createActor("Asteroid Manager");
    asteroidManager->addComponent<Cosmic::AsteroidManager>();

    Engine::Camera::getRenderCamera()->getActor()->addComponent<Cosmic::Follower>();
    
}

int main()
{
    Engine::GameLoop::initialize("game");

    Cosmic::SpriteManager::loadSprites();
    initTag();
    readyCamera();
    loadActors();

    Engine::Actor* font = Engine::Actor::createUIActor("Font");
    font->addComponent<Engine::Text>();
    
    Engine::GameLoop::begin();

    std::cout << std::endl << "Succesfully Close ..." << std::endl;
    
    return 0;
}