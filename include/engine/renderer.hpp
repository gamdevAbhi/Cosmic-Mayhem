#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include <glad/glad.h>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>
#include <engine/ebo.hpp>
#include <engine/actor.hpp>
#include <engine/handler.hpp>
#include <engine/component.hpp>
#include <algorithm>

namespace Engine
{
    // data structure for vertices
    struct vertex
    {
        glm::vec3 position;
        glm::vec2 uv;
    };

    class Renderer : public Component
    {
    public:
        int getOrder();
        void setOrder(int index);
    protected:
        int order;
        virtual void draw() = 0;
        static bool compare(Renderer* left, Renderer* right);
    friend class RendererManager;
    };
}

#endif