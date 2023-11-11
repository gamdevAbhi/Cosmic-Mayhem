#ifndef COSMIC_ASTEROID_HPP
#define COSMIC_ASTEROID_HPP

#include <engine/gameloop.hpp>

#include "health.hpp"

namespace Cosmic
{
    class Asteroid : public Engine::Component
    {
    public:
        glm::vec3 direction;
        Engine::Transform* target;
        static int getCount();
        void calculateDamage();
    protected:
        float speed;
        float damage;
        float minSpeed = 12.f;
        float maxSpeed = 35.f;
        float maxDistance = 120.f;
        float baseDamage = 8.f;
        int asteroidTag;
        int spaceshipTag;
        Engine::Transform* transform;
        inline static int count = 0;
        void start();
        void update();
        void onCollisionEnter(Engine::Collider* collider);
        void onDestroy();
    };
}

#endif