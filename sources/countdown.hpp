#ifndef COSMIC_COUNTDOWN_HPP
#define COSMIC_COUNTDOWN_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class Countdown : public Engine::Component
    {
    public:
        void initialize(void (*function)(), Engine::Text* text, float time,
        std::string message);
    protected:
        float callbackTime;
        void (*callback)();
        Engine::Text* text = nullptr;
        std::string message;
        void update();
    };
}

#endif