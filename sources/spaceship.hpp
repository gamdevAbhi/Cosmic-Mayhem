#ifndef COSMIC_SPACESHIP_HPP
#define COSMIC_SPACESHIP_HPP

#include <engine/gameloop.hpp>

#include "bullet.hpp"
#include "spritemanager.hpp"

namespace Cosmic
{
    class SpaceShip : public Engine::Component
    {
    public:
        double forwardSpeed = 15.f;
        double backwardSpeed = 12.5f;
        double rotateSpeed = 6.f;
        void moveForward();
        void moveBackward();
        void rotateLeft();
        void rotateRight();
        void shoot();
    protected:
        Engine::Transform* transform;
        Engine::Transform* shootOrigin;
        void start();
    };
}

#endif