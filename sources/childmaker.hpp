#ifndef COSMIC_CHILD_MAKER_HPP
#define COSMIC_CHILD_MAKER_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class ChildMaker : public Engine::Component
    {
    public:
        Engine::Transform* transform;
        Engine::Input* input;
    protected:
        void start();
        void update();
    };
}

#endif