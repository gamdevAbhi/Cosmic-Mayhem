#include <engine/buttonmanager.hpp>

// initialize function
void Engine::ButtonManager::initialize()
{
    Button::root = new QuadTree(AABB(0, 0, 100));
}

// check interaction
void Engine::ButtonManager::checkInteraction()
{
    std::vector<Node*> nodes;
    std::vector<Node*> allNodes;
    Button::root->find(Input::getMousePos(), nodes);
    Button::root->find(Button::root->boundary, allNodes);

    for(int i = 0; i < nodes.size(); i++)
    {
        Button* button = dynamic_cast<Button*>(nodes[i]->object);
        
        if(!isHover(button)) continue;

        button->hovered();

        Input::KeyStatus mouseStatus = Input::getMouseButtonStatus(GLFW_MOUSE_BUTTON_1);

        if(button->clickStatus == Button::BUTTON_NONE && mouseStatus == Input::KEY_HOLD 
        || button->clickStatus == Button::BUTTON_RELEASE && mouseStatus == Input::KEY_HOLD) continue;
        else if(mouseStatus == Input::KEY_PRESS || mouseStatus == Input::KEY_HOLD) button->clicked();
    }

    for(int i = 0; i < allNodes.size(); i++)
    {
        Button* button = dynamic_cast<Button*>(allNodes[i]->object);
        button->updateStatus();
    }
}

// check if mouse is hovering button
bool Engine::ButtonManager::isHover(Button* button)
{
    std::vector<glm::vec3> axises = button->getAxis();
    std::vector<glm::vec3> vertices = button->getVertices();
    glm::vec3 pos = glm::vec3(Input::getMousePos(), 0.f);
    glm::vec3 pointAxis;
    double distance = DBL_MAX;

    for(int i = 0; i < vertices.size(); i++)
    {
        glm::vec3 axis = vertices[0] - pos;
        double length = glm::length(axis);

        if(length < distance)
        {
            distance = length;
            pointAxis = axis;
        }
    }

    axises.push_back(glm::normalize(pointAxis));

    for(int i = 0; i < axises.size(); i++)
    {
        glm::vec2 projection = button->getProjection(axises[i]);
        double pointProj = glm::dot(axises[i], pos);

        if(projection.x > pointProj || projection.y < pointProj) return false;
    }

    return true;
}
