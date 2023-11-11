#ifndef COSMIC_SHIP_HANDLER_HPP
#define COSMIC_SHIP_HANDLER_HPP

#include <engine/gameloop.hpp>

#include "spaceship.hpp"
#include "health.hpp"
#include "spritemanager.hpp"

namespace Cosmic
{
    class ShipHandler : public Engine::Component
    {
    public:
        void addScore(int value);
        void (*callback)();
    protected:
        Engine::Transform* transform;
        SpaceShip* shipComponent;
        Health* health;
        Engine::Actor* backBoost;
        Engine::Actor* frontBoost;
        Engine::Actor* leftBoost;
        Engine::Actor* rightBoost;
        Engine::Actor* muzzle;
        Engine::Text* healthText;
        Engine::Text* scoreText;
        Engine::Text* pauseText;
        int score = 0;
        bool isPause = false;
        void start();
        void update();
    };
}

#endif