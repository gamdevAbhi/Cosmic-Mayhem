#include <engine/ebo.hpp>

Engine::EBO::EBO(GLsizeiptr size, const void* data)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    unbind();
}

void Engine::EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void Engine::EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Engine::EBO::destroy()
{
    glDeleteBuffers(1, &id);
}