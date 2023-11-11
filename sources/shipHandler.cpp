#include "shiphandler.hpp"
#include "scenemanager.hpp"

void Cosmic::ShipHandler::addScore(int value)
{
    score += value;
}

void Cosmic::ShipHandler::start()
{
    transform = getActor()->getComponent<Engine::Transform>();

    getActor()->addComponent<Engine::SpriteRenderer>()->setOrder(0);

    Engine::BoxCollider* collider = getActor()->addComponent<Engine::BoxCollider>();
    collider->setTag(Engine::ColliderManager::getTag("Space Ship"));
    collider->setBoundary(0.3f, 0.3f, 0.4f, 0.4f);

    shipComponent = getActor()->addComponent<SpaceShip>();
    health = getActor()->addComponent<Health>();
    health->setHealth(100);
    health->shouldDestroy = false;

    backBoost = Engine::Actor::createActor("Back Boost");
    frontBoost = Engine::Actor::createActor("Front Boost");
    leftBoost = Engine::Actor::createActor("Left Boost");
    rightBoost = Engine::Actor::createActor("Right Boost");
    muzzle = Engine::Actor::createActor("Muzzle");

    backBoost->getComponent<Engine::Transform>()->setParent(transform);
    backBoost->getComponent<Engine::Transform>()->setLocalPosition(glm::vec3(0.f));
    backBoost->addComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::backBoost);
    
    frontBoost->getComponent<Engine::Transform>()->setParent(transform);
    frontBoost->getComponent<Engine::Transform>()->setLocalPosition(glm::vec3(0.f));
    frontBoost->addComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::frontBoost);
    
    leftBoost->getComponent<Engine::Transform>()->setParent(transform);
    leftBoost->getComponent<Engine::Transform>()->setLocalPosition(glm::vec3(0.f));
    leftBoost->addComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::leftBoost);
    
    rightBoost->getComponent<Engine::Transform>()->setParent(transform);
    rightBoost->getComponent<Engine::Transform>()->setLocalPosition(glm::vec3(0.f));
    rightBoost->addComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::rightBoost);

    muzzle->getComponent<Engine::Transform>()->setParent(transform);
    muzzle->getComponent<Engine::Transform>()->setLocalPosition(glm::vec3(0.f));
    muzzle->addComponent<Engine::SpriteRenderer>()->setSprite(SpriteManager::muzzle);

    Engine::RectTransform* healthRect = Engine::Actor::createUIActor("Health UI")->getComponent<Engine::RectTransform>();
    healthRect->getActor()->addComponent<Engine::Billboard>()->setSprite(SpriteManager::health);
    healthRect->setAnchor(glm::vec2(-0.8f, 0.8f));
    healthRect->setAnchorSize(glm::vec2(0.08f));
    Engine::RectTransform* hTextRect = Engine::Actor::createUIActor("Health Text")->getComponent<Engine::RectTransform>();
    hTextRect->setAnchor(glm::vec2(-0.8f, 0.8f));
    healthText = hTextRect->getActor()->addComponent<Engine::Text>();
    healthText->setScale(0.8f);
    healthText->setAlignment(Engine::Text::MIDDLE);
    healthText->setText(std::to_string(health->getHealth()));

    Engine::RectTransform* scoreTextRect = Engine::Actor::createUIActor("Score Text")->getComponent<Engine::RectTransform>();
    scoreTextRect->setAnchor(glm::vec2(-0.96f, -0.9f));
    scoreText = scoreTextRect->getActor()->addComponent<Engine::Text>();
    healthText->setScale(0.8f);
    scoreText->setText(std::string("Score : ") + std::to_string(score));

    Engine::RectTransform* pauseRect = Engine::Actor::createUIActor("Pause Text")->getComponent<Engine::RectTransform>();
    pauseText = pauseRect->getActor()->addComponent<Engine::Text>();
    pauseText->setScale(1.25f);
    pauseText->setText("Pause");
    pauseText->setAlignment(Engine::Text::MIDDLE);
    pauseText->getActor()->setActive(false);
}

void Cosmic::ShipHandler::update()
{
    backBoost->setActive(false);
    frontBoost->setActive(false);
    rightBoost->setActive(false);
    leftBoost->setActive(false);
    muzzle->setActive(true);

    healthText->setText(std::to_string(health->getHealth()));
    scoreText->setText(std::string("Score : ") + std::to_string(score));

    if(health->getHealth() <= 0)
    {
        SceneManager::lastGameScore = score;
        (*callback)();
        return;
    }

    if(Engine::Input::getKeyStatus(GLFW_KEY_P) == Engine::Input::KEY_PRESS)
    {
        isPause = !isPause;

        if(isPause)
        {
            Engine::Time::setTimeScale(0.f);
            pauseText->getActor()->setActive(true);
        }
        else
        {
            Engine::Time::setTimeScale(1.f);
            pauseText->getActor()->setActive(false);
        }
    }

    if(isPause) return;

    if(Engine::Input::getKeyStatus(GLFW_KEY_A) == Engine::Input::KEY_HOLD)
    {
        shipComponent->rotateLeft();
        rightBoost->setActive(true);
    }
    else if(Engine::Input::getKeyStatus(GLFW_KEY_D) == Engine::Input::KEY_HOLD)
    {
        shipComponent->rotateRight();
        leftBoost->setActive(true);
    }

    if(Engine::Input::getKeyStatus(GLFW_KEY_LEFT_SHIFT) == Engine::Input::KEY_HOLD)
    {
        shipComponent->moveForward();
        frontBoost->setActive(true);
    }
    else if(Engine::Input::getKeyStatus(GLFW_KEY_LEFT_CONTROL) == Engine::Input::KEY_HOLD)
    {
        shipComponent->moveBackward();
        backBoost->setActive(true);
    }

    if(Engine::Input::getKeyStatus(GLFW_KEY_F) == Engine::Input::KEY_PRESS)
    {
        shipComponent->shoot();
        muzzle->setActive(true);
    }

    if(Engine::Input::getKeyStatus(GLFW_KEY_I) == Engine::Input::KEY_PRESS)
    {
        std::cout << "Last Frame Per Second(s) :" << std::endl;
        std::cout << Engine::Time::getLastFPS() << std::endl;
        std::cout << "Total Actors :" << std::endl;
        std::cout << Engine::Actor::getActorCount() << std::endl;
        std::cout << "Last Render Count :" << std::endl;
        std::cout << Engine::RendererManager::getLastRenderCount() << std::endl;
    }
}