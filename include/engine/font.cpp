#include <engine/font.hpp>

Engine::Font::Font(std::string relative_font_path)
{
    if(Resources::is_file_exist(Resources::get_current_dir() + relative_font_path))
    {
        Handler::debug("font path not exist", "Font");
        return;
    }

    font_path = Resources::get_current_dir() + relative_font_path;
}

// get font character
std::map<char, Engine::Character> Engine::Font::getCharacter(int fontSize)
{
    if(character_map.find(fontSize) == character_map.end()
    && addCharacter(fontSize)) return std::map<char, Engine::Character>();
    else return character_map[fontSize];
}

// add font character
bool Engine::Font::addCharacter(int fontSize)
{
    std::map<char, Character> newCharacters;
    FT_Library fLibrary;
    FT_Face face;

    if(FT_Init_FreeType(&fLibrary))
    {
        Handler::debug("font can't be instantiate", "Font");
        return false;
    }

    if(FT_New_Face(fLibrary, font_path.c_str(), 0, &face))
    {
        Handler::debug("font can't create new face", "Font");
        return false;
    }

    FT_Set_Pixel_Sizes(face, 0, fontSize);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(unsigned char c = 0; c < 128; c++)
    {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            Handler::debug("font can't load a character", "Font");
            continue;
        }

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
        face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = 
        {
            texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        newCharacters.insert(std::pair<char, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    FT_Done_Face(face);
    FT_Done_FreeType(fLibrary);

    character_map.insert(std::pair<int, std::map<char, Character>>(fontSize, newCharacters));

    return true;
}