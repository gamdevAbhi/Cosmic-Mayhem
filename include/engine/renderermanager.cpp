#include <engine/renderermanager.hpp>

// get the last render count
int Engine::RendererManager::getLastRenderCount()
{
    return count;
}

// initialize all the renderers
void Engine::RendererManager::initialize()
{
    Renderer::initialize();
    SpriteRenderer::initField();
    Billboard::initField();
}

// finding all the renderers which needed to drawn
void Engine::RendererManager::findRenderers()
{
    // clearing the renderers
    sprites.clear();
    billboards.clear();
    count = 0;

    // finding the sprite renderers which needed be drawn
    Engine::Camera* camera = Engine::Camera::getRenderCamera();
    glm::mat4 camera_matrix = camera->getOrtho();

    glm::vec2 position = camera->getActor()->getComponent<Transform>()->getWorldPosition();
    std::vector<Node*> nodes;

    SpriteRenderer::root->find(AABB(position.x, position.y, camera->getDiagonal()), nodes);

    for(int i = 0; i < nodes.size(); i++) sprites.push_back(dynamic_cast<SpriteRenderer*>(nodes[i]->object));
    
    // finding the billboard renderers which needed be drawn
    glm::mat4 ortho = UI::getOrtho();
    glm::vec2 resolution = UI::getResolution();
    nodes.clear();

    float area = std::sqrt(std::pow(resolution.x, 2) + std::pow(resolution.y, 2));

    Billboard::root->find(AABB(resolution.x / 2.f, resolution.y / 2.f, area / 2.f), nodes);

    if(nodes.size() == 0) return;
    for(int i = 0; i < nodes.size(); i++) billboards.push_back(dynamic_cast<Billboard*>(nodes[i]->object));

    // sorting the renderers
    if(sprites.size() > 0) std::sort(sprites.begin(), sprites.end(), Renderer::compare);
    if(billboards.size() > 0) std::sort(billboards.begin(), billboards.end(), Renderer::compare);
}

// drawing the renderers which are in world
void Engine::RendererManager::drawWorld()
{
    for(int i = 0; i < sprites.size(); i++) 
    {
        if(sprites[i]->getActor()->getActive()) 
        {
            sprites[i]->draw();
            count++;
        }
    }
}

// drawing the renderers which are in screen
void Engine::RendererManager::drawScreen()
{
    for(int i = 0; i < billboards.size(); i++)
    {
        if(billboards[i]->getActor()->getActive())
        {
            billboards[i]->draw();
            count++;
        }
    }
}