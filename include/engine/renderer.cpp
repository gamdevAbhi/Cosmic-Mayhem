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

// add renderer to renderering
void Engine::Renderer::addRenderer(Renderer* renderer)
{
    renderers.push_back(renderer);
    shouldSort = true;
}

// remove renderer from rendering
void Engine::Renderer::removeRenderer(Renderer* renderer)
{
    int i = 0;

    while(i < renderers.size())
    {
        if(renderers[i] != renderer) 
        {
            i++;
            continue;
        }
        renderers.erase(renderers.begin() + i);
    }

    shouldSort = true;
}

// call when order is changed
void Engine::Renderer::orderChanged()
{
    shouldSort = true;
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