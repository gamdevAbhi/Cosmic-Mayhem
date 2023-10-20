#ifndef ENGINE_BOX_COLLIDER_HPP
#define ENGINE_BOX_COLLIDER_HPP

#include <glm/glm.hpp>
#include <engine/actor.hpp>
#include <engine/component.hpp>
#include <engine/transform.hpp>
#include <map>

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
        std::map<BoxCollider*, bool> colliders;
        void start();
        void onDestroy();
        void call(BoxCollider* collider, glm::vec3 axis);
        void stackUpdate();
        std::vector<glm::vec3> getVertices();
        std::vector<glm::vec3> getAxis();
        glm::vec2 getProjection(glm::vec3 axis);
        static bool isOverLap(glm::vec2 project1, glm::vec2 project2);
        static double getOverLap(glm::vec2 project1, glm::vec2 project2);
        inline static std::vector<BoxCollider*> boxColliders;
    friend class ColliderManager;
    };
}

#endif