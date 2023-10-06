#include <engine/actor.hpp>

using namespace Engine;

int main()
{
    Actor* actor = Actor::createActor("Hello");
    Transform* transform = actor->getComponent<Transform>();
    
    return 0;
}