#ifndef ENGINE_SPRITE_RENDERER_HPP
#define ENGINE_SPRITE_RENDERER_HPP

#include <glad/glad.h>
#include <engine/camera.hpp>
#include <engine/handler.hpp>
#include <engine/shader.hpp>
#include <engine/sprite.hpp>
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
        void setOrder(unsigned int index);
        void setSprite(Sprite* sprite);
    protected:
        inline static Shader* shader = nullptr;
        inline static Sprite* defaultSprite = nullptr;
        std::vector<vertex> vertices;
        std::vector<GLuint> indices;
        VAO* vao;
        VBO* vbo;
        EBO* ebo;
        Sprite* sprite;
        void start();
        virtual void draw();
        virtual void onDestroy();
    friend class GameLoop;
    };
}


#endif