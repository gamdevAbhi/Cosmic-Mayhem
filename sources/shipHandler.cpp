#include "shiphandler.hpp"

void Cosmic::ShipHandler::start()
{
    input = Engine::GameLoop::getInput();
    transform = getActor()->getComponent<Engine::Transform>();

    getActor()->addComponent<Engine::SpriteRenderer>()->setOrder(0);
    getActor()->addComponent<Engine::BoxCollider>();
    shipComponent = getActor()->addComponent<SpaceShip>();

    backBoost = Engine::Actor::createActor("Back Boost");
    frontBoost = Engine::Actor::createActor("Front Boost");
    leftBoost = Engine::Actor::createActor("Left Boost");
    rightBoost = Engine::Actor::createActor("Right Boost");

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
}

void Cosmic::ShipHandler::update()
{
    backBoost->setActive(false);
    frontBoost->setActive(false);
    rightBoost->setActive(false);
    leftBoost->setActive(false);

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

    if(input->getKeyStatus(GLFW_KEY_I) == KEY_HOLD)
    {
        std::cout << "Last Frame Per Second(s) :" << std::endl;
        std::cout << Engine::Time::getLastFPS() << std::endl;
        std::cout << "Total Actors :" << std::endl;
        std::cout << Engine::Actor::getActorCount() << std::endl;
        std::cout << "Last Render Count :" << std::endl;
        std::cout << Engine::SpriteRenderer::lastRenderCount() << std::endl;
    }
}