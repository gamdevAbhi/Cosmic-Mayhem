#ifndef ENGINE_SPRITE_RENDERER_HPP
#define ENGINE_SPRITE_RENDERER_HPP

#include <glad/glad.h>
#include <engine/renderer.hpp>

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
    protected:
        inline static Shader* shader = nullptr;
        std::vector<vertex> vertices;
        std::vector<GLuint> indices;
        VAO* vao;
        VBO* vbo;
        EBO* ebo;
        SpriteRenderer();
        ~SpriteRenderer();
        virtual void draw();
    friend class Actor;
    };
}


#endif