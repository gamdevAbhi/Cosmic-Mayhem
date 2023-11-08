#ifndef ENGINE_SPRITE_RENDERER_HPP
#define ENGINE_SPRITE_RENDERER_HPP

#include <engine/renderer.hpp>
#include <engine/camera.hpp>
#include <engine/shader.hpp>
#include <engine/sprite.hpp>
#include <engine/quadtree.hpp>

namespace Engine
{    
    // sprite renderer for rendering 2d plane
    class SpriteRenderer : public Renderer
    {
    public:
        glm::vec4 getColor();
        Sprite* getSprite();
        void setColor(glm::vec4 color);
        void setSprite(Sprite* sprite);
    protected:
        inline static std::vector<vertex> vertices;
        inline static std::vector<GLuint> indices;
        inline static VAO* vao = nullptr;
        inline static VBO* vbo = nullptr;
        inline static EBO* ebo = nullptr;
        inline static Shader* shader = nullptr;
        inline static Sprite* defaultSprite = nullptr;
        inline static QuadTree* root = nullptr;
        Sprite* sprite;
        Node* node;
        glm::vec4 color;
        void start();
        void onTransformChanged();
        virtual void onDestroy();
    private:
        static void initialize();
        void draw();
    friend class RendererManager;
    };
}


#endif