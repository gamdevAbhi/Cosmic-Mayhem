#include <engine/gameloop.hpp>

class Mover : public Engine::Component
{
protected:
    void update();
};

void Mover::update()
{
    Engine::Transform* transform = getActor()->getComponent<Engine::Transform>();
    transform->position.x += Engine::Time::getDeltaTime() * 1.0f;
    Engine::SpriteRenderer* renderer = getActor()->getComponent<Engine::SpriteRenderer>();
    renderer->color.r = (float)(rand() % 100) / 100.0f;
    renderer->color.g = (float)(rand() % 100) / 100.0f;
    renderer->color.b = (float)(rand() % 100) / 100.0f;
}

int main()
{
    Engine::GameLoop::init();

    Engine::Actor* actor = Engine::Actor::createActor("test");
    actor->addComponent<Mover>();
    actor->addComponent<Engine::SpriteRenderer>();

    Engine::GameLoop::begin();
    return 0;
}