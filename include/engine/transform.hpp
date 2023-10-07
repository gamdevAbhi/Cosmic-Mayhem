#ifndef ENGINE_TRANSFORM_HPP
#define ENGINE_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <engine/component.hpp>

namespace Engine
{
    class Transform final : Component
    {
    public:
        inline static const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        inline static const glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
        inline static const glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    private:
        void start();
        inline void update() {};
        inline void fixedUpdate() {};
        inline void lateUpdate() {};
        inline void onDestroy() {};
        friend class Actor;
    };
}

#endif