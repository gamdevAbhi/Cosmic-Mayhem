#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

#include <glm/gtc/matrix_transform.hpp>
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
        const bool perspective = true;
        const bool orthographic = false;
        bool projectionMode = orthographic;
        float nearClip = 0.1f;
        float farClip = 100.0f;
        float orthographicSize = 10.0f;
        float fov = 45.0f;
        glm::mat4 getMatrix();
        static Camera* getRenderCamera();
    private:
        inline static Camera* renderCamera = nullptr;
        inline static Window* gameWindow = nullptr;
    friend class GameLoop;
    };
}

#endif