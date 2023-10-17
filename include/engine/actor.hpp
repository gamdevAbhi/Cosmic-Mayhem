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
        bool manualDestroy;
        // member functions
        void setDestroy();
        void setActive(bool status);
        bool getActive();
        template <class T> T* addComponent();
        template <class T> T* getComponent();
        template <class T> std::vector<T*> getComponents(); 
        // static member functions
        static Actor* createActor(std::string name);
    protected:
        // protected member variable
        bool active;
        bool shouldDestroy;
        static void destroy(Actor* actor);
        static void destroy(Component* component);
    private:
        // private member variable
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

#endif