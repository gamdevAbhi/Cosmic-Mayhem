#ifndef COSMIC_ASTEROID_MANAGER_HPP
#define COSMIC_ASTEROID_MANAGER_HPP

#include <engine/gameloop.hpp>

#include "asteroid.hpp"
#include "spritemanager.hpp"

namespace Cosmic
{
    class AsteroidManager : public Engine::Component
    {
    public:
        void initialize(Engine::Transform* target);
    protected:
        int max = 20;
        float minTime = 0.5f;
        float maxTime = 1.5f;
        float currentTime = 0.f;
        float newTime;
        float box = 10.f;
        float offset = 30.f;
        Engine::Transform* target;
        void update();
        void resetTime();
        void createAsteroid();
    };
}

#endif