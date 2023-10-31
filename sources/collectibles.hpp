#ifndef COSMIC_COLLECTIBLES_HPP
#define COSMIC_COLLECTIBLES_HPP

#include <engine/gameloop.hpp>

#include "shiphandler.hpp"

namespace Cosmic
{
    class Collectibles : public Engine::Component
    {
    public:
        Engine::Transform* target;
        ShipHandler* shiphandler;
        float maxLength;
        static int getCount();
    protected:
        int desiredTag;
        Engine::Transform* transform;
        inline static int counts = 0;
        void update();
        void onDestroy();
    };
}

#endif