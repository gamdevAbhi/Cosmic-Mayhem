#include <engine/renderer.hpp>

void Engine::Renderer::start()
{
    vao = VAO();
    vbo = VBO(vertices);
    ebo = EBO(indices);
}

void Engine::Renderer::update()
{

}

void Engine::Renderer::fixedUpdate()
{

}

void Engine::Renderer::lateUpdate()
{

}

void Engine::Renderer::onDestroy()
{
    
}

void Engine::Renderer::draw()
{
    Actor* actor = getActor();
    Transform* transform = actor->getComponent<Transform>();

    glm::mat4 position(1.0f);
    glm::mat4 rotation(1.0f);
    glm::mat4 scale(1.0f);

    position = glm::translate(position, transform->position);
    rotation = glm::mat4_cast(glm::quat(transform->rotation));
    scale = glm::scale(scale, transform->scale);


    // pass references to shader
    
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}