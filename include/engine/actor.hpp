#ifndef ENGINE_ACTOR_HPP
#define ENGINE_ACTOR_HPP

#include <engine/component.hpp>
#include <iostream>
#include <vector>

namespace engine
{
    class Actor
    {
    public:
        bool active;
        std::string name;
        Actor(std::string name);
        template <typename T> void addComponent();
        template <typename T> T* getComponent(); 
        template <typename T> void removeComponent();
        static void destroy(Actor& actor);
    private:
        std::vector<Component> components;
    };
}

#endif