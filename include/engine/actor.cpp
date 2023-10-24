#include <engine/actor.hpp>

// destructor
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

// actor will be destroyed in next update loop
void Engine::Actor::setDestroy()
{
    shouldDestroy = true;
}

// set the actor's active status
void Engine::Actor::setActive(bool status)
{
    Transform* transform = getComponent<Transform>();
    Transform* parent = transform->getParent();

    if(parent != nullptr && parent->actor->getActive() == false && status == true) return;
    
    active = status;
    for(int i = 0; i < transform->getChildsSize(); i++) transform->getChild(i)->actor->setActive(status);
}

// get actor active status
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
    actor->shouldDestroy = false;
    // creating transform component class
    Component* transform = new Transform();
    transform->actor = actor;
    dynamic_cast<Transform*>(transform)->refSiblings = &actor->components;
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

    Transform* transform = actor->getComponent<Transform>();
    Transform* parent = transform->getParent();
    if(parent != nullptr) parent->removeChild(transform);

    while(transform->getChildsSize() > 0)
    {
        Actor::destroy(transform->getChild(0)->actor);
    }

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

// destroy the component
void Engine::Actor::destroy(Component* component)
{
    Actor* actor = component->actor;
    
    for(int i = 0; i < actor->components.size(); i++)
    {
        if(actor->components[i] != component) continue;
        actor->components.erase(actor->components.begin() + i);
        break;
    }

    component->onDestroy();
    delete component;
}