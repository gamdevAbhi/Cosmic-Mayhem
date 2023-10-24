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
        inline static glm::vec3 currentAxis;
        inline static double currentOverlap;
        inline static QuadTree* root;
        static void initialize();
        static void startDetection();
        static void narrowPhase(Node* node);
        static void collisionDetected(BoxCollider* collider1, BoxCollider* collider2);
        static bool checkCollision(BoxCollider* collider1, BoxCollider* collider2);
    friend class GameLoop;
    };
}

#endif