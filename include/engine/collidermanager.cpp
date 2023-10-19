#include <engine/collidermanager.hpp>

// start detecting collision
void Engine::ColliderManager::startDetection()
{
    for(int i = 0; i < BoxCollider::boxColliders.size(); i++)
    {
        for(int j = i + 1; j < BoxCollider::boxColliders.size(); j++)
        {
            if(checkCollision(BoxCollider::boxColliders[i], BoxCollider::boxColliders[j]))
            {
                BoxCollider::boxColliders[i]->call(BoxCollider::boxColliders[j]);
                BoxCollider::boxColliders[j]->call(BoxCollider::boxColliders[i]);
            }
        }
    }
}

// checking collision between two box collider
bool Engine::ColliderManager::checkCollision(BoxCollider* collider1, BoxCollider* collider2)
{
    std::vector<glm::vec3> axises1 = collider1->getAxis();
    std::vector<glm::vec3> axises2 = collider2->getAxis();

    for(int i = 0; i < axises1.size(); i++)
    {
        glm::vec2 projection1 = collider1->getProjection(axises1[i]);
        glm::vec2 projection2 = collider2->getProjection(axises1[i]);

        if(BoxCollider::isOverLap(projection1, projection2) == false) return false;
        if(BoxCollider::isOverLap(projection2, projection1) == false) return false;
    }

    for(int i = 0; i < axises2.size(); i++)
    {
        glm::vec2 projection1 = collider1->getProjection(axises2[i]);
        glm::vec2 projection2 = collider2->getProjection(axises2[i]);

        if(BoxCollider::isOverLap(projection1, projection2) == false) return false;
        if(BoxCollider::isOverLap(projection2, projection1) == false) return false;
    }

    return true;
}