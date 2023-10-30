#ifndef COSMIC_SPRITE_MANAGER_HPP
#define COSMIC_SPRITE_MANAGER_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class SpriteManager : public Engine::Component
    {
    public:
        inline static Engine::Sprite* spaceship = nullptr;
        inline static Engine::Sprite* bullet = nullptr;
        inline static Engine::Sprite* backBoost = nullptr;
        inline static Engine::Sprite* frontBoost = nullptr;
        inline static Engine::Sprite* leftBoost = nullptr;
        inline static Engine::Sprite* rightBoost = nullptr;
        inline static Engine::Sprite* muzzle = nullptr;
        inline static Engine::Sprite* asteroid = nullptr;
        inline static Engine::Sprite* collectible = nullptr;
        static void loadSprites();
    };
}

#endif