#ifndef COSMIC_BUTTON_HPP
#define COSMIC_BUTTON_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class Button : public Engine::Component
    {
    public:
        void initialize(void (*function)(), glm::vec4 borderColor, glm::vec4 bgColor, std::string text);
    protected:
        void (*callback)();
        Engine::Button* button;
        Engine::RectTransform* transform;
        Engine::Text* text;
        glm::vec2 scale;
        void update();
    };
}


#endif