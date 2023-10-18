#include <engine/component.hpp>

// get the actor
Engine::Actor* Engine::Component::getActor()
{
    return this->actor;
}

// compoenent will be destroyed in next update loop
void Engine::Component::setDestroy()
{
    shouldDestroy = true;
}

void Engine::Component::start() {}
void Engine::Component::update() {}
void Engine::Component::lateUpdate() {}
void Engine::Component::fixedUpdate() {}
void Engine::Component::onCollision() {}
void Engine::Component::onDestroy() {}
Engine::Component::~Component() {}