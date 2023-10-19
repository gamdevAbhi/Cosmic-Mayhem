#include "childmaker.hpp"

void Cosmic::ChildMaker::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
    input = Engine::GameLoop::getInput();
}

void Cosmic::ChildMaker::update()
{
    if(input->getKeyStatus(GLFW_KEY_F) == KEY_PRESS)
    {
        Engine::Actor* child = Engine::Actor::createActor("Child");
        child->addComponent<Engine::SpriteRenderer>();
        Engine::Transform* transform = child->getComponent<Engine::Transform>();
        transform->setParent(this->transform);
        transform->setPosition(false, glm::vec3(-4.0f, 0.0f, 0.0f));
    }
    else if(input->getKeyStatus(GLFW_KEY_E) == KEY_PRESS)
    {
        transform->getChild(transform->getChildsSize() - 1)->getActor()->setDestroy();
    }
    else if(input->getKeyStatus(GLFW_KEY_I) == KEY_PRESS)
    {
        std::cout << "Child = " << transform->getChildsSize() << std::endl;
        std::cout << "Frame = " << Engine::Time::getLastFPS() << std::endl;
    }
}