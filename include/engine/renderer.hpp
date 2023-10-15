#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include <engine/actor.hpp>
#include <engine/component.hpp>
#include <engine/transform.hpp>
#include <engine/shader.hpp>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>
#include <engine/ebo.hpp>
#include <bits/stdc++.h>

namespace Engine
{
    class Renderer : public Component
    {
    public:
        virtual void setOrder(unsigned int index) = 0;
        unsigned int getOrder();
    protected:
        unsigned int order;
        virtual void draw() = 0;
        inline static bool shouldSort;
        inline static std::vector<Renderer*> renderers;
    private:
        static bool compare(Renderer* left, Renderer* right);
        static void beforeDraw();
    friend class GameLoop;
    };
}

#endif