#include <engine/recttransform.hpp>

// get the anchor up direction
glm::vec3 Engine::RectTransform::getAnchorUp()
{
    glm::mat4 screen_matrix = getMatrix(UI::CENTER);
    glm::vec3 anchor_up;

    anchor_up.x = screen_matrix[1][0];
    anchor_up.y = screen_matrix[1][1];
    anchor_up.z = screen_matrix[1][2];

    return anchor_up;
}

// get the anchor right direction
glm::vec3 Engine::RectTransform::getAnchorRight()
{
    glm::mat4 screen_matrix = getMatrix(UI::CENTER);
    glm::vec3 anchor_right;

    anchor_right.x = screen_matrix[0][0];
    anchor_right.y = screen_matrix[0][1];
    anchor_right.z = screen_matrix[0][2];

    return anchor_right;
}

// get the anchor forward direction
glm::vec3 Engine::RectTransform::getAnchorForward()
{
    glm::mat4 screen_matrix = getMatrix(UI::CENTER);
    glm::vec3 anchor_forward;

    anchor_forward.x = screen_matrix[2][0];
    anchor_forward.y = screen_matrix[2][1];
    anchor_forward.z = screen_matrix[2][2];

    return anchor_forward;
}

// get the screen up direction
glm::vec3 Engine::RectTransform::getScreenUp()
{
    return glm::vec3(0.f, 1.f, 0.f);
}

// get the screen right direction
glm::vec3 Engine::RectTransform::getScreenRight()
{
    return glm::vec3(1.f, 0.f, 0.f);
}

// get the screen forward direction
glm::vec3 Engine::RectTransform::getScreenForward()
{
    return glm::vec3(0.f, 0.f, 1.f);
}

// get the screen position respective to the anchor transform
glm::vec3 Engine::RectTransform::getScreenPosAt(glm::vec3 localOffset)
{
    glm::mat4 translate(1.0f);
    glm::mat4 rotation(1.0f);
    glm::mat4 scale(1.0f);

    translate = glm::translate(translate, anchorPosition + localOffset);
    rotation = glm::mat4_cast(glm::quat(anchorRotation));
    scale = glm::scale(scale, anchorScale);

    glm::mat4 newLocalMatrix = translate * rotation * scale;
    glm::mat4 newWorldMatrix = (parent != nullptr)? parent->getMatrix(anchor) * newLocalMatrix : 
    UI::getMatrix(anchor) * newLocalMatrix;

    return glm::vec3(newWorldMatrix[3][0], newWorldMatrix[3][1], newWorldMatrix[3][2]);
}

// get the anchor position
glm::vec3 Engine::RectTransform::getAnchorPosition()
{
    return anchorPosition;
}

// get the anchor rotation
glm::vec3 Engine::RectTransform::getAnchorRotation()
{
    return anchorRotation;
}

// get the anchor scale
glm::vec3 Engine::RectTransform::getAnchorScale()
{
    return anchorScale;
}

// get the screen position
glm::vec3 Engine::RectTransform::getScreenPosition()
{
    return screenPosition;
}

// get the screen rotation
glm::vec3 Engine::RectTransform::getScreenRotation()
{
    return screenRotation;
}

// get the screen scale
glm::vec3 Engine::RectTransform::getScreenScale()
{
    return screenScale;
}

// get the rect sizze
glm::vec2 Engine::RectTransform::getRectSize()
{
    return rectSize;
}

// get the anchor
Engine::UI::Anchor Engine::RectTransform::getAnchor()
{
    return anchor;
}

// get childs size
int Engine::RectTransform::getChildsSize()
{
    return childs.size();
}

// get the child
Engine::RectTransform* Engine::RectTransform::getChild(int index)
{
    if(childs.size() <= index) Handler::debug("child index is out of bound", "");
    return childs[index];
}

// get the parent
Engine::RectTransform* Engine::RectTransform::getParent()
{
    return parent;
}

// get the screen matrix
glm::mat4 Engine::RectTransform::getMatrix(UI::Anchor anchor)
{
    return screenMatrix[anchor];
}

// get the final matrix
glm::mat4 Engine::RectTransform::getRectMatrix()
{
    return rectMatrix;
}

// set the anchor position
void Engine::RectTransform::setAnchorPosition(glm::vec3 position)
{
    anchorPosition = position;
    updateScreenProperties();
}

// set the anchor rotation
void Engine::RectTransform::setAnchorRotation(glm::vec3 rotation)
{
    anchorRotation = fixRotation(rotation);
    updateScreenProperties();
}

// set the anchor scale
void Engine::RectTransform::setAnchorScale(glm::vec3 scale)
{
    anchorScale = scale;
    updateScreenProperties();
}

