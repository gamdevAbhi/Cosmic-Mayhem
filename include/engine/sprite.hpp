#ifndef ENGINE_SPRITE_HPP
#define ENGINE_SPRITE_HPP

#include <stb/stb_image.h>
#include <engine/resources.hpp>
#include <iostream>

namespace Engine
{
    // create sprite texture
    class Sprite
    {
    public:
        Sprite(std::string relative_file_path);
        void destroy();
    private:
        GLuint id;
        void bind();
        void unbind();
    friend class SpriteRenderer;
    };
}

#endif