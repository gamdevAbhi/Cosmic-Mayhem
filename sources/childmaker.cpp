#include "childmaker.hpp"

void Cosmic::ChildMaker::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
    input = Engine::GameLoop::getInput();
    indicator = Engine::Actor::createActor("Indicator");
    Engine::Transform* iTransform = indicator->getComponent<Engine::Transform>();
    iTransform->setScale(true, glm::vec3(0.25f, 0.25f, 1.0f));
    iTransform->setParent(transform);
    iTransform->setPosition(false, glm::vec3(1.0f, 1.0f, 0.0f));
    indicator->addComponent<Engine::SpriteRenderer>()->setOrder(0);
    indicator->getComponent<Engine::SpriteRenderer>()->color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    indicator->setActive(false);
}

void Cosmic::ChildMaker::update()
{
    if(input->getKeyStatus(GLFW_KEY_F) == KEY_PRESS)
    {
        Engine::Actor* child = Engine::Actor::createActor("Child");
        
        // child->addComponent<Engine::BoxCollider>();
        // if(actors.size() % 2 != 0) child->getComponent<Engine::BoxCollider>()->setTrigger(true);

        child->addComponent<Engine::SpriteRenderer>()->setOrder(0);
        if(actors.size() % 2 == 0) child->getComponent<Engine::SpriteRenderer>()->color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        else child->getComponent<Engine::SpriteRenderer>()->color = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        
        Engine::Transform* transform = child->getComponent<Engine::Transform>();
        transform->setScale(true, glm::vec3(1.f, 1.f, 1.0f));
        transform->setPosition(true, this->transform->getWorldPosAt(glm::vec3(-4.f, 0.f, 0.0f)));
        transform->setStatic(true);
        
        actors.push_back(child);
    }
    else if(input->getKeyStatus(GLFW_KEY_E) == KEY_PRESS)
    {
        actors[actors.size() - 1]->setDestroy();
        actors.pop_back();
    }
    else if(input->getKeyStatus(GLFW_KEY_I) == KEY_PRESS)
    {
        Engine::Camera* camera = Engine::Camera::getRenderCamera();
        glm::vec2 screenPos = camera->getWorldToScreenPos(transform->getPosition(true));
        glm::vec3 worldPos = camera->getScreenToWorldPos(screenPos);

        std::cout << "Child = " << actors.size() << std::endl;
        std::cout << "Frame = " << Engine::Time::getLastFPS() << std::endl;
        std::cout << "Location =" << " X : " <<  screenPos.x << " Y : " << screenPos.y << std::endl;
        std::cout << "Location =" << " X : " <<  worldPos.x << " Y : " << worldPos.y << " Z : " << worldPos.z << std::endl;
    }
    else if(input->getKeyStatus(GLFW_KEY_G) == KEY_PRESS)
    {
        Engine::Transform* cTransform = Engine::Camera::getRenderCamera()->getActor()->getComponent<Engine::Transform>();
        cTransform->setRotation(true, cTransform->getRotation(true) + glm::vec3(0.0f, 0.0f, 90.f));
    }
}

void Cosmic::ChildMaker::onCollisionEnter(Engine::BoxCollider* boxCollider)
{
    indicator->setActive(true);
}

void Cosmic::ChildMaker::onCollisionExit(Engine::BoxCollider* boxCollider)
{
    indicator->setActive(false);
}

void Cosmic::ChildMaker::onTriggerEnter(Engine::BoxCollider* boxCollider)
{
    indicator->setActive(true);
}

void Cosmic::ChildMaker::onTriggerExit(Engine::BoxCollider* boxCollider)
{
    indicator->setActive(false);
}