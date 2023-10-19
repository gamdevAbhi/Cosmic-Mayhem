#include "shiphandler.hpp"

void Cosmic::ShipHandler::start()
{
    input = Engine::GameLoop::getInput();
    ship = getActor()->getComponent<SpaceShip>();
}

void Cosmic::ShipHandler::update()
{
    if(input->getKeyStatus(GLFW_KEY_A) == KEY_HOLD)
    {
        ship->rotateLeft();
    }
    else if(input->getKeyStatus(GLFW_KEY_D) == KEY_HOLD)
    {
        ship->rotateRight();
    }

    if(input->getKeyStatus(GLFW_KEY_LEFT_SHIFT) == KEY_HOLD)
    {
        ship->moveForward();
    }
    else if(input->getKeyStatus(GLFW_KEY_LEFT_CONTROL) == KEY_HOLD)
    {
        ship->moveBackward();
    }
}