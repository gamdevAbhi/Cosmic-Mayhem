#include <engine/sprite.hpp>

Engine::Sprite::Sprite(std::string relative_file_path)
{
    int width, height, numCh;

    stbi_set_flip_vertically_on_load(true);

    unsigned char* bytes = stbi_load((Resources::get_current_dir() + relative_file_path).c_str(),
    &width, &height, &numCh, 0);

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0);
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLenum format = numCh == 1? GL_RED : numCh == 2? GL_RG : numCh == 3? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    stbi_image_free(bytes);
    unbind();
}

// bind the sprite
void Engine::Sprite::bind()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

// unbind the sprite
void Engine::Sprite::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

// destroy the sprite
void Engine::Sprite::destroy()
{
    glDeleteTextures(1, &id);
}