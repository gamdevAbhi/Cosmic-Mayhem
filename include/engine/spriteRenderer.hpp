#ifndef ENGINE_SPRITE_RENDERER_HPP
#define ENGINE_SPRITE_RENDERER_HPP

#include <glad/glad.h>
#include <engine/handler.hpp>
#include <engine/shader.hpp>
#include <engine/renderer.hpp>
#include <engine/camera.hpp>

namespace Engine
{
    // data structure for vertices
    struct vertex
    {
        glm::vec3 position;
        glm::vec2 uv;
    };
    
    // sprite renderer for rendering 2d plane
    class SpriteRenderer : public Renderer
    {
    public:
        glm::vec4 color;
        void setOrder(int index);
    protected:
        inline static Shader* shader = nullptr;
        int order;
        std::vector<vertex> vertices;
        std::vector<GLuint> indices;
        VAO* vao;
        VBO* vbo;
        EBO* ebo;
        void start();
        virtual void draw();
    };
}


#endif