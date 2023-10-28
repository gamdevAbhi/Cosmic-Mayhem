#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

#include <engine/actor.hpp>
#include <engine/window.hpp>
#include <engine/handler.hpp>
#include <engine/component.hpp>
#include <engine/transform.hpp>

namespace Engine
{
    // Camera class
    class Camera : public Component
    {
    public:
        float nearClip = 0.1f;
        float farClip = 100.0f;
        float orthographicSize = 10.0f;
        glm::mat4 getOrtho();
        glm::vec2 getBoundary();
        glm::vec2 getWorldToScreenPos(glm::vec3 worldPosition);
        glm::vec3 getScreenToWorldPos(glm::vec2 screenPos);
        float getDiagonal();
        static Camera* getRenderCamera();
    protected:
        void setDestroy();
    private:
        inline static Camera* renderCamera = nullptr;
        inline static Window* gameWindow = nullptr;
        glm::mat4 ortho;
        void updateOrtho();
    friend class GameLoop;
    };
}

#endif