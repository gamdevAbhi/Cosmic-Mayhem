#ifndef ENGINE_INPUT_HPP
#define ENGINE_INPUT_HPP
#define GLFW_INCLUDE_NONE

#define KEY_RELEASE GLFW_RELEASE
#define KEY_PRESS   GLFW_PRESS
#define KEY_HOLD    2

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <engine/window.hpp>
#include <unordered_map>

namespace engine
{
    // handle inputs of a window
    class Input
    {
    public:
        int getKeyStatus(int key);
        int getMouseButtonStatus(int mouseButton);
        std::tuple<double, double> getMousePos();
    private:
        Input(Window& window);
        std::unordered_map<int, int> keyboardInputs, mouseInputs;
        Window* window;
    };
}

#endif