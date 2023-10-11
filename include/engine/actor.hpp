#ifndef ENGINE_ACTOR_HPP
#define ENGINE_ACTOR_HPP

#include <engine/component.hpp>
#include <engine/transform.hpp>
#include <engine/handler.hpp>
#include <iostream>
#include <vector>

namespace Engine
{
    // actor class
    class Actor final
    {
    public:
        // members veriables
        std::string name;
        // member functions
        void setActive(bool status);
        template <class T> T* addComponent();
        template <class T> T* getComponent();
        template <class T> std::vector<T*> getComponents(); 
        template <class T> void removeComponent();
        // static member functions
        static Actor* createActor(std::string name);
        static void destroy(Actor* actor);
    private:
        // private member variable
        bool active;
        std::vector<Component*> components;
        inline static std::vector<Actor*> actors;
        // destructor
        ~Actor();
        friend class GameLoop;
    };
}

// add components to the actor
template <class T> T* Engine::Actor::addComponent()
{
    // checking if template class is Transform or is not derived from the component class
    if(std::is_same<T, Transform>::value) Handler::error("adding transform is not allowed", name);
    if(std::is_base_of<Component, T>::value == false) Handler::error("class must be derived from Component Class", name);
    // adding the new component of the specified component class in the actor
    Component* component = new T();
    components.push_back(component);
    // adding actor ref and calling start function
    component->actor = this;
    component->start();

    return dynamic_cast<T*>(component);
} 

// get the first component of the specified component class
template <class T> T* Engine::Actor::getComponent()
{
    T* ptr = nullptr;

    // checking if the template class is derived from component class
    if(std::is_base_of<Component, T>::value == true)
    {
        // searching if the specified component class instance exist in the actor
        for(int i = 0; i < this->components.size(); i++)
        {
            ptr = dynamic_cast<T*>(this->components[i]);
            if(ptr != nullptr) break;
        }
    }

    if(ptr == nullptr) Handler::error(typeid(T).name() + " is not found", name);
    
    return ptr;
}

// get all the component of this component class exist in the actor
template <class T> std::vector<T*> Engine::Actor::getComponents()
{
    std::vector<T*> list;

    // checking if the template class is derived from component class
    if(std::is_base_of<Component, T>::value == true)
    {
        // searching all the specified component class instance exist in the actor
        for(int i = 0; i < this->components.size(); i++)
        {
            T* ptr = dynamic_cast<T*>(this->components[i]);
            if(ptr != nullptr) list.push_back(ptr);
        }
    }

    return list;
}

// remove the first component found of the specified component class in the actor
template <class T> void Engine::Actor::removeComponent()
{
    // checking if template class is Transform
    if(std::is_same<T, Transform>::value) return;
    // checking if the template class is not derived from the component class 
    if(std::is_base_of<Component, T>::value == true)
    {
        // searching if the specified component class instance exist in the actor
        for(int i = 0; i < this->components.size(); i++)
        {
            if(dynamic_cast<T*>(this->components[i]) != nullptr)
            {
                // remove the component from the actor
                this->components[i]->onDestroy();
                
                delete this->components[i];
                this->components.erase(this->components.begin() + i);
                break;
            }
        }
    }
}

#endif