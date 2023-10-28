#ifndef ENGINE_SPRITE_RENDERER_HPP
#define ENGINE_SPRITE_RENDERER_HPP

#include <glad/glad.h>
#include <engine/vao.hpp>
#include <engine/vbo.hpp>
#include <engine/ebo.hpp>
#include <engine/camera.hpp>
#include <engine/handler.hpp>
#include <engine/shader.hpp>
#include <engine/sprite.hpp>
#include <engine/quadtree.hpp>
#include <algorithm>

namespace Engine
{
    // data structure for vertices
    struct vertex
    {
        glm::vec3 position;
        glm::vec2 uv;
    };
    
    // sprite renderer for rendering 2d plane
    class SpriteRenderer : public Component
    {
    public:
        glm::vec4 color;
        void setOrder(unsigned int index);
        unsigned int getOrder();
        void setSprite(Sprite* sprite);
        static int lastRenderCount();
    protected:
        inline static Shader* shader = nullptr;
        inline static Sprite* defaultSprite = nullptr;
        inline static QuadTree* root = nullptr;
        inline static int count = 0;
        inline static std::vector<vertex> vertices;
        inline static std::vector<GLuint> indices;
        inline static VAO* vao;
        inline static VBO* vbo;
        inline static EBO* ebo;
        Sprite* sprite;
        Node* node;
        unsigned int order;
        void start();
        void onTransformChanged();
        virtual void onDestroy();
    private:
        static void initialize();
        static bool compare(SpriteRenderer* left, SpriteRenderer* right);
        static void draw();
    friend class GameLoop;
    };
}


#endif