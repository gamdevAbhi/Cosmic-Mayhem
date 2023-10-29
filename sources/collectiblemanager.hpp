#ifndef COSMIC_COLLECTIBLE_MANAGER_HPP
#define COSMIC_COLLECTIBLE_MANAGER_HPP

#include <engine/gameloop.hpp>

#include "collectibles.hpp"

namespace Cosmic
{
    class CollectibleManager : public Engine::Component
    {
    protected:
        int max = 20;
        float expand = 40.f;
        Engine::Transform* target;
        Engine::Sprite* collectibleSprite;
        void start();
        void update();
    };
}

#endif