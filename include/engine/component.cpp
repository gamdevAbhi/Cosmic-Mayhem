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
void Engine::Component::onTransformChanged() {}
void Engine::Component::onCollisionEnter(BoxCollider* boxCollider) {}
void Engine::Component::onCollisionStay(BoxCollider* boxCollider) {}
void Engine::Component::onCollisionExit(BoxCollider* boxCollder) {}
void Engine::Component::onTriggerEnter(BoxCollider* boxCollider) {}
void Engine::Component::onTriggerStay(BoxCollider* boxCollider) {}
void Engine::Component::onTriggerExit(BoxCollider* boxCollider) {}
void Engine::Component::onDestroy() {}
Engine::Component::~Component() {}