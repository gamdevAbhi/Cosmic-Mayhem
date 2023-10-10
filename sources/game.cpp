#include <engine/gameloop.hpp>

class Mover : public Engine::Component
{
protected:
    void update();
};

void Mover::update()
{
    Engine::Transform* transform = getActor()->getComponent<Engine::Transform>();
    transform->scale.x = 5.0f;
    transform->scale.y = 5.0f;
    transform->rotation.z += Engine::Time::getDeltaTime() * 2.5f;
}

int main()
{
    Engine::GameLoop::init();

    Engine::Actor* actor = Engine::Actor::createActor("test");
    actor->addComponent<Mover>();
    actor->addComponent<Engine::SpriteRenderer>();

    Engine::Transform* camTrans = Engine::Camera::getRenderCamera()->getActor()->getComponent<Engine::Transform>();
    camTrans->position.z = 2.0f;

    Engine::GameLoop::begin();
    return 0;
}