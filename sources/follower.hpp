#ifndef FOLLOWER_HPP
#define FOLLOWER_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class Follower : public Engine::Component
    {
    public:
        double followSpeed = 3.5f;
        double maxDistance = 1.75f;
        Engine::Transform* target;
        Engine::Transform* transform;
    protected:
        void start();
        void lateUpdate();
    };
}

#endif