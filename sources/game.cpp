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

    // Cosmic::SpriteManager::loadSprites();
    // initTag();
    // readyCamera();
    // loadActors();

    // test
    Engine::Actor* parent = Engine::Actor::createUIActor("Parent");
    Engine::RectTransform* pRect = parent->getComponent<Engine::RectTransform>();
    parent->addComponent<Cosmic::ButtonClicker>()->shouldRotate = true;
    parent->getComponent<Engine::Billboard>()->setOrder(1);
    parent->getComponent<Engine::Billboard>()->setColor(glm::vec4(1.f));

    pRect->setRectSize(glm::vec2(100.f, 100.f));

    for(int i = 0; i < 2; i++)
    {
        Engine::Actor* child = Engine::Actor::createUIActor("Child");
        Engine::RectTransform* cRect = child->getComponent<Engine::RectTransform>();
        child->addComponent<Cosmic::ButtonClicker>()->shouldRotate = true;
        child->getComponent<Cosmic::ButtonClicker>()->shouldScale = true;

        cRect->setParent(pRect);
        cRect->setAnchor(Engine::UI::CENTER);
        cRect->setAnchorPosition(glm::vec3(0.f, (60.f * i) + 20.f, 0.f));
        cRect->setRectSize(glm::vec2(80.f, 40.f));
    }

    Engine::GameLoop::begin();

    std::cout << std::endl << "Succesfully Close ..." << std::endl;
    
    return 0;
}