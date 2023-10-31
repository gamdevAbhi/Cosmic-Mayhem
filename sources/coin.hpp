#ifndef COSMIC_COIN_HPP
#define COSMIC_COIN_HPP

#include "collectibles.hpp"

namespace Cosmic
{
    class Coin : public Collectibles
    {
    protected:
        int value;
        void start();
        void onTriggerEnter(Engine::Collider* collider);
    };
}

#endif