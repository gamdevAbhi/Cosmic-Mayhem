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
    Engine::Actor* canvas = Engine::Actor::createUIActor("Canvas");
    Engine::Actor* greenButton = Engine::Actor::createUIActor("Green Button");
    Engine::Actor* redButton = Engine::Actor::createUIActor("Red Button");

    Engine::RectTransform* canvasR = canvas->getComponent<Engine::RectTransform>();
    Engine::RectTransform* gBR = greenButton->getComponent<Engine::RectTransform>();
    Engine::RectTransform* rBR = redButton->getComponent<Engine::RectTransform>();

    canvas->addComponent<Cosmic::ButtonClicker>()->shouldRotate = true;

    gBR->setParent(canvasR);
    rBR->setParent(canvasR);

    gBR->setAnchor(Engine::UI::TOP_CENTER);
    rBR->setAnchor(Engine::UI::BOTTOM_CENTER);

    gBR->setAnchorPosition(glm::vec3(0.f, -80.f, 0.f));
    rBR->setAnchorPosition(glm::vec3(0.f, 80.f, 0.f));

    canvasR->setRectSize(glm::vec2(200.f, 140.f));
    gBR->setRectSize(glm::vec2(140.f, 60.f));
    rBR->setRectSize(glm::vec2(140.f, 60.f));

    Engine::Billboard* billboard = canvas->getComponent<Engine::Billboard>();
    billboard->setOrder(1);
    billboard->setColor(glm::vec4(1.f, 1.f, 1.f, 0.8f));

    greenButton->addComponent<Cosmic::ButtonClicker>()->shouldScale = true;
    redButton->addComponent<Cosmic::ButtonClicker>()->shouldScale = true;

    greenButton->getComponent<Engine::Billboard>()->setColor(glm::vec4(0.f, 1.f, 0.f, 1.f));
    redButton->getComponent<Engine::Billboard>()->setColor(glm::vec4(1.f, 0.f, 0.f, 1.f));

    Engine::GameLoop::begin();

    std::cout << std::endl << "Succesfully Close ..." << std::endl;
    
    return 0;
}