// set the screen position
void Engine::RectTransform::setScreenPosition(glm::vec3 position)
{
    screenPosition = position;
    updateAnchorProperties();
}

// set the screen rotation
void Engine::RectTransform::setScreenRotation(glm::vec3 rotation)
{
    screenRotation = fixRotation(rotation);
    updateAnchorProperties();
}

// set the screen scale
void Engine::RectTransform::setScreenScale(glm::vec3 scale)
{
    screenScale = scale;
    updateAnchorProperties();
}

// set the rect size
void Engine::RectTransform::setRectSize(glm::vec2 rectSize)
{
    this->rectSize = rectSize;

    updateScreenProperties();
}

// set the parent
void Engine::RectTransform::setParent(RectTransform* transform)
{
    if(transform == this) 
    {
        Handler::debug("can't make parent of own rect transform", "rect transform");
        return;
    }

    for(int i = 0; i < childs.size(); i++)
    {
        if(childs[i] != transform) continue;
        Handler::debug("can't make parent of his own child", "transform");
        return;
    }

    if(parent != nullptr) parent->removeChild(this);
    if(transform != nullptr) transform->addChild(this);
    
    parent = transform;

    updateAnchorProperties();
}

// set the anchor of the rect transform
void Engine::RectTransform::setAnchor(UI::Anchor anchor)
{
    this->anchor = anchor;
    updateScreenProperties();
}

// start function
void Engine::RectTransform::start()
{
    anchorPosition = glm::vec3(0.0f);
    anchorRotation = glm::vec3(0.0f);
    anchorScale = glm::vec3(1.0f);
    rectSize = glm::vec2(UI::getResolution().x / 10.f, UI::getResolution().y / 10.f);

    updateScreenProperties();
}

// set destroy
void Engine::RectTransform::setDestroy()
{
    Handler::error("can't destroy rect transform", "rect transform");
}

// update the anchor matrix array
void Engine::RectTransform::updateAnchorMatrixArray()
{
    glm::mat4 translate(1.0f);
    glm::mat4 rotation(1.0f);
    glm::mat4 scale(1.0f);

    // top left
    translate = glm::translate(glm::mat4(1.f), anchorPosition + glm::vec3(-rectSize.x, rectSize.y, 0.f));
    rotation = glm::mat4_cast(glm::quat(anchorRotation));
    scale = glm::scale(glm::mat4(1.f), anchorScale);
    anchorMatrix[UI::TOP_LEFT] = translate * rotation * scale;
    // top center
    translate = glm::translate(glm::mat4(1.f), anchorPosition + glm::vec3(0.f, rectSize.y, 0.f));
    rotation = glm::mat4_cast(glm::quat(anchorRotation));
    scale = glm::scale(glm::mat4(1.f), anchorScale);
    anchorMatrix[UI::TOP_CENTER] = translate * rotation * scale;
    // top right
    translate = glm::translate(glm::mat4(1.f), anchorPosition + glm::vec3(rectSize.x, rectSize.y, 0.f));
    rotation = glm::mat4_cast(glm::quat(anchorRotation));
    scale = glm::scale(glm::mat4(1.f), anchorScale);
    anchorMatrix[UI::TOP_RIGHT] = translate * rotation * scale;
    // left
    translate = glm::translate(glm::mat4(1.f), anchorPosition + glm::vec3(-rectSize.x, 0.f, 0.f));
    rotation = glm::mat4_cast(glm::quat(anchorRotation));
    scale = glm::scale(glm::mat4(1.f), anchorScale);
    anchorMatrix[UI::LEFT] = translate * rotation * scale;
    // center
    translate = glm::translate(glm::mat4(1.f), anchorPosition);
    rotation = glm::mat4_cast(glm::quat(anchorRotation));
    scale = glm::scale(glm::mat4(1.f), anchorScale);
    anchorMatrix[UI::CENTER] = translate * rotation * scale;
    // right
    translate = glm::translate(glm::mat4(1.f), anchorPosition + glm::vec3(rectSize.x, 0.f, 0.f));
    rotation = glm::mat4_cast(glm::quat(anchorRotation));
    scale = glm::scale(glm::mat4(1.f), anchorScale);
    anchorMatrix[UI::RIGHT] = translate * rotation * scale;
    // bottom left
    translate = glm::translate(glm::mat4(1.f), anchorPosition + glm::vec3(-rectSize.x, -rectSize.y, 0.f));
    rotation = glm::mat4_cast(glm::quat(anchorRotation));
    scale = glm::scale(glm::mat4(1.f), anchorScale);
    anchorMatrix[UI::BOTTOM_LEFT] = translate * rotation * scale;
    // bottom center
    translate = glm::translate(glm::mat4(1.f), anchorPosition + glm::vec3(0.f, -rectSize.y, 0.f));
    rotation = glm::mat4_cast(glm::quat(anchorRotation));
    scale = glm::scale(glm::mat4(1.f), anchorScale);
    anchorMatrix[UI::BOTTOM_CENTER] = translate * rotation * scale;
    // bottom right
    translate = glm::translate(glm::mat4(1.f), anchorPosition + glm::vec3(rectSize.x, -rectSize.y, 0.f));
    rotation = glm::mat4_cast(glm::quat(anchorRotation));
    scale = glm::scale(glm::mat4(1.f), anchorScale);
    anchorMatrix[UI::BOTTOM_RIGHT] = translate * rotation * scale;
}

