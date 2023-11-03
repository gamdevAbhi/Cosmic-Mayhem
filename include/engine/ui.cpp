#include <engine/ui.hpp>

// get the UI resolution
glm::vec2 Engine::UI::getResolution()
{
    return glm::vec2(width, height);
}

// get ortho resolution
glm::mat4 Engine::UI::getOrtho()
{
    return orthoMatrix;
}

// get matrix respective to the anchor
glm::mat4 Engine::UI::getMatrix(Engine::UI::Anchor anchor)
{
    return uIMatrix[anchor];
}

// set the UI resolution
void Engine::UI::setResolution(int width, int height)
{
    UI::width = width;
    UI::height = height;

    updateOrthoMatrix();
    updateUIMatrix();
}

// update the ortho matrix
void Engine::UI::updateOrthoMatrix()
{
    glm::mat4 ortho = glm::ortho(0.f, (float)width, 0.f, (float)height, 0.1f, 100.f);

    glm::mat4 translate(1.f);
    glm::mat4 rotation(1.f);
    glm::mat4 scale(1.f);
    glm::mat4 view(1.f);

    translate = glm::translate(translate, glm::vec3(0.f, 0.f, 10.f));
    rotation = glm::mat4_cast(glm::quat(glm::vec3(0.f)));
    scale = glm::scale(scale, glm::vec3(1.f));

    view = translate * rotation * scale;

    orthoMatrix = ortho * glm::inverse(view);
}

// updating the ui matrix
void Engine::UI::updateUIMatrix()
{
    // positions respective to the ui
    glm::vec3 tl_position = glm::vec3(0.f, height, 0.f);
    glm::vec3 tc_position = glm::vec3((float)width / 2.f, height, 0.f);
    glm::vec3 tr_position = glm::vec3(width, height, 0.f);
    glm::vec3 l_position = glm::vec3(0.f, (float)height / 2.f, 0.f);
    glm::vec3 c_position = glm::vec3((float)width / 2.f, (float)height / 2.f, 0.f);
    glm::vec3 r_position = glm::vec3(width, (float)height / 2.f, 0.f);
    glm::vec3 bl_position = glm::vec3(0.f);
    glm::vec3 bc_position = glm::vec3((float)width / 2.f, 0.f, 0.f);
    glm::vec3 br_position = glm::vec3(width, 0.f, 0.f);

    // assigning the matrix respective to their location
    uIMatrix[TOP_LEFT] = glm::translate(glm::mat4(1.f), tl_position) * 
    glm::mat4_cast(glm::quat(glm::vec3(0.f))) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
    uIMatrix[TOP_CENTER] = glm::translate(glm::mat4(1.f), tc_position) * 
    glm::mat4_cast(glm::quat(glm::vec3(0.f))) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
    uIMatrix[TOP_RIGHT] = glm::translate(glm::mat4(1.f), tr_position) * 
    glm::mat4_cast(glm::quat(glm::vec3(0.f))) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
    uIMatrix[LEFT] = glm::translate(glm::mat4(1.f), l_position) * 
    glm::mat4_cast(glm::quat(glm::vec3(0.f))) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
    uIMatrix[CENTER] = glm::translate(glm::mat4(1.f), c_position) * 
    glm::mat4_cast(glm::quat(glm::vec3(0.f))) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
    uIMatrix[RIGHT] = glm::translate(glm::mat4(1.f), r_position) * 
    glm::mat4_cast(glm::quat(glm::vec3(0.f))) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
    uIMatrix[BOTTOM_LEFT] = glm::translate(glm::mat4(1.f), bl_position) * 
    glm::mat4_cast(glm::quat(glm::vec3(0.f))) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
    uIMatrix[BOTTOM_CENTER] = glm::translate(glm::mat4(1.f), bc_position) * 
    glm::mat4_cast(glm::quat(glm::vec3(0.f))) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
    uIMatrix[BOTTOM_RIGHT] = glm::translate(glm::mat4(1.f), br_position) * 
    glm::mat4_cast(glm::quat(glm::vec3(0.f))) * glm::scale(glm::mat4(1.f), glm::vec3(1.f));
}