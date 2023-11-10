#include "countdown.hpp"

void Cosmic::Countdown::initialize(void (*function)(), Engine::Text* text, float time,
std::string message)
{
    callbackTime = time;
    callback = function;
    this->text = text;
    this->message = message;
    text->setText(message + std::to_string(callbackTime) + std::string(" s"));
}

void Cosmic::Countdown::update()
{
    if(text == nullptr) getActor()->setDestroy();

    callbackTime -= Engine::Time::getDeltaTime();
    
    if(callbackTime < 0.f) 
    {
        (*callback)();
        return;
    }

    text->setText(message + std::to_string(callbackTime) + std::string(" s"));

}