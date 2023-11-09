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
        glm::vec2 getScale();
        unsigned int getCharPerLine();
        int getFontSize();
        void setFont(Font* font);
        void setText(std::string text);
        void setTextColor(glm::vec4 color);
        void setScale(glm::vec2 scale);
        void setCharPerLine(unsigned int chars);
    protected:
        inline static Font* defaultFont = nullptr;
        inline static QuadTree* root = nullptr;
        inline static Shader* shader = nullptr;
        inline static VAO* vao = nullptr;
        inline static VBO* vbo = nullptr;
        inline static EBO* ebo = nullptr;
        std::vector<vertex> vertices;
        std::vector<glm::vec2> offsets;
        std::vector<Sprite*> sprites;
        Node* node;
        Font* font;
        std::string text;
        glm::vec4 textColor;
        glm::vec2 scale;
        unsigned int charPerLine;
        int fontSize;
        float lengthX;
        float lengthY;
        void start();
        void onTransformChanged();
        void updateProperties();
        void nodeUpdate();
        void onDestroy();
        void setFontSize(int fontSize);
    private:
        static void initialize();
        void draw();
    friend class RendererManager;
    };
}

#endif