// update the screen matrix array
void Engine::RectTransform::updateScreenMatrixArray()
{
    // top left
    screenMatrix[UI::TOP_LEFT] = (parent != nullptr)? parent->getMatrix(anchor) * anchorMatrix[UI::TOP_LEFT] :
    UI::getMatrix(anchor) * anchorMatrix[UI::TOP_LEFT];
    // top center
    screenMatrix[UI::TOP_CENTER] = (parent != nullptr)? parent->getMatrix(anchor) * anchorMatrix[UI::TOP_CENTER] :
    UI::getMatrix(anchor) * anchorMatrix[UI::TOP_CENTER];
    // top right
    screenMatrix[UI::TOP_RIGHT] = (parent != nullptr)? parent->getMatrix(anchor) * anchorMatrix[UI::TOP_RIGHT] :
    UI::getMatrix(anchor) * anchorMatrix[UI::TOP_RIGHT];
    // left
    screenMatrix[UI::LEFT] = (parent != nullptr)? parent->getMatrix(anchor) * anchorMatrix[UI::LEFT] :
    UI::getMatrix(anchor) * anchorMatrix[UI::LEFT];
    // center
    screenMatrix[UI::CENTER] = (parent != nullptr)? parent->getMatrix(anchor) * anchorMatrix[UI::CENTER] :
    UI::getMatrix(anchor) * anchorMatrix[UI::CENTER];
    // right
    screenMatrix[UI::RIGHT] = (parent != nullptr)? parent->getMatrix(anchor) * anchorMatrix[UI::RIGHT] :
    UI::getMatrix(anchor) * anchorMatrix[UI::RIGHT];
    // bottom left
    screenMatrix[UI::BOTTOM_LEFT] = (parent != nullptr)? parent->getMatrix(anchor) * anchorMatrix[UI::BOTTOM_LEFT] :
    UI::getMatrix(anchor) * anchorMatrix[UI::BOTTOM_LEFT];
    // bottom center
    screenMatrix[UI::BOTTOM_CENTER] = (parent != nullptr)? parent->getMatrix(anchor) * anchorMatrix[UI::BOTTOM_CENTER] :
    UI::getMatrix(anchor) * anchorMatrix[UI::BOTTOM_CENTER];
    // bottom right
    screenMatrix[UI::BOTTOM_RIGHT] = (parent != nullptr)? parent->getMatrix(anchor) * anchorMatrix[UI::BOTTOM_RIGHT] :
    UI::getMatrix(anchor) * anchorMatrix[UI::BOTTOM_RIGHT];
}

// update the rect matrix
void Engine::RectTransform::updateRectMatrix()
{
    glm::mat4 translate(1.f);
    glm::mat4 rotation(1.f);
    glm::mat4 scale(1.f);

    translate = glm::translate(translate, screenPosition);
    rotation = glm::mat4_cast(glm::quat(screenRotation));
    scale = glm::scale(scale, glm::vec3(screenScale.x * rectSize.x, screenScale.y * rectSize.y, screenScale.z));

    rectMatrix = translate * rotation * scale;
}

// update the anchor properties
void Engine::RectTransform::updateAnchorProperties()
{
    glm::mat4 translate(1.0f);
    glm::mat4 rotation(1.0f);
    glm::mat4 scale(1.0f);

    translate = glm::translate(translate, screenPosition);
    rotation = glm::mat4_cast(glm::quat(screenRotation));
    scale = glm::scale(scale, screenScale);

    screenMatrix[UI::CENTER] = translate * rotation * scale;

    glm::mat4 anchorMatrix = (parent != nullptr)? glm::inverse(parent->getMatrix(anchor)) * screenMatrix[UI::CENTER] :
    glm::inverse(UI::getMatrix(anchor)) * screenMatrix[UI::CENTER];

    anchorPosition = calculatePosition(anchorMatrix);
    anchorRotation = calculateRotation(anchorMatrix);
    anchorScale = calculateScale(anchorMatrix);

    updateAnchorMatrixArray();
    updateScreenMatrixArray();
    updateRectMatrix();

    for(int i = 0; i < childs.size(); i++) childs[i]->updateScreenProperties();

    for(int i = 0; i < refSiblings->size(); i++) (*refSiblings)[i]->onTransformChanged();
}

