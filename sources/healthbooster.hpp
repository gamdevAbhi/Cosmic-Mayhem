#ifndef COSMIC_HEALTH_BOOSTER_HPP
#define COSMIC_HEALTH_BOOSTER_HPP

#include <engine/gameloop.hpp>

#include "health.hpp"
#include "collectibles.hpp"

namespace Cosmic
{
    class HealthBooster : public Collectibles
    {
    protected:
        int healthBooster;
        int minHealthBooster = 10;
        int maxHealthBooster = 40;
        void start();
        void onTriggerEnter(Engine::Collider* collider);
    };
}

#endif