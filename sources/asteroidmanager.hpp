#ifndef COSMIC_ASTEROID_MANAGER_HPP
#define COSMIC_ASTEROID_MANAGER_HPP

#include <engine/gameloop.hpp>

#include "asteroid.hpp"

namespace Cosmic
{
    class AsteroidManager : public Engine::Component
    {
    protected:
        int max = 20;
        float minTime = 0.5f;
        float maxTime = 1.5f;
        float currentTime = 0.f;
        float newTime;
        float box = 10.f;
        float offset = 30.f;
        Engine::Sprite* asteroidSprite;
        Engine::Transform* target;
        void start();
        void update();
        void resetTime();
        void createAsteroid();
    };
}

#endif