#ifndef COSMIC_SHIP_HANDLER_HPP
#define COSMIC_SHIP_HANDLER_HPP

#include <engine/gameloop.hpp>
#include "spaceship.hpp"

namespace Cosmic
{
    class ShipHandler : public Engine::Component
    {
    public:
        Engine::Input* input;
        SpaceShip* ship;
    protected:
        void start();
        void update();
    };
}

#endif