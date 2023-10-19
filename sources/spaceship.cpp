#include "spaceship.hpp"

void Cosmic::SpaceShip::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
    renderer = getActor()->getComponent<Engine::SpriteRenderer>();
    shipSprite = new Engine::Sprite("\\resources\\sprites\\spaceship_test.png");

    renderer->setSprite(shipSprite);
    renderer->setOrder(1);
}

void Cosmic::SpaceShip::moveForward()
{
    glm::vec3 direction = transform->getUp(false);
    direction *= Engine::Time::getDeltaTime() * forwardSpeed;

    transform->setPosition(true, transform->getPosition(true) + direction);
}

void Cosmic::SpaceShip::moveBackward()
{
    glm::vec3 direction = transform->getUp(false);
    direction *= Engine::Time::getDeltaTime() * backwardSpeed;

    transform->setPosition(true, transform->getPosition(true) - direction);
}

void Cosmic::SpaceShip::rotateRight()
{
    glm::vec3 rotate(0.f);
    rotate.z += Engine::Time::getDeltaTime() * rotateSpeed;

    transform->setRotation(true, transform->getRotation(true) - rotate);
}

void Cosmic::SpaceShip::rotateLeft()
{
    glm::vec3 rotate(0.f);
    rotate.z += Engine::Time::getDeltaTime() * rotateSpeed;

    transform->setRotation(true, transform->getRotation(true) + rotate);
}

void Cosmic::SpaceShip::onDestroy()
{
    shipSprite->destroy();
    shipSprite = nullptr;
    renderer->setSprite(nullptr);
}