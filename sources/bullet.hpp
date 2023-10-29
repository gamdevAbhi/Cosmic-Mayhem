#ifndef COSMIC_BULLET_HPP
#define COSMIC_BULLET_HPP

#include <engine/gameloop.hpp>

namespace Cosmic
{
    class Bullet : public Engine::Component
    {
    public:
        Engine::Transform* target;
        glm::vec3 direction;
    protected:
        Engine::Transform* transform;
        float speed = 9.5f;
        float maxLength = 40.f;
        int desiredTag;
        void start();
        void update();
        void onCollisionEnter(Engine::BoxCollider* collider);
    };
}

#endif