#ifndef ENGINE_VBO_HPP
#define ENGINE_VBO_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace Engine
{
    class VBO
    {
    public:
        VBO(GLsizeiptr size, const void* data);
        void bind();
        void unbind();
        void destroy();
    private:
        GLuint id;
    };
}

#endif