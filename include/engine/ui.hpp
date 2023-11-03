#ifndef ENGINE_UI_HPP
#define ENGINE_UI_HPP

#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine/component.hpp>

namespace Engine
{ 
    class UI : public Component
    {
    public:
        enum Anchor
        {
            TOP_LEFT, TOP_CENTER, TOP_RIGHT, 
            LEFT, CENTER, RIGHT, 
            BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
        };
        static glm::vec2 getResolution();
        static glm::mat4 getOrtho();
        static glm::mat4 getMatrix(Anchor anchor);
        static void setResolution(int width, int height);
    protected:
        inline static int width;
        inline static int height;
        inline static glm::mat4 orthoMatrix;
        inline static glm::mat4 uIMatrix[9];
        static void updateOrthoMatrix();
        static void updateUIMatrix();
    };
}

#endif