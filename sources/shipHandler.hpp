#ifndef COSMIC_SHIP_HANDLER_HPP
#define COSMIC_SHIP_HANDLER_HPP

#include <engine/gameloop.hpp>
#include "spaceship.hpp"

namespace Cosmic
{
    class ShipHandler : public Engine::Component
    {
    public:
        void addScore(int value);
    protected:
        Engine::Input* input;
        Engine::Transform* transform;
        SpaceShip* shipComponent;
        Engine::Actor* backBoost;
        Engine::Actor* frontBoost;
        Engine::Actor* leftBoost;
        Engine::Actor* rightBoost;
        Engine::Actor* muzzle;
        int score = 0;
        void start();
        void update();
    };
}

#endif