#include "button.hpp"

void Cosmic::Button::initialize(void (*function)(), glm::vec4 borderColor, glm::vec4 bgColor, std::string text)
{
    transform = getActor()->getComponent<Engine::RectTransform>();
    Engine::Billboard* billboard = getActor()->addComponent<Engine::Billboard>();
    button = getActor()->addComponent<Engine::Button>();
    callback = function;

    billboard->setOrder(2);
    billboard->setColor(borderColor);
    scale = transform->getAnchorSize();

    Engine::RectTransform* bg = Engine::Actor::createUIActor("background")->getComponent<Engine::RectTransform>();
    Engine::Billboard* bgBillboard = bg->getActor()->addComponent<Engine::Billboard>();
    this->text = bg->getActor()->addComponent<Engine::Text>();

    bg->setParent(transform);
    bg->setAnchorSize(glm::vec2(0.95f, 0.9f));
    bgBillboard->setOrder(1);
    bgBillboard->setColor(bgColor);
    this->text->setAlignment(Engine::Text::MIDDLE);
    this->text->setText(text);
    this->text->setTextColor(glm::vec4(0.f, 0.f, 0.f, 1.f));
}

void Cosmic::Button::update()
{
    if(button->getClickStatus() == Engine::Button::BUTTON_CLICK)
    {
        (*callback)();
        return;
    }
    
    if(button->getHoverStatus() == Engine::Button::HOVER_ENTER)
    {
        transform->setAnchorSize(scale * 1.5f);
        text->setScale(1.25f);
    }
    else if(button->getHoverStatus() == Engine::Button::HOVER_EXIT)
    {
        transform->setAnchorSize(scale);
        text->setScale(1.f);
    }
}