// update the screen properties
void Engine::RectTransform::updateScreenProperties()
{
    updateAnchorMatrixArray();
    
    glm::mat4 screenMatrix = (parent != nullptr)? parent->getMatrix(anchor) * anchorMatrix[UI::CENTER] : 
    UI::getMatrix(anchor) * anchorMatrix[UI::CENTER];

    screenPosition = calculatePosition(screenMatrix);
    screenRotation = calculateRotation(screenMatrix);
    screenScale = calculateScale(screenMatrix);

    updateScreenMatrixArray();
    updateRectMatrix();

    for(int i = 0; i < childs.size(); i++) childs[i]->updateScreenProperties();

    for(int i = 0; i < refSiblings->size(); i++) (*refSiblings)[i]->onTransformChanged();
}

// add child
void Engine::RectTransform::addChild(RectTransform* transform)
{
    childs.push_back(transform);
}

// remove child
void Engine::RectTransform::removeChild(RectTransform* transform)
{
    for(int i = 0; i < childs.size(); i++)
    {
        if(childs[i] != transform) continue;
        childs.erase(childs.begin() + i);
        break;
    }
}

// fix the rotation to -360 to 360
glm::vec3 Engine::RectTransform::fixRotation(glm::vec3 rotation)
{
    glm::vec3 fixRotation;

    fixRotation.x = (rotation.x - (int)rotation.x) + (int)rotation.x % 360;
    fixRotation.y = (rotation.y - (int)rotation.y) + (int)rotation.y % 360;
    fixRotation.z = (rotation.z - (int)rotation.z) + (int)rotation.z % 360;

    if(fixRotation.x < -360.f) fixRotation.x = std::abs(fixRotation.x) - 360.f;
    if(fixRotation.y < -360.f) fixRotation.y = std::abs(fixRotation.y) - 360.f;
    if(fixRotation.z < -360.f) fixRotation.z = std::abs(fixRotation.z) - 360.f;

    return fixRotation;
}

// calculate the position from the matrix
glm::vec3 Engine::RectTransform::calculatePosition(glm::mat4 matrix)
{
    glm::vec3 position;
    
    position.x = matrix[3][0];
    position.y = matrix[3][1];
    position.z = matrix[3][2];
    
    return position;
}

// calculate the rotation from the matrix
glm::vec3 Engine::RectTransform::calculateRotation(glm::mat4 matrix)
{
    glm::mat3 rotationMatrix;
    glm::vec3 scale = calculateScale(matrix);

    rotationMatrix[0] = matrix[0] / scale.x;
    rotationMatrix[1] = matrix[1] / scale.y;
    rotationMatrix[2] = matrix[2] / scale.z;
    
    float roll = 0;
    float pitch = 0;
    float yaw = 0;

    if(rotationMatrix[0][2] != -1 && rotationMatrix[0][2] != 1)
    {
        pitch = -1 * glm::asin(rotationMatrix[0][2]);
        roll = glm::atan2(rotationMatrix[1][2] / glm::cos(pitch), 
        rotationMatrix[2][2] / glm::cos(pitch));
        yaw = glm::atan2(rotationMatrix[0][1] / glm::cos(pitch), 
        rotationMatrix[0][0] / glm::cos(pitch));
    }
    else
    {
        if(rotationMatrix[0][2] == -1)
        {
            pitch = glm::pi<float>() / 2.0f;
            roll = yaw + glm::atan2(rotationMatrix[1][0], rotationMatrix[2][0]);
        }
        else
        {
            pitch = -glm::pi<float>() / 2.0f;
            roll = -yaw + glm::atan2(-1.0f * rotationMatrix[1][0], -1.0f * rotationMatrix[2][0]);
        }
    }

    glm::vec3 rotation = glm::vec3(roll * 180.0f / glm::pi<float>(), pitch * 180.0f / glm::pi<float>(), 
    yaw * 180.0f / glm::pi<float>());
    
    return rotation;
}

// calculate the scale from the matrix
glm::vec3 Engine::RectTransform::calculateScale(glm::mat4 matrix)
{
    glm::vec3 scale;

    scale.x = glm::sqrt(matrix[0][0] * matrix[0][0] + matrix[0][1] * matrix[0][1] 
    + matrix[0][2] * matrix[0][2]);
    scale.y = glm::sqrt(matrix[1][0] * matrix[1][0] + matrix[1][1] * matrix[1][1] 
    + matrix[1][2] * matrix[1][2]);
    scale.z = glm::sqrt(matrix[2][0] * matrix[2][0] + matrix[2][1] * matrix[2][1] 
    + matrix[2][2] * matrix[2][2]);

    return scale;
}