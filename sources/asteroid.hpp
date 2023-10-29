#ifndef COSMIC_ASTEROID_HPP
#define COSMIC_ASTEROID_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class Asteroid : public Engine::Component
    {
    public:
        glm::vec3 direction;
        Engine::Transform* target;
        static int getCount();
    protected:
        float speed;
        float minSpeed = 6.f;
        float maxSpeed = 20.f;
        float maxDistance = 120.f;
        int asteroidTag;
        int spaceshipTag;
        Engine::Transform* transform;
        inline static int count = 0;
        void start();
        void update();
        void onCollisionEnter(Engine::BoxCollider* collider);
        void onDestroy();
    };
}

#endif