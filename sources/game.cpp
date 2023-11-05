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

    // test
    Engine::Actor* parent = Engine::Actor::createUIActor("Parent");
    Engine::Actor* leftChild = Engine::Actor::createUIActor("Left Child");
    Engine::Actor* centerChild = Engine::Actor::createUIActor("Center Child");
    Engine::Actor* rightChild = Engine::Actor::createUIActor("Right Child");
    glm::vec2 parentRect = Engine::UI::getResolution();
    parentRect /= 2.f;
    parentRect *= 0.6f;

    parent->getComponent<Engine::RectTransform>()->setAnchor(Engine::UI::CENTER);
    parent->getComponent<Engine::RectTransform>()->setRectSize(parentRect);
    parent->addComponent<Engine::Billboard>()->setOrder(1);

    leftChild->getComponent<Engine::RectTransform>()->setParent(parent->getComponent<Engine::RectTransform>());
    centerChild->getComponent<Engine::RectTransform>()->setParent(parent->getComponent<Engine::RectTransform>());
    rightChild->getComponent<Engine::RectTransform>()->setParent(parent->getComponent<Engine::RectTransform>());

    leftChild->getComponent<Engine::RectTransform>()->setAnchor(Engine::UI::LEFT);
    centerChild->getComponent<Engine::RectTransform>()->setAnchor(Engine::UI::CENTER);
    rightChild->getComponent<Engine::RectTransform>()->setAnchor(Engine::UI::RIGHT);

    leftChild->getComponent<Engine::RectTransform>()->setRectSize(glm::vec2(40.f, 80.f));
    centerChild->getComponent<Engine::RectTransform>()->setRectSize(glm::vec2(40.f, 80.f));
    rightChild->getComponent<Engine::RectTransform>()->setRectSize(glm::vec2(40.f, 80.f));

    // leftChild->getComponent<Engine::RectTransform>()->setAnchorPosition(glm::vec3(-40.f, 0.f, 0.f));
    // rightChild->getComponent<Engine::RectTransform>()->setAnchorPosition(glm::vec3(-40.f, 0.f, 0.f));

    leftChild->addComponent<Cosmic::ButtonClicker>()->shouldRotate = true;
    centerChild->addComponent<Cosmic::ButtonClicker>()->shouldRotate = false;
    rightChild->addComponent<Cosmic::ButtonClicker>()->shouldRotate = true;

    Engine::GameLoop::begin();

    std::cout << std::endl << "Succesfully Close ..." << std::endl;
    
    return 0;
}