#ifndef FOLLOWER_HPP
#define FOLLOWER_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class Follower : public Engine::Component
    {
    public:
        double followSpeed = 2.5f;
        double maxLength = 3.f;
        Engine::Transform* target;
        Engine::Transform* transform;
    protected:
        void start();
        void lateUpdate();
        void move();
    };
}

#endif