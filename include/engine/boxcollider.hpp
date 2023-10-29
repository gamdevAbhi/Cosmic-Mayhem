#ifndef ENGINE_BOX_COLLIDER_HPP
#define ENGINE_BOX_COLLIDER_HPP

#include <glm/glm.hpp>
#include <engine/actor.hpp>
#include <engine/component.hpp>
#include <engine/transform.hpp>
#include <engine/quadtree.hpp>
#include <map>

namespace Engine
{
    class BoxCollider : public Component
    {
    public:
        void setBoundary(float left, float right, float up, float down);
        void setFixed(bool x, bool y);
        void setTag(int tag);
        int getTag();
        std::tuple<bool, bool> getFixed();
        glm::vec2 getWidth();
        glm::vec2 getHeight();
        void setTrigger(bool isTrigger);
    protected:
        inline static QuadTree** rootP = nullptr;
        int tag;
        float left;
        float right;
        float up;
        float down;
        bool isTrigger;
        bool fixed_x;
        bool fixed_y;
        bool isMoved;
        Transform* transform;
        std::map<BoxCollider*, bool> colliders;
        Node* node;
        void start();
        void onTransformChanged();
        void onDestroy();
        void call(BoxCollider* collider, glm::vec3 axis);
        void stackUpdate();
        std::vector<glm::vec3> getVertices();
        std::vector<glm::vec3> getAxis();
        glm::vec2 getProjection(glm::vec3 axis);
        static bool isOverLap(glm::vec2 project1, glm::vec2 project2);
        static double getOverLap(glm::vec2 project1, glm::vec2 project2);
    friend class ColliderManager;
    };
}

#endif