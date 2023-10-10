#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <engine/actor.hpp>
#include <engine/component.hpp>
#include <engine/transform.hpp>
#include <engine/shader.hpp>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>
#include <engine/ebo.hpp>

namespace Engine
{
    class Renderer : public Component
    {
    private:
        virtual void draw() = 0;
    friend class GameLoop;
    };
}

#endif