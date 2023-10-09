#include <engine/vbo.hpp>

Engine::VBO::VBO(GLsizeiptr size, const void* data)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    unbind();
}

void Engine::VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void Engine::VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Engine::VBO::destroy()
{
    glDeleteBuffers(1, &id);
}