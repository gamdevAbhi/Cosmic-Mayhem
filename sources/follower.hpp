#ifndef FOLLOWER_HPP
#define FOLLOWER_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class Follower : public Engine::Component
    {
    public:
        void initialize(Engine::Transform* target);
        void removeTarget();
    protected:
        double followSpeed = 3.5f;
        double maxDistance = 0.8f;
        Engine::Transform* target;
        Engine::Transform* transform;
        void lateUpdate();
    };
}

#endif