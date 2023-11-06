#include "buttonclicker.hpp"

void Cosmic::ButtonClicker::start()
{
    rect = getActor()->getComponent<Engine::RectTransform>();
    billboard = getActor()->addComponent<Engine::Billboard>();
    button = getActor()->addComponent<Engine::Button>();

    billboard->setColor(glm::vec4(1.f, 0.f, 0.f, 0.8f));
}

void Cosmic::ButtonClicker::update()
{
    if(button->getHoverStatus() == Engine::Button::HOVER_ENTER && shouldScale == true)
    {
        rect->setAnchorScale(glm::vec3(2.f, 2.f, 1.f));
    }
    else if(button->getHoverStatus() == Engine::Button::HOVER_STAY && shouldRotate == true)
    {
        glm::vec3 rotation = rect->getAnchorRotation();
        rotation.z += Engine::Time::getFixedDeltaTime() * 2.f;
        rect->setAnchorRotation(rotation);
    }
    else if(button->getHoverStatus() == Engine::Button::HOVER_EXIT && shouldScale == true)
    {
        rect->setAnchorScale(glm::vec3(1.f));
    }

    if(button->getClickStatus() == Engine::Button::BUTTON_CLICK)
    {
        float r = std::rand() % 100 / 100.f;
        float g = std::rand() % 100 / 100.f;
        float b = std::rand() % 100 / 100.f;

        billboard->setColor(glm::vec4(r, g, b, 0.8f));
    }
}