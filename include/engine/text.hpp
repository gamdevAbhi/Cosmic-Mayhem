#ifndef ENGINE_TEXT_HPP
#define ENGINE_TEXT_HPP

#include <engine/vao.hpp>
#include <engine/vbo.hpp>
#include <engine/ebo.hpp>
#include <engine/shader.hpp>
#include <engine/font.hpp>
#include <engine/renderer.hpp>
#include <engine/recttransform.hpp>

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
        inline static Shader* shader = nullptr;
        inline static Font* defaultFont = nullptr;
        inline static VAO* vao = nullptr;
        inline static VBO* vbo = nullptr;
        inline static EBO* ebo = nullptr;
        std::vector<vertex> vertices;
        std::vector<GLuint> indices;
        Font* font;
        std::string text;
        glm::vec4 textColor;
        int fontSize;
        void updateVertices();
        void draw();
        static void initialize();
    friend class RendererManager;
    };
}

#endif