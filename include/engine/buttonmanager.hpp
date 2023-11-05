#ifndef ENGINE_BUTTON_MANAGER_HPP
#define ENGINE_BUTTON_MANAGER_HPP

#include <engine/input.hpp>
#include <engine/button.hpp>

namespace Engine
{
    class ButtonManager
    {
    protected:
        static void initialize();
        static void checkInteraction();
        static bool isHover(Button* button);
    friend class GameLoop;
    };
}

#endif