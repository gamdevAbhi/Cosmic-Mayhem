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
    class Renderer : Component
    {
    protected:
        std::vector<vertex> vertices;
        std::vector<GLuint> indices;
        Renderer();
    private:
        // shader
        // texture
        VAO vao;
        VBO vbo;
        EBO ebo;
        virtual void start() final;
        virtual void update();
        virtual void fixedUpdate();
        virtual void lateUpdate();
        virtual void onDestroy();
        virtual void draw();
    };
}

#endif