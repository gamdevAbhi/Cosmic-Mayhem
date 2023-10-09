#include <engine/component.hpp>

Engine::Actor* Engine::Component::getActor()
{
    return this->actor;
}

void Engine::Component::start() {}
void Engine::Component::update() {}
void Engine::Component::lateUpdate() {}
void Engine::Component::fixedUpdate() {}

Engine::Component::~Component() {}