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