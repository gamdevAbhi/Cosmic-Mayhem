#include <engine/gameloop.hpp>

#include "shiphandler.hpp"
#include "follower.hpp"
#include "starmanager.hpp"

int main()
{
    Engine::GameLoop::initialize("game");

    Engine::Actor* spaceShip = Engine::Actor::createActor("Space Ship");
    spaceShip->addComponent<Cosmic::ShipHandler>();
    spaceShip->getComponent<Engine::Transform>()->setScale(true, glm::vec3(2.0f, 2.0f, 1.0f));

    Engine::Actor* starManager = Engine::Actor::createActor("Star Manager");
    starManager->addComponent<Cosmic::StarManager>();

    Engine::Camera* camera = Engine::Camera::getRenderCamera();
    camera->orthographicSize = 25.f;
    camera->getActor()->addComponent<Cosmic::Follower>();

    Engine::GameLoop::begin();

    std::cout << std::endl << "Succesfully Close ..." << std::endl;
    
    return 0;
}