#ifndef ENGINE_RECT_TRANSFORM_HPP
#define ENGINE_RECT_TRANSFORM_HPP

#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <engine/ui.hpp>
#include <engine/component.hpp>
#include <engine/handler.hpp>

namespace Engine
{
    class RectTransform : public Component
    {
    public:
        glm::vec3 getAnchorUp();
        glm::vec3 getAnchorRight();
        glm::vec3 getAnchorForward();
        glm::vec3 getScreenUp();
        glm::vec3 getScreenRight();
        glm::vec3 getScreenForward();
        glm::vec3 getScreenPosAt(glm::vec3 localOffset);
        glm::vec3 getAnchorPosition();
        glm::vec3 getAnchorRotation();
        glm::vec3 getAnchorScale();
        glm::vec3 getScreenPosition();
        glm::vec3 getScreenRotation();
        glm::vec3 getScreenScale();
        glm::vec2 getRectSize();
        UI::Anchor getAnchor();
        int getChildsSize();
        RectTransform* getChild(int index);
        RectTransform* getParent();
        glm::mat4 getPivotMatrix(UI::Anchor anchor);
        glm::mat4 getScreenMatrix();
        void setAnchorPosition(glm::vec3 position);
        void setAnchorRotation(glm::vec3 rotation);
        void setAnchorScale(glm::vec3 scale);
        void setScreenPosition(glm::vec3 position);
        void setScreenRotation(glm::vec3 rotation);
        void setScreenScale(glm::vec3 scale);
        void setRectSize(glm::vec2 rectSize);
        void setParent(RectTransform* transform);
        void setAnchor(UI::Anchor anchor);
    protected:
        glm::vec3 anchorPosition;
        glm::vec3 anchorRotation;
        glm::vec3 anchorScale;
        glm::vec3 screenPosition;
        glm::vec3 screenRotation;
        glm::vec3 screenScale;
        glm::vec2 rectSize;
        glm::mat4 anchorMatrix;
        glm::mat4 nonScaledMatrix;
        glm::mat4 pivotMatrix[9];
        glm::mat4 screenMatrix;
        std::vector<Component*>* refSiblings;
        std::vector<RectTransform*> childs;
        UI::Anchor anchor = UI::CENTER;
        RectTransform* parent = nullptr;
        void start();
        void setDestroy();
        void updatePivotMatrixArray();
        void updateAnchorProperties();
        void updateScreenProperties();
        void addChild(RectTransform* transform);
        void removeChild(RectTransform* transform);
        static glm::vec3 fixRotation(glm::vec3 rotation);
        static glm::vec3 calculatePosition(glm::mat4 matrix);
        static glm::vec3 calculateRotation(glm::mat4 matrix);
        static glm::vec3 calculateScale(glm::mat4 matrix);
    friend class Actor;
    };
}

#endif