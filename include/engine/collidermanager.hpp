#ifndef ENGINE_COLLIDER_MANAGER_HPP
#define ENGINE_COLLIDER_MANAGER_HPP

#include <engine/actor.hpp>
#include <engine/transform.hpp>
#include <engine/boxcollider.hpp>

namespace Engine
{
    class ColliderManager
    {
    protected:
        static void startDetection();
        static bool checkCollision(BoxCollider* collider1, BoxCollider* collider2);
    };
}

#endif