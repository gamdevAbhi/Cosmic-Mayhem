#include "shiphandler.hpp"

void Cosmic::ShipHandler::addScore(int value)
{
    score += value;
    std::cout << score << std::endl;
}

void Cosmic::ShipHandler::start()
{
    input = Engine::GameLoop::getInput();
    transform = getActor()->getComponent<Engine::Transform>();

    getActor()->addComponent<Engine::SpriteRenderer>()->setOrder(0);

    Engine::BoxCollider* collider = getActor()->addComponent<Engine::BoxCollider>();
    collider->setTag(Engine::ColliderManager::getTag("Space Ship"));
    collider->setBoundary(0.4f, 0.4f, 0.5f, 0.5f);

    shipComponent = getActor()->addComponent<SpaceShip>();

    backBoost = Engine::Actor::createActor("Back Boost");
    frontBoost = Engine::Actor::createActor("Front Boost");
    leftBoost = Engine::Actor::createActor("Left Boost");
    rightBoost = Engine::Actor::createActor("Right Boost");
    muzzle = Engine::Actor::createActor("Muzzle");

    backBoost->getComponent<Engine::Transform>()->setParent(transform);
    backBoost->getComponent<Engine::Transform>()->setPosition(false, glm::vec3(0.f));
    backBoost->addComponent<Engine::SpriteRenderer>()->setSprite(new Engine::Sprite(
    "\\resources\\sprites\\Back Boost.png"));
    
    frontBoost->getComponent<Engine::Transform>()->setParent(transform);
    frontBoost->getComponent<Engine::Transform>()->setPosition(false, glm::vec3(0.f));
    frontBoost->addComponent<Engine::SpriteRenderer>()->setSprite(new Engine::Sprite(
    "\\resources\\sprites\\Front Boost.png"));
    
    leftBoost->getComponent<Engine::Transform>()->setParent(transform);
    leftBoost->getComponent<Engine::Transform>()->setPosition(false, glm::vec3(0.f));
    leftBoost->addComponent<Engine::SpriteRenderer>()->setSprite(new Engine::Sprite(
    "\\resources\\sprites\\Left Boost.png"));
    
    rightBoost->getComponent<Engine::Transform>()->setParent(transform);
    rightBoost->getComponent<Engine::Transform>()->setPosition(false, glm::vec3(0.f));
    rightBoost->addComponent<Engine::SpriteRenderer>()->setSprite(new Engine::Sprite(
    "\\resources\\sprites\\Right Boost.png"));

    muzzle->getComponent<Engine::Transform>()->setParent(transform);
    muzzle->getComponent<Engine::Transform>()->setPosition(false, glm::vec3(0.f));
    muzzle->addComponent<Engine::SpriteRenderer>()->setSprite(new Engine::Sprite(
    "\\resources\\sprites\\Muzzle.png"));
}

void Cosmic::ShipHandler::update()
{
    backBoost->setActive(false);
    frontBoost->setActive(false);
    rightBoost->setActive(false);
    leftBoost->setActive(false);
    muzzle->setActive(true);

    if(input->getKeyStatus(GLFW_KEY_A) == KEY_HOLD)
    {
        shipComponent->rotateLeft();
        rightBoost->setActive(true);
    }
    else if(input->getKeyStatus(GLFW_KEY_D) == KEY_HOLD)
    {
        shipComponent->rotateRight();
        leftBoost->setActive(true);
    }

    if(input->getKeyStatus(GLFW_KEY_LEFT_SHIFT) == KEY_HOLD)
    {
        shipComponent->moveForward();
        frontBoost->setActive(true);
    }
    else if(input->getKeyStatus(GLFW_KEY_LEFT_CONTROL) == KEY_HOLD)
    {
        shipComponent->moveBackward();
        backBoost->setActive(true);
    }

    if(input->getKeyStatus(GLFW_KEY_F) == KEY_PRESS)
    {
        shipComponent->shoot();
        muzzle->setActive(true);
    }

    if(input->getKeyStatus(GLFW_KEY_I) == KEY_PRESS)
    {
        std::cout << "Last Frame Per Second(s) :" << std::endl;
        std::cout << Engine::Time::getLastFPS() << std::endl;
        std::cout << "Total Actors :" << std::endl;
        std::cout << Engine::Actor::getActorCount() << std::endl;
        std::cout << "Last Render Count :" << std::endl;
        std::cout << Engine::SpriteRenderer::lastRenderCount() << std::endl;
    }
}