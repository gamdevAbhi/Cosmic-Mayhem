#include <engine/gameloop.hpp>

// create window and input for the game
void Engine::GameLoop::init(std::string title, int width, 
int height)
{
    GameLoop::title = title;
    GameLoop::width = width;
    GameLoop::height = height;

    window = new Window(title.c_str(), width, height);
    input = new Input(*window);

    Camera::gameWindow = window;
    Handler::gameWindow = window;
    
    Actor* camActor = Actor::createActor("Main Camera");
    Camera::renderCamera = camActor->addComponent<Camera>();
}

// called after game is ready to execute game loop
void Engine::GameLoop::begin()
{
    double fixedTime = 0.0f;

    while(window->shouldClose() == false)
    {
        window->clearWindow();
        Time::frameStart();

        fixedTime += Time::getDeltaTime();
        // checking if fixed update should call or not
        if(fixedTime >= 0.2f)
        {
            fixedTime = 0.0f;
            callFixedUpdate();
        }

        callDestroy();
        callUpdate();
        callLateUpdate();
        callDraw();

        window->updateWindow();
        Time::frameEnd();
    }

    clearActors();

    window->close();
}

// destroy all components & actors which set as should destroy
void Engine::GameLoop::callDestroy()
{
    std::vector<Actor*> actors;

    for(int i = 0; i < Actor::actors.size(); i++)
    {
        if(Actor::actors[i]->shouldDestroy == true) actors.push_back(Actor::actors[i]);
        else
        {
            std::vector<Component*> components;

            for(Component* component : Actor::actors[i]->components)
            {
                if(component->shouldDestroy == true) components.push_back(component); 
            }

            while(components.size() > 0)
            {
                Actor::destroy(components[0]);
                components.erase(components.begin());
            }
        }
    }

    while(actors.size() > 0)
    {
        Actor::destroy(actors[0]);
        actors.erase(actors.begin());
    }
}

// get all the components of all actors
void Engine::GameLoop::getAllComponents(std::vector<Component*>& components)
{
    for(int i = 0; i < Actor::actors.size(); i++)
    {
        Actor* actor = Actor::actors[i];
        
        if(actor->active == false) continue;

        for(int j = 0; j < actor->components.size(); j++)
        {
            components.push_back(actor->components[j]);
        }
    }
}

// call the fixed update each components
void Engine::GameLoop::callFixedUpdate()
{
    std::vector<Component*> components;

    getAllComponents(components);

    while(components.size() > 0)
    {
        components[0]->fixedUpdate();
        components.erase(components.begin());
    }
}

// call the update each components
void Engine::GameLoop::callUpdate()
{
    std::vector<Component*> components;

    getAllComponents(components);

    while(components.size() > 0)
    {
        components[0]->update();
        components.erase(components.begin());
    }
}

// call the late update each components 
void Engine::GameLoop::callLateUpdate()
{
    std::vector<Component*> components;

    getAllComponents(components);

    while(components.size() > 0)
    {
        components[0]->lateUpdate();
        components.erase(components.begin());
    }
}

// call the draw of each renderers
void Engine::GameLoop::callDraw()
{
    Renderer::beforeDraw();
    
    for(int i = 0; i < Renderer::renderers.size(); i++)
    {
        if(Renderer::renderers[i]->getActor()->active == false) continue;
        Renderer::renderers[i]->draw();
    }
}

// get the input class
Engine::Input* Engine::GameLoop::getInput()
{
    return input;
}

// destroy all the actors (only non manualDestroy)
void Engine::GameLoop::clearScene()
{
    int i = 0;

    while(i < Actor::actors.size())
    {
        if(Actor::actors[i]->manualDestroy) i++;
        else Actor::destroy(Actor::actors[i]);
    }
}

// destroy all the actors (also manualDestroy)
void Engine::GameLoop::clearActors()
{
    while(Actor::actors.size() > 0)
    {
        Actor::destroy(Actor::actors[0]);
    }
}