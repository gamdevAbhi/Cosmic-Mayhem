#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

#include <vector>

namespace Engine
{
    class Actor;
    
    // base component class
    class Component
    {
    public:
        // get the attached actor
        Actor* getActor();
    protected:
        virtual ~Component() = 0;
    private:
        Actor* actor;
        // called when component is add
        virtual void start();
        // called in every frame
        virtual void update();
        // called every specific time interval
        virtual void fixedUpdate();
        // called after update
        virtual void lateUpdate();
        // called when component is destroying
        virtual void onDestroy();
    friend class Actor;
    friend class GameLoop;
    };
}

#endif