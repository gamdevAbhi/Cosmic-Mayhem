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

    tDRect->setAnchor(glm::vec2(0.f, 0.6f));
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

    // adding asteroid manager
    Engine::Actor* asteroidManager = Engine::Actor::createActor("Asteroid Manager");
    asteroidManager->addComponent<Cosmic::AsteroidManager>()->initialize(worldOrigin);

    // adding cosmic mayhem title text
    Engine::Actor* title = Engine::Actor::createUIActor("Title");
    Engine::RectTransform* tRect = title->getComponent<Engine::RectTransform>();
    Engine::Text* tText = title->addComponent<Engine::Text>();

    tRect->setAnchor(glm::vec2(0.f, 0.6f));
    tText->setAlignment(Engine::Text::MIDDLE);
    tText->setTextColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
    tText->setScale(2.f);
    tText->setText("COSMIC MAYHEM");

    // adding play button
    Engine::RectTransform* pRect = Engine::Actor::createUIActor("Play")->getComponent<Engine::RectTransform>();
    pRect->setAnchor(glm::vec2(0.f, -0.3f));
    pRect->setAnchorSize(glm::vec2(0.125f));
    pRect->getActor()->addComponent<Cosmic::Button>()->initialize(&loadGameScene,
    glm::vec4(1.f), glm::vec4(0.1f, 0.9f, 0.2f, 1.f), "PLAY");
    // adding exit button
    Engine::RectTransform* eRect = Engine::Actor::createUIActor("Exit")->getComponent<Engine::RectTransform>();
    eRect->setAnchor(glm::vec2(0.f, -0.7f));
    eRect->setAnchorSize(glm::vec2(0.125f));
    eRect->getActor()->addComponent<Cosmic::Button>()->initialize(&Engine::GameLoop::endGameLoop,
    glm::vec4(1.f), glm::vec4(0.9f, 0.1f, 0.2f, 1.f), "EXIT");
}

// load game scene
void Cosmic::SceneManager::loadGameScene()
{
    // clearing previous actors
    Engine::Actor::clearActors();

    // adding spaceship
    Engine::Actor* spaceShip = Engine::Actor::createActor("Space Ship");
    Engine::Transform* transform = spaceShip->getComponent<Engine::Transform>();

    spaceShip->addComponent<Cosmic::ShipHandler>()->callback = &loadGameOverScene;
    transform->setWorldScale(glm::vec3(2.0f, 2.0f, 1.0f));

    // adding start manager
    Engine::Actor* starManager = Engine::Actor::createActor("Star Manager");
    starManager->addComponent<Cosmic::StarManager>()->initialize(transform);

    // adding collectible manager
    Engine::Actor* collectibleManager = Engine::Actor::createActor("Collectible Manager");
    collectibleManager->addComponent<Cosmic::CollectibleManager>();

    // adding asteroid manager
    Engine::Actor* asteroidManager = Engine::Actor::createActor("Asteroid Manager");
    asteroidManager->addComponent<Cosmic::AsteroidManager>()->initialize(transform);

    // adding follower component
    Engine::Camera::getRenderCamera()->getActor()->addComponent<Cosmic::Follower>()->initialize(transform);
}

// load game over scene
void Cosmic::SceneManager::loadGameOverScene()
{
    // clearing previous actors
    Engine::Actor::clearActors();
    // removing follower component
    Engine::Camera::getRenderCamera()->getActor()->getComponent<Cosmic::Follower>()->setDestroy();
    // adding game over text
    Engine::Actor* title = Engine::Actor::createUIActor("Game Over");
    Engine::RectTransform* tRect = title->getComponent<Engine::RectTransform>();
    Engine::Text* tText = title->addComponent<Engine::Text>();

    tRect->setAnchor(glm::vec2(0.f, 0.6f));
    tText->setAlignment(Engine::Text::MIDDLE);
    tText->setTextColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
    tText->setScale(2.f);
    tText->setText("Game Over");
    // adding score text
    Engine::Actor* score = Engine::Actor::createUIActor("Score");
    Engine::RectTransform* sRect = score->getComponent<Engine::RectTransform>();
    Engine::Text* sText = score->addComponent<Engine::Text>();

    sRect->setAnchor(glm::vec2(0.f, 0.4f));
    sText->setAlignment(Engine::Text::MIDDLE);
    sText->setTextColor(glm::vec4(1.f, 1.f, 1.f, 1.f));
    sText->setScale(1.25f);
    sText->setText("Score : " + std::to_string(lastGameScore));
    // adding retry button
    Engine::RectTransform* rRect = Engine::Actor::createUIActor("Retry")->getComponent<Engine::RectTransform>();
    rRect->setAnchor(glm::vec2(0.f, -0.3f));
    rRect->setAnchorSize(glm::vec2(0.125f));
    rRect->getActor()->addComponent<Cosmic::Button>()->initialize(&loadGameScene,
    glm::vec4(1.f), glm::vec4(0.1f, 0.2f, 0.9f, 1.f), "RETRY");
    // adding menu button
    Engine::RectTransform* mRect = Engine::Actor::createUIActor("Menu")->getComponent<Engine::RectTransform>();
    mRect->setAnchor(glm::vec2(0.f, -0.7f));
    mRect->setAnchorSize(glm::vec2(0.125f));
    mRect->getActor()->addComponent<Cosmic::Button>()->initialize(&loadMenuScene,
    glm::vec4(1.f), glm::vec4(0.1f, 0.9f, 0.2f, 1.f), "MENU");
}