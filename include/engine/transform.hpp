#ifndef ENGINE_TRANSFORM_HPP
#define ENGINE_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine/component.hpp>
#include <engine/handler.hpp>

namespace Engine
{
    // transform class
    class Transform final : public Component
    {
    public:
        glm::vec3 getRight(bool isWorld);
        glm::vec3 getUp(bool isWorld);
        glm::vec3 getForward(bool isWorld);
        glm::vec3 getOrientedVector(glm::vec3 vector);
        glm::vec3 getWorldPosAt(glm::vec3 localOffset);
        glm::vec3 getPosition(bool isWorld);
        glm::vec3 getRotation(bool isWorld);
        glm::vec3 getScale(bool isWorld);
        glm::mat4 getMatrix();
        Transform* getChild(int index);
        Transform* getParent();
        int getChildsSize();
        void setPosition(bool isWorld, glm::vec3 position);
        void setRotation(bool isWorld, glm::vec3 rotation);
        void setScale(bool isWorld, glm::vec3 scale);
        void setParent(Transform* transform);
    protected:
        glm::vec3 localPosition;
        glm::vec3 localRotation;
        glm::vec3 localScale;
        glm::vec3 worldPosition;
        glm::vec3 worldRotation;
        glm::vec3 worldScale;
        glm::mat4 localMatrix;
        glm::mat4 worldMatrix;
        std::vector<Component*>* refSiblings;
        std::vector<Transform*> childs;
        Transform* parent = nullptr;
        void start();
        void updateWorldMatrix();
        void updateLocalMatrix();
        void setDestroy();
        void removeChild(Transform* transform);
        void addChild(Transform* transform);
        static glm::vec3 calculatePosition(glm::mat4 matrix);
        static glm::vec3 calculateRotation(glm::mat4 matrix);
        static glm::vec3 calculateScale(glm::mat4 matrix);
        static glm::vec3 fixRotation(glm::vec3 rotation);
    friend class Actor;
    };
}

#endif