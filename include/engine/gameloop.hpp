#ifndef ENGINE_GAMELOOP_HPP
#define ENGINE_GAMELOOP_HPP

#include <engine/actor.hpp>
#include <engine/camera.hpp>
#include <engine/component.hpp>
#include <engine/ebo.hpp>
#include <engine/input.hpp>
#include <engine/renderer.hpp>
#include <engine/resources.hpp>
#include <engine/shader.hpp>
#include <engine/spriteRenderer.hpp>
#include <engine/time.hpp>
#include <engine/transform.hpp>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>
#include <engine/window.hpp>

namespace Engine
{
    class GameLoop final
    {
    public:
        static void init(std::string title = "", int width = Window::screen_width / 2, 
        int height = Window::screen_height / 2);
        static void begin();
    private:
        inline static std::string title = "";
        inline static int width = 0;
        inline static int height = 0;
        inline static Input* input = nullptr;
        inline static Window* window = nullptr;
    };
}

#endif