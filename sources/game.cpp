#include <engine/gameloop.hpp>

#include "spaceship.hpp"
#include "shiphandler.hpp"
#include "follower.hpp"
#include "childmaker.hpp"

int main()
{
    Engine::GameLoop::initialize();

    Engine::Actor* actor = Engine::Actor::createActor("Space Ship");

    actor->addComponent<Engine::SpriteRenderer>();
    actor->addComponent<Engine::BoxCollider>();
    actor->addComponent<Cosmic::SpaceShip>();
    actor->addComponent<Cosmic::ShipHandler>();
    actor->addComponent<Cosmic::ChildMaker>();

    Engine::Camera::getRenderCamera()->orthographicSize = 25.f;
    Engine::Camera::getRenderCamera()->getActor()->getComponent<Engine::Transform>()->setPosition(true, glm::vec3(0.0f, 0.0f, 2.0f));
    Engine::Camera::getRenderCamera()->getActor()->addComponent<Cosmic::Follower>()->target = actor->getComponent<Engine::Transform>();

    Engine::GameLoop::begin();

    std::cout << std::endl << "Succesfully Close ..." << std::endl;
    
    return 0;
}