#include <engine/actor.hpp>

Engine::Actor::~Actor()
{
    // deleting all components from the actor
    for(int i = 0; i < components.size(); i++)
    {
        components[i]->onDestroy();
        delete components[i];
    }

    components.clear();
}

void Engine::Actor::setActive(bool status)
{
    Transform* transform = getComponent<Transform>();
    Transform* parent = transform->getParent();

    if(parent != nullptr && parent->actor->getActive() == false && status == true) return;
    
    active = status;
    for(int i = 0; i < transform->getChildsSize(); i++) transform->getChild(i)->actor->setActive(status);
}

bool Engine::Actor::getActive()
{
    return active;
}

// get an actor
Engine::Actor* Engine::Actor::createActor(std::string name)
{
    // creating actor
    Actor* actor = new Actor();
    actor->name = name;
    actor->manualDestroy = false;
    actor->active = true;
    // creating transform component class
    Component* transform = new Transform();
    transform->actor = actor;
    transform->start();
    // adding the transform component and actor class
    actor->components.push_back(transform);
    actors.push_back(actor);

    return actor;
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