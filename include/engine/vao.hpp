#ifndef ENGINE_VAO_HPP
#define ENGINE_VAO_HPP

#include <glad/glad.h>
#include <engine/vbo.hpp>

namespace Engine
{
    class VAO
    {
    private:
        VAO();
        void bind();
        void unbind();
        void link(VBO& vbo, GLint index, GLuint size, GLsizeiptr stride, void* offset);
        void destroy();
        GLuint id;
        friend class Renderer;
    };
}

#endif