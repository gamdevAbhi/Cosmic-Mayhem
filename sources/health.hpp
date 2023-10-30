#ifndef COSMIC_HEALTH_HPP
#define COSMIC_HEALTH_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class Health : public Engine::Component
    {
    public:
        bool shouldDestroy = true;
        void setHealth(int value);
        void addHealth(int value);
        void addDamage(int value);
        int getHealth();
    protected:
        int maxHealth, health;
        void update();
    };
}

#endif