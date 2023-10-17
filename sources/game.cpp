#include <engine/gameloop.hpp>

class Rotator : public Engine::Component
{
public:
    Engine::Transform* transform;
    float time;
    float actors;
protected:
    void start();
    void update();
};

void Rotator::start()
{
    transform = getActor()->getComponent<Engine::Transform>();
    time = 0.0f;
    actors = 2;
}

void Rotator::update()
{
    glm::vec3 rotation = transform->getRotation(true);
    rotation.z += 2.0f * Engine::Time::getDeltaTime();

    transform->setRotation(true, rotation);
    time += Engine::Time::getDeltaTime();

    if(time >= 5.0f)
    {
        time = 0.0f;
        std::cout << Engine::Time::getLastFPS() << std::endl;
        std::cout << actors << std::endl;
    }

    if(Engine::GameLoop::getInput()->getKeyStatus(GLFW_KEY_F) == KEY_PRESS)
    {
        Engine::Actor* actor = Engine::Actor::createActor("Test");
        actor->getComponent<Engine::Transform>()->setParent(transform);
        
        float r = (std::rand() % 100) / 100.f;
        float g = (std::rand() % 100) / 100.f;
        float b = (std::rand() % 100) / 100.f;
        float a = (50 + (std::rand() % 50)) / 100.f;

        Engine::SpriteRenderer* renderer = actor->addComponent<Engine::SpriteRenderer>();
        renderer->color = glm::vec4(r, g, b, a);
        renderer->setOrder(1);
        actors++;
    }

    if(Engine::GameLoop::getInput()->getKeyStatus(GLFW_KEY_D) == KEY_PRESS)
    {
        for(int i = 0; i < transform->getChildsSize(); i++)
        {
            transform->getChild(i)->getActor()->getComponent<Engine::SpriteRenderer>()->setDestroy();
        }
    }

    if(Engine::GameLoop::getInput()->getKeyStatus(GLFW_KEY_E) == KEY_PRESS)
    {
        for(int i = 0; i < transform->getChildsSize(); i++)
        {
            transform->getChild(i)->getActor()->addComponent<Engine::SpriteRenderer>()->setOrder(1);
        }
    }
}

int main()
{
    Engine::GameLoop::init();

    Engine::Actor* parent = Engine::Actor::createActor("Parent");
    
    parent->addComponent<Rotator>();

    Engine::SpriteRenderer* parentRenderer = parent->addComponent<Engine::SpriteRenderer>();

    parentRenderer->color = glm::vec4(1.0f, 1.0f, 1.0f, 0.5f);
    parentRenderer->setSprite(new Engine::Sprite("\\resources\\sprites\\cat.png"));
    parentRenderer->setOrder(2);

    Engine::Actor* child = Engine::Actor::createActor("Child");

    child->getComponent<Engine::Transform>()->setParent(parent->getComponent<Engine::Transform>());

    Engine::SpriteRenderer* childRenderer = child->addComponent<Engine::SpriteRenderer>();
    childRenderer->color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    childRenderer->setSprite(new Engine::Sprite("\\resources\\sprites\\rupee.png"));
    childRenderer->setOrder(0);

    Engine::Camera::getRenderCamera()->orthographicSize = 50.0f;
    Engine::Camera::getRenderCamera()->getActor()->getComponent<Engine::Transform>()->setPosition(true, glm::vec3(0.0f, 0.0f, 2.0f));

    Engine::GameLoop::begin();

    std::cout << std::endl << "Close ..." << std::endl;
    
    return 0;
}