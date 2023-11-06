#ifndef COSMIC_BUTTON_CLICKER_HPP
#define COSMIC_BUTTON_CLICKER_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class ButtonClicker : public Engine::Component
    {
    public:
        bool shouldRotate = false;
        bool shouldScale = false;
    protected:
        Engine::RectTransform* rect;
        Engine::Billboard* billboard;
        Engine::Button* button;
        void start();
        void update();
    };
}

#endif