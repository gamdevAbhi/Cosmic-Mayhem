#include <engine/actor.hpp>

Engine::Actor::~Actor()
{
    // deleting all components from the actor
    for(int i = 0; i < components.size(); i++)
    {
        delete components[i];
        components.erase(components.begin() + i);
    }
}

// get an actor
Engine::Actor* Engine::Actor::createActor(std::string name)
{
    // creating actor
    Actor* actor = new Actor();
    actor->name = name;
    actor->active = true;
    // creating transform component class
    Transform* transform = new Transform();
    transform->actor = actor;
    transform->start();
    // adding the transform component and actor class
    actor->components.push_back(transform);
    actors.push_back(actor);

    return actor;
}

// set actor active status
void Engine::Actor::setActive(bool status)
{
    this->active = status;
}

// destroy the actor
void Engine::Actor::destroy(Actor* actor)
{
    if(actor == nullptr) return;

    for(int i = 0; i < actors.size(); i++)
    {
        if(actors[i] == actor)
        {
            actors.erase(actors.begin() + i);
            break;
        }
    }

    delete actor;
}