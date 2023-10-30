#ifndef ENGINE_ACTOR_HPP
#define ENGINE_ACTOR_HPP

#include <engine/component.hpp>
#include <engine/transform.hpp>
#include <engine/handler.hpp>
#include <iostream>
#include <vector>

namespace Engine
{
    class Actor final
    {
    public:
        std::string name;
        bool manualDestroy;
        void setDestroy();
        void setActive(bool status);
        bool getActive();
        template <class T> T* addComponent();
        template <class T> T* getComponent();
        template <class T> std::vector<T*> getComponents(); 
        static Actor* createActor(std::string name);
        static Actor* getActor(std::string name);
        static int getActorCount();
    protected:
        bool active;
        bool shouldDestroy;
        static void destroy(Actor* actor);
        static void destroy(Component* component);
    private:
        std::vector<Component*> components;
        inline static std::vector<Actor*> actors;
        ~Actor();
        friend class GameLoop;
        friend class BoxCollider;
    };
}

// add components to the actor
template <class T> T* Engine::Actor::addComponent()
{
    if(std::is_same<T, Transform>::value) 
    {
        Handler::error("adding transform is not allowed", name);
    }

    if(std::is_base_of<Component, T>::value == false)
    {
        Handler::error("class must be derived from Component Class", name);
    }

    Component* component = new T();
    components.push_back(component);
    component->actor = this;
    component->start();

    return dynamic_cast<T*>(component);
} 

// get the first component of the specified component class
template <class T> T* Engine::Actor::getComponent()
{
    T* ptr = nullptr;

    if(std::is_base_of<Component, T>::value == true)
    {
        for(int i = 0; i < this->components.size(); i++)
        {
            ptr = dynamic_cast<T*>(this->components[i]);
            if(ptr != nullptr) break;
        }
    }
    
    return ptr;
}

// get all the component of this component class exist in the actor
template <class T> std::vector<T*> Engine::Actor::getComponents()
{
    std::vector<T*> list;

    if(std::is_base_of<Component, T>::value == true)
    {
        for(int i = 0; i < this->components.size(); i++)
        {
            T* ptr = dynamic_cast<T*>(this->components[i]);
            if(ptr != nullptr) list.push_back(ptr);
        }
    }

    return list;
}

#endif