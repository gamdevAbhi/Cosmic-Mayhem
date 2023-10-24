#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

#include <vector>

namespace Engine
{
    class Actor;
    class BoxCollider;
    
    // base component class
    class Component
    {
    public:
        // get the attached actor
        Actor* getActor();
        virtual void setDestroy();
    protected:
        bool shouldDestroy = false;
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
        // called when transform is changed
        virtual void onTransformChanged();
        // called when collision detected
        virtual void onCollisionEnter(BoxCollider* boxCollider);
        virtual void onCollisionStay(BoxCollider* boxCollider);
        virtual void onCollisionExit(BoxCollider* boxCollider);
        virtual void onTriggerEnter(BoxCollider* boxCollider);
        virtual void onTriggerStay(BoxCollider* boxCollider);
        virtual void onTriggerExit(BoxCollider* boxCollider);
        // called when component is destroying
        virtual void onDestroy();
    friend class Actor;
    friend class Transform;
    friend class BoxCollider;
    friend class GameLoop;
    };
}

#endif