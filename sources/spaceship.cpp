#include "spaceship.hpp"

void Cosmic::SpaceShip::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
    shootOrigin = Engine::Actor::createActor("Shoot")->getComponent<Engine::Transform>();

    shootOrigin->setParent(transform);
    shootOrigin->setLocalPosition(glm::vec3(0.0f, .8f, 0.0f));

    getActor()->getComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::spaceship);
}

void Cosmic::SpaceShip::moveForward()
{
    glm::vec3 direction = transform->getLocalUp();
    direction *= Engine::Time::getDeltaTime() * forwardSpeed;

    transform->setWorldPosition(transform->getWorldPosition() + direction);
}

void Cosmic::SpaceShip::moveBackward()
{
    glm::vec3 direction = transform->getLocalUp();
    direction *= Engine::Time::getDeltaTime() * backwardSpeed;

    transform->setWorldPosition(transform->getWorldPosition() - direction);
}

void Cosmic::SpaceShip::rotateRight()
{
    glm::vec3 rotate(0.f);
    rotate.z += Engine::Time::getDeltaTime() * rotateSpeed;

    transform->setWorldRotation(transform->getWorldRotation() - rotate);
}

void Cosmic::SpaceShip::rotateLeft()
{
    glm::vec3 rotate(0.f);
    rotate.z += Engine::Time::getDeltaTime() * rotateSpeed;

    transform->setWorldRotation(transform->getWorldRotation() + rotate);
}

void Cosmic::SpaceShip::shoot()
{
    Engine::Actor* bullet = Engine::Actor::createActor("Bullet");

    Engine::Transform* bulletT = bullet->getComponent<Engine::Transform>();
    bulletT->setWorldPosition(shootOrigin->getWorldPosition());
    bulletT->setWorldRotation(transform->getWorldRotation());
    
    bullet->addComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::bullet);
    Cosmic::Bullet* script = bullet->addComponent<Cosmic::Bullet>();
    script->direction = transform->getLocalUp();
    script->target = transform;
}