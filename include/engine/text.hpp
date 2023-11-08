#ifndef ENGINE_TEXT_HPP
#define ENGINE_TEXT_HPP

#include <engine/vao.hpp>
#include <engine/vbo.hpp>
#include <engine/ebo.hpp>
#include <engine/shader.hpp>
#include <engine/sprite.hpp>
#include <engine/font.hpp>
#include <engine/renderer.hpp>
#include <engine/recttransform.hpp>
#include <engine/quadtree.hpp>

namespace Engine
{
    class Text : public Renderer
    {
    public:
        Font* getFont();
        std::string getText();
        glm::vec4 getTextColor();
        int getFontSize();
        void setFont(Font* font);
        void setText(std::string text);
        void setTextColor(glm::vec4 color);
        void setFontSize(int fontSize);
    protected:
        inline static Font* defaultFont = nullptr;
        inline static QuadTree* root = nullptr;
        inline static VAO* vao = nullptr;
        inline static VBO* vbo = nullptr;
        inline static EBO* ebo = nullptr;
        std::vector<vertex> vertices;
        std::vector<GLuint> indices;
        std::vector<Sprite*> sprites;
        Node* node;
        Font* font;
        std::string text;
        glm::vec4 textColor;
        int fontSize;
        void start();
        void onTransformChanged();
        void updateProperties();
        void nodeUpdate();
        void onDestroy();
    private:
        static void initialize();
        void draw();
    friend class RendererManager;
    };
}

#endif