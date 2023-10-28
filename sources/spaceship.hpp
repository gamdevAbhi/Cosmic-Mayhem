#ifndef COSMIC_SPACESHIP_HPP
#define COSMIC_SPACESHIP_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class SpaceShip : public Engine::Component
    {
    public:
        double forwardSpeed = 5.f;
        double backwardSpeed = 4.5f;
        double rotateSpeed = 6.f;
        void moveForward();
        void moveBackward();
        void rotateLeft();
        void rotateRight();
    protected:
        Engine::Transform* transform;
        Engine::SpriteRenderer* renderer;
        Engine::Sprite* shipSprite;
        void start();
        void onDestroy();
    };
}

#endif