#include <engine/renderer.hpp>

// get the index
int Engine::Renderer::getOrder()
{
    return order;
}

// set draw order
void Engine::Renderer::setOrder(int index)
{
    order = index;
}

// compare two sprite renderer
bool Engine::Renderer::compare(Engine::Renderer *left, Engine::Renderer *right)
{
    return left->order > right->order;
}

// initialize the members of renderer
void Engine::Renderer::initialize()
{
    vertices = std::vector<vertex>
    {
        vertex{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
        vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
        vertex{glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
        vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)}
    };
    indices = std::vector<GLuint>
    {
        0, 1, 3,
        0, 2, 3
    };

    vao = new VAO();
    vao->bind();
    vbo = new VBO(vertices.size() * sizeof(vertex), vertices.data(), GL_STATIC_DRAW);
    vbo->bind();
    ebo = new EBO(indices.size() * sizeof(GLuint), indices.data());
    ebo->bind();

    vao->link(*vbo, 0, 3, sizeof(vertex), (void*)0);
    vao->link(*vbo, 1, 2, sizeof(vertex), (void*)(3 * sizeof(float)));

    vbo->unbind();
    vao->unbind();
    ebo->unbind();
}