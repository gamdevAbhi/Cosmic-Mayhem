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

// get position respective to the anchor
glm::vec3 Engine::UI::getPosition(Engine::UI::Anchor anchor)
{
    return uIPos[anchor];
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
    updateUIPos();
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

// updating the UI position
void Engine::UI::updateUIPos()
{
    // positions respective to the UI
    uIPos[TOP_LEFT] = glm::vec3(0.f, height, 0.f);
    uIPos[TOP_CENTER] = glm::vec3((float)width / 2.f, height, 0.f);
    uIPos[TOP_RIGHT] = glm::vec3(width, height, 0.f);
    uIPos[LEFT] = glm::vec3(0.f, (float)height / 2.f, 0.f);
    uIPos[CENTER] = glm::vec3((float)width / 2.f, (float)height / 2.f, 0.f);
    uIPos[RIGHT] = glm::vec3(width, (float)height / 2.f, 0.f);
    uIPos[BOTTOM_LEFT] = glm::vec3(0.f);
    uIPos[BOTTOM_CENTER] = glm::vec3((float)width / 2.f, 0.f, 0.f);
    uIPos[BOTTOM_RIGHT] = glm::vec3(width, 0.f, 0.f);
}

// update UI Matrix
void Engine::UI::updateUIMatrix()
{
    for(int i = 0; i < 9; i++)
    {
        glm::mat4 translate(1.f);
        glm::mat4 rotation(1.f);
        glm::mat4 scale(1.f);

        translate = glm::translate(translate, uIPos[i]);
        rotation = glm::mat4_cast(glm::quat(glm::vec3(0.f)));
        scale = glm::scale(scale, glm::vec3(1.f));

        uIMatrix[i] = translate * rotation * scale;
    }
}