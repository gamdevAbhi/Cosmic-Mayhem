#include <engine/gameloop.hpp>

#include "spaceship.hpp"
#include "shiphandler.hpp"
#include "follower.hpp"

int main()
{
    Engine::GameLoop::initialize("game");

    Engine::Actor* spaceShip = Engine::Actor::createActor("Space Ship");
    Engine::Actor* starManager = Engine::Actor::createActor("Star Manager");

    spaceShip->addComponent<Engine::SpriteRenderer>();
    spaceShip->addComponent<Engine::BoxCollider>();
    spaceShip->addComponent<Cosmic::SpaceShip>();
    spaceShip->addComponent<Cosmic::ShipHandler>();

    Engine::Camera* camera = Engine::Camera::getRenderCamera();
    camera->orthographicSize = 25.f;
    camera->getActor()->getComponent<Engine::Transform>()->setPosition(true, glm::vec3(0.0f, 0.0f, 2.0f));
    camera->getActor()->addComponent<Cosmic::Follower>()->target = spaceShip->getComponent<Engine::Transform>();

    Engine::GameLoop::begin();

    std::cout << std::endl << "Succesfully Close ..." << std::endl;
    
    return 0;
}