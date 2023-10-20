#include <engine/collidermanager.hpp>

// start detecting collision
void Engine::ColliderManager::startDetection()
{
    broadPhase();
    narrowPhase();

    for(int i = 0; i < BoxCollider::boxColliders.size(); i++)
    {
        BoxCollider::boxColliders[i]->stackUpdate();
    }
}

// broad phase collision detection
void Engine::ColliderManager::broadPhase()
{

}

// narrow phase collision detection
void Engine::ColliderManager::narrowPhase()
{
    for(int i = 0; i < BoxCollider::boxColliders.size(); i++)
    {        
        for(int j = i + 1; j < BoxCollider::boxColliders.size(); j++)
        {
            if(checkCollision(BoxCollider::boxColliders[i], BoxCollider::boxColliders[j]))
            {
                collisionDetected(BoxCollider::boxColliders[i], BoxCollider::boxColliders[j]);
            }
        }
    }
}

// collision detected
void Engine::ColliderManager::collisionDetected(BoxCollider* collider1, BoxCollider* collider2)
{
    double length1 = glm::length(collider1->transform->getPosition(true)); 
    double length2 = glm::length(collider2->transform->getPosition(true));

    BoxCollider* close = (length1 < length2)? collider1 : collider2;
    BoxCollider* distant = (close == collider1)? collider2 : collider1;

    glm::vec3 offset = currentAxis;
    offset *= currentOverlap;

    glm::vec3 distance = close->transform->getPosition(true) - distant->transform->getPosition(true);
    // glm::vec3 direction = glm::normalize(distance);

    float closeDot = glm::dot(distance, offset);
    float distantDot = glm::dot(-distance, offset);

    if(closeDot > distantDot)
    {
        close->call(distant, offset);
        distant->call(close, -offset);
    }
    else
    {
        close->call(distant, -offset);
        distant->call(close, offset);
    }
}

// checking collision between two box collider
bool Engine::ColliderManager::checkCollision(BoxCollider* collider1, BoxCollider* collider2)
{
    glm::vec3 axis;
    double overlap = DBL_MAX;

    std::vector<glm::vec3> axises1 = collider1->getAxis();
    std::vector<glm::vec3> axises2 = collider2->getAxis();

    for(int i = 0; i < axises1.size(); i++)
    {
        glm::vec2 projection1 = collider1->getProjection(axises1[i]);
        glm::vec2 projection2 = collider2->getProjection(axises1[i]);

        if(BoxCollider::isOverLap(projection1, projection2) == false) return false;

        double current = BoxCollider::getOverLap(projection1, projection2);
        
        if(current < overlap)
        {
            axis = axises1[i];
            overlap = current;
        }
    }

    for(int i = 0; i < axises2.size(); i++)
    {
        glm::vec2 projection1 = collider1->getProjection(axises2[i]);
        glm::vec2 projection2 = collider2->getProjection(axises2[i]);

        if(BoxCollider::isOverLap(projection1, projection2) == false) return false;

        double current = BoxCollider::getOverLap(projection1, projection2);
        
        if(current < overlap)
        {
            axis = axises2[i];
            overlap = current;
        }
    }

    currentAxis = axis;
    currentOverlap = overlap;

    return true;
}