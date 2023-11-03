#include <engine/actor.hpp>

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

// create an actor
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

// create an UI actor
Engine::Actor* Engine::Actor::createUIActor(std::string name)
{
    // creating actor
    Actor* actor = new Actor();
    actor->name = name;
    actor->manualDestroy = false;
    actor->active = true;
    actor->shouldDestroy = false;
    // creating transform component class
    Component* transform = new RectTransform();
    transform->actor = actor;
    dynamic_cast<RectTransform*>(transform)->refSiblings = &actor->components;
    transform->start();
    // adding the transform component and actor class
    actor->components.push_back(transform);
    actors.push_back(actor);

    return actor;
}

// get actor by name
Engine::Actor* Engine::Actor::getActor(std::string name)
{
    for(int i = 0; i < actors.size(); i++)
    {
        if(actors[i]->name == name) return actors[i];
    }

    return nullptr;
}

// get actors by name
std::vector<Engine::Actor*> Engine::Actor::getActors(std::string name)
{
    std::vector<Engine::Actor*> matchActors;

    for(int i = 0; i < actors.size(); i++)
    {
        if(actors[i]->name == name) matchActors.push_back(actors[i]);
    }

    return matchActors;
}

// get total actor count
int Engine::Actor::getActorCount()
{
    return actors.size();
}

// create main camera actor
void Engine::Actor::createMainCamera()
{
    // creating actor
    Actor* actor = new Actor();
    actor->name = "Main Camera";
    actor->manualDestroy = false;
    actor->active = true;
    actor->shouldDestroy = false;
    // creating transform component class
    Component* transform = new Transform();
    transform->actor = actor;
    dynamic_cast<Transform*>(transform)->refSiblings = &actor->components;
    // creating camera component class
    Component* camera = new Camera();
    camera->actor = actor;
    dynamic_cast<Camera*>(camera)->transform = dynamic_cast<Transform*>(transform);
    transform->start();
    camera->start();
    // adding the transform component and actor class
    actor->components.push_back(transform);
    actor->components.push_back(camera);
    actors.push_back(actor);
}

// destroy the actor
void Engine::Actor::destroy(Actor* actor)
{
    if(actor == nullptr) return;

    Transform* transform = actor->getComponent<Transform>();
    
    if(transform != nullptr)
    {
        Transform* parent = transform->getParent();
        if(parent != nullptr) parent->removeChild(transform);

        while(transform->getChildsSize() > 0)
        {
            Actor::destroy(transform->getChild(0)->actor);
        }
    }
    else
    {
        RectTransform* rect = actor->getComponent<RectTransform>();
        RectTransform* parent = rect->getParent();
        if(parent != nullptr) parent->removeChild(rect);

        while(rect->getChildsSize() > 0)
        {
            Actor::destroy(rect->getChild(0)->actor);
        }
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