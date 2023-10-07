#ifndef ENGINE_EBO_HPP
#define ENGINE_EBO_HPP

#include <glad/glad.h>
#include <vector>

namespace Engine
{
    class EBO
    {
    private:
        GLuint id;
        EBO(std::vector<GLuint>& indices);
        void bind();
        void unbind();
        void destroy();
        friend class Renderer;
    };
}

#endif