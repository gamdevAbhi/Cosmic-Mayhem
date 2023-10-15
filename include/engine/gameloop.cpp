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

        std::vector<Component*> components;

        for(int i = 0; i < Actor::actors.size(); i++)
        {
            Actor* actor = Actor::actors[i];
            
            if(actor->active == false) continue;

            for(int j = 0; j < actor->components.size(); j++)
            {
                components.push_back(actor->components[j]);
            }
        }


        // checking if fixed update should call or not
        if(fixedTime >= 0.2f)
        {
            fixedTime = 0.0f;

            // calling fixed update each component
            for(int i = 0; i < components.size(); i++)
            {
                components[i]->fixedUpdate();
            }
        }

        // calling update each component
        for(int i = 0; i < components.size(); i++)
        {
            components[i]->update();
        }

        // calling late update each component
        for(int i = 0; i < components.size(); i++)
        {
            components[i]->lateUpdate();
        }

        // calling draw function each renderer component

        Renderer::beforeDraw();

        for(int i = 0; i < Renderer::renderers.size(); i++)
        {
            if(Renderer::renderers[i]->getActor()->active == false) continue;
            Renderer::renderers[i]->draw();
        }

        window->updateWindow();
        Time::frameEnd();
    }

    clearActors();

    window->close();
}

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