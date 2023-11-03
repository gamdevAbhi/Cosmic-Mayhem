#ifndef ENGINE_INPUT_HPP
#define ENGINE_INPUT_HPP
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <engine/window.hpp>
#include <unordered_map>

namespace Engine
{
    // handle inputs of a window
    class Input final
    {
    public:
        enum KeyStatus {KEY_NONE, KEY_PRESS, KEY_HOLD, KEY_RELEASE};
        static int getKeyStatus(int key);
        static int getMouseButtonStatus(int mouseButton);
        static glm::vec2 getMousePos();
    private:
        static void initialize();
        inline static std::unordered_map<int, KeyStatus> keyboardInputs, mouseInputs;
        inline static Window* window;
    friend class GameLoop;
    };
}

#endif