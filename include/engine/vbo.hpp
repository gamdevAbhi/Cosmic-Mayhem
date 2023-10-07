#ifndef ENGINE_VBO_HPP
#define ENGINE_VBO_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

namespace Engine
{
    struct vertex
    {
        glm::vec3 position;
        glm::vec2 uv;
    };

    class VBO
    {
    private:
        GLuint id;
        VBO(std::vector<vertex>& vertices);
        void bind();
        void unbind();
        void destroy();
        friend class VAO;
        friend class Renderer;
    };
}

#endif