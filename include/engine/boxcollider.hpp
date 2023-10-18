#ifndef ENGINE_BOX_COLLIDER_HPP
#define ENGINE_BOX_COLLIDER_HPP

#include <glm/glm.hpp>
#include <engine/actor.hpp>
#include <engine/component.hpp>
#include <engine/transform.hpp>

namespace Engine
{
    class BoxCollider : public Component
    {
    public:
        void setBoundary(float left, float right, float up, float down);
        glm::vec2 getWidth();
        glm::vec2 getHeight();
        void setTrigger(bool isTrigger);
    protected:
        float left;
        float right;
        float up;
        float down;
        bool isTrigger;
        Transform* transform;
        void start();
        void onDestroy();
        void call(BoxCollider* collider);
        std::vector<glm::vec3> getVertices();
        std::vector<glm::vec3> getAxis();
        glm::vec2 getProjection(glm::vec3 axis);
        static bool isOverLap(glm::vec2 project_1, glm::vec2 project_2);
        inline static std::vector<BoxCollider*> boxColliders;
    friend class ColliderManager;
    };
}

#endif