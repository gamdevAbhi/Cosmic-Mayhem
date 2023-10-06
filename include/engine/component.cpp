#include <engine/component.hpp>

Engine::Actor* Engine::Component::getActor()
{
    return this->actor;
}