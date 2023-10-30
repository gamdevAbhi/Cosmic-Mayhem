#include "spaceship.hpp"

void Cosmic::SpaceShip::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
    shootOrigin = Engine::Actor::createActor("Shoot")->getComponent<Engine::Transform>();

    shootOrigin->setParent(transform);
    shootOrigin->setPosition(false, glm::vec3(0.0f, .8f, 0.0f));

    getActor()->getComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::spaceship);
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

void Cosmic::SpaceShip::shoot()
{
    Engine::Actor* bullet = Engine::Actor::createActor("Bullet");

    Engine::Transform* bulletT = bullet->getComponent<Engine::Transform>();
    bulletT->setPosition(true, shootOrigin->getPosition(true));
    bulletT->setRotation(true, transform->getRotation(true));
    
    bullet->addComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::bullet);
    Cosmic::Bullet* script = bullet->addComponent<Cosmic::Bullet>();
    script->direction = transform->getUp(false);
    script->target = transform;
}