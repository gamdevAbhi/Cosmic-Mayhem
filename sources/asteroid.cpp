#include "asteroid.hpp"

// get the count of total asteroids
int Cosmic::Asteroid::getCount()
{
    return count;
}

// calculating the damage
void Cosmic::Asteroid::calculateDamage()
{
    float factor = 10.f * (transform->getScale(true).x - 0.4f);
    damage = baseDamage * factor;
}

void Cosmic::Asteroid::start()
{
    // assigning variables
    speed = minSpeed + ((std::rand() % 100) / 100.f) * (maxSpeed - minSpeed);
    asteroidTag = Engine::ColliderManager::getTag("Asteroid");
    spaceshipTag = Engine::ColliderManager::getTag("Space Ship");
    transform = getActor()->getComponent<Engine::Transform>();
    // adding box collider
    Engine::BoxCollider* collider = getActor()->addComponent<Engine::BoxCollider>();
    collider->setBoundary(0.8f, 0.8f, 0.8f, 0.8f);
    collider->setTag(asteroidTag);
    
    count++;
}

void Cosmic::Asteroid::update()
{
    // checking if asteroid is out of scope else moving the asteroid
    glm::vec3 targetPos = target->getPosition(true);
    glm::vec3 pos = transform->getPosition(true);

    if(glm::length(targetPos - pos) >= maxDistance) getActor()->setDestroy();
    else
    {
        glm::vec3 offset = direction;
        offset *= Engine::Time::getDeltaTime() * speed;
        
        transform->setPosition(true, transform->getPosition(true) + offset);
    }
}

void Cosmic::Asteroid::onCollisionEnter(Engine::BoxCollider* collider)
{
    // if collided with asteroid then change the direction
    // else if collided with spaceship then destroying itself
    // at last adding the damage to the collided actor
    if(collider->getTag() == asteroidTag)
    {
        direction = glm::vec3(direction.y, -direction.x, direction.z);
    }
    else if(collider->getTag() == spaceshipTag)
    {
        getActor()->setDestroy();
    }
    
    Health* health = collider->getActor()->getComponent<Health>();
    
    if(health == nullptr) return;

    health->addDamage(damage);
}

void Cosmic::Asteroid::onDestroy()
{
    count--;
}