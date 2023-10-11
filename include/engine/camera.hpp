#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

#include <engine/actor.hpp>
#include <engine/window.hpp>
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
        glm::mat4 getMatrix();
        static Camera* getRenderCamera();
    private:
        inline static Camera* renderCamera = nullptr;
        inline static Window* gameWindow = nullptr;
    friend class GameLoop;
    };
}

#endif