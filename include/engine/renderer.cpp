#include <engine/renderer.hpp>

// compare two sprite renderer
bool Engine::Renderer::compare(Engine::Renderer *left, Engine::Renderer *right)
{
    return left->order > right->order;
}

// get the index
unsigned int Engine::Renderer::getOrder()
{
    return order;
}

// calls before start drawing
void Engine::Renderer::beforeDraw()
{
    if(shouldSort == false) return;

    int index = 0;

    // removing null renderers
    while(index < renderers.size())
    {
        if(renderers[index] != nullptr) index++;
        else
        {
            renderers.erase(renderers.begin() + index);
        }
    }

    // sorting
    std::sort(renderers.begin(), renderers.end(), compare);
    shouldSort = false;
}