#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

#include <vector>

namespace Engine
{
    class Actor;
    
    // base component class
    class Component
    {
    protected:
        virtual Actor* getActor() final;
    private:
        Actor* actor;
        virtual void start() = 0;
        virtual void update() = 0;
        virtual void fixedUpdate() = 0;
        virtual void lateUpdate() = 0;
        virtual void onDestroy() = 0;
        friend class Actor;
    };
}

#endif