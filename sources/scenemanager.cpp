#include "scenemanager.hpp"

// load the technical scene for the game
void Cosmic::SceneManager::loadTechScene()
{
    // setting the camera background color
    Engine::Camera* camera = Engine::Camera::getRenderCamera();
    camera->setBackgroundColor(glm::vec3(0.98f, 0.96f, 0.898f));

    // loading UI Actors
    // adding demo main text
    Engine::Actor* technicalDemoText = Engine::Actor::createUIActor("Technical Demo Text");
    Engine::RectTransform* tDRect = technicalDemoText->getComponent<Engine::RectTransform>(); 
    Engine::Text* tDText = technicalDemoText->addComponent<Engine::Text>();

    tDRect->setAnchor(glm::vec2(0.f, 0.5f));
    tDText->setAlignment(Engine::Text::MIDDLE);
    tDText->setTextColor(glm::vec4(0.01f, 0.074f, 0.121f, 1.f));
    tDText->setScale(1.2f);
    tDText->setText("HAZARD ENGINE 2D TECH DEMO 1.0");

    // adding count down actor
    Engine::Actor* countdown = Engine::Actor::createUIActor("Count Down Actor");
    Engine::RectTransform* cdRect = countdown->getComponent<Engine::RectTransform>();
    Engine::Text* cdText = countdown->addComponent<Engine::Text>();
    
    cdRect->setAnchor(glm::vec2(0.f, -0.75f));
    cdText->setAlignment(Engine::Text::MIDDLE);
    cdText->setTextColor(glm::vec4(0.01f, 0.074f, 0.121f, 1.f));
    cdText->setScale(0.8f);
    countdown->addComponent<Cosmic::Countdown>()->initialize(&loadMenuScene, cdText, 5.f, 
    "THE GAME SCREEN WILL APPEAR IN ");
}

// load the game menu scene
void Cosmic::SceneManager::loadMenuScene()
{
    // clearing previous scene
    Engine::Actor::clearActors();

    // changing camera background
    Engine::Camera* camera = Engine::Camera::getRenderCamera();
    camera->setBackgroundColor(glm::vec3(0.01f, 0.074f, 0.121f));
    camera->setOrthographicSize(20.f);
    camera->getActor()->getComponent<Engine::Transform>()->setWorldPosition(glm::vec3(0.f, 0.f, 3.f));

    // adding world origin for stars
    Engine::Transform* worldOrigin = Engine::Actor::createActor("World Origin")->getComponent<Engine::Transform>();

    // adding stars in background
    Engine::Actor* starManager = Engine::Actor::createActor("Star Manager");
    starManager->addComponent<Cosmic::StarManager>()->initialize(worldOrigin);

    // adding cosmic mayhem title text
    // adding play button
    // adding exit button
}

// load game scene
void Cosmic::SceneManager::loadGameScene()
{
    // clearing previous actors
    Engine::Actor::clearActors();

    // adding spaceship
    Engine::Actor* spaceShip = Engine::Actor::createActor("Space Ship");
    Engine::Transform* transform = spaceShip->getComponent<Engine::Transform>();

    spaceShip->addComponent<Cosmic::ShipHandler>();
    transform->setWorldScale(glm::vec3(2.0f, 2.0f, 1.0f));

    // adding start manager
    Engine::Actor* starManager = Engine::Actor::createActor("Star Manager");
    starManager->addComponent<Cosmic::StarManager>();

    // adding collectible manager
    Engine::Actor* collectibleManager = Engine::Actor::createActor("Collectible Manager");
    collectibleManager->addComponent<Cosmic::CollectibleManager>();

    // adding asteroid manager
    Engine::Actor* asteroidManager = Engine::Actor::createActor("Asteroid Manager");
    asteroidManager->addComponent<Cosmic::AsteroidManager>();

    // adding follower component
    Engine::Camera::getRenderCamera()->getActor()->addComponent<Cosmic::Follower>()->initialize(transform);

    // adding health UI
    // adding score UI
}

// load game over scene
void Cosmic::SceneManager::loadGameOverScene()
{
    // clearing previous actors
    // removing follower component
    // adding game over text
    // adding score text
    // adding retry button
    // adding main menu button
}