#ifndef ENGINE_FONT_HPP
#define ENGINE_FONT_HPP

#include <ft2build.h>
#include FT_FREETYPE_H
#include <engine/handler.hpp>
#include <engine/resources.hpp>
#include <engine/recttransform.hpp>
#include <map>

namespace Engine
{
    struct Character
    {
        unsigned int texture;
        glm::ivec2 size;
        glm::ivec2 bearing;
        long int advance;
    };

    class Font
    {
    public:
        Font(std::string relative_font_path);
    protected:
        std::string font_path;
        std::map<int, std::map<char, Character>> character_map;
        std::map<char, Character> getCharacter(int fontSize);
        bool addCharacter(int fontSize);
    friend class Text;
    };
}

#endif