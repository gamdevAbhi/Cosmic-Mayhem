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

            // calling fixed update each actor's all component
            for(int i = 0; i < Actor::actors.size(); i++)
            {
                Actor* actor = Actor::actors[i];

                for(int j = 0; j < actor->components.size(); j++)
                {
                    actor->components[j]->fixedUpdate();
                }
            }
        }

        // calling update each actor's all component
        for(int i = 0; i < Actor::actors.size(); i++)
        {
            Actor* actor = Actor::actors[i];

            for(int j = 0; j < actor->components.size(); j++)
            {
                actor->components[j]->update();
            }
        }

        // calling late update each actor's all component
        for(int i = 0; i < Actor::actors.size(); i++)
        {
            Actor* actor = Actor::actors[i];
        
            for(int j = 0; j < actor->components.size(); j++)
            {
                actor->components[j]->lateUpdate();
            }
        }

        // calling draw function each actor's all renderer component
        for(int i = 0; i < Actor::actors.size(); i++)
        {
            Actor* actor = Actor::actors[i];

            std::vector<Renderer*> renderers = actor->getComponents<Renderer>();

            for(int j = 0; j < renderers.size(); j++)
            {
                renderers[j]->draw();
            }
        }

        window->updateWindow();
        Time::frameEnd();
    }

    window->close();
}