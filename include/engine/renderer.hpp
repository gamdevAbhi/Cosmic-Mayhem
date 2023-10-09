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
    protected:
        virtual void draw() = 0;
        virtual ~Renderer();
    friend class GameLoop;
    };
}

#endif