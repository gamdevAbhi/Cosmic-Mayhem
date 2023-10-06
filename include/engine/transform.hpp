#ifndef ENGINE_TRANSFORM_HPP
#define ENGINE_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <engine/component.hpp>

namespace Engine
{
    class Transform final : public Component
    {
    public:
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