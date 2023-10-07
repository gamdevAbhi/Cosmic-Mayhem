#include <engine/vbo.hpp>

Engine::VBO::VBO(std::vector<vertex>& vertices)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_VERTEX_ARRAY, vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
    unbind();
}

void Engine::VBO::bind()
{
    glBindBuffer(GL_VERTEX_ARRAY, id);
}

void Engine::VBO::unbind()
{
    glBindBuffer(GL_VERTEX_ARRAY, 0);
}

void Engine::VBO::destroy()
{
    glDeleteBuffers(1, &id);
}