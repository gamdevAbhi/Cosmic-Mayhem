#ifndef ENGINE_COMPONENT_HPP
#define ENGINE_COMPONENT_HPP

namespace engine
{
    class Component
    {
    public:
        virtual void awake();
        virtual void start();
        virtual void update();
        virtual void fixedUpdate();
        virtual void lateUpdate();
        virtual void onDestroy();
        Actor* getActor();
    private:
        Actor* actor;
        inline static std::vector<Component*> components;
    };
}

#endif