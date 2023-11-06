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
        static glm::vec2 getResolution();
        static glm::mat4 getOrtho();
        static glm::vec3 getAnchorPosition(glm::vec2 anchor);
        static glm::vec3 getAnchorSize(glm::vec2 size);
        static void setResolution(int width, int height);
    protected:
        inline static int width;
        inline static int height;
        inline static glm::mat4 orthoMatrix;
        static void updateOrthoMatrix();
        static void updateUIContents();
    };
}

#endif