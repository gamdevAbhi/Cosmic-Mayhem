#include <engine/collidermanager.hpp>

void Engine::ColliderManager::addTag(std::string tag, bool selfRelation)
{
    if(tags.find(tag) != tags.end()) return;
    tags[tag] = tags.size();
    if(selfRelation) relations[tags[tag]].push_back(tags[tag]);
    relations[tags[tag]].push_back(tags["default"]);
    relations[tags["default"]].push_back(tags[tag]);
}

int Engine::ColliderManager::getTag(std::string tag)
{
    if(tags.find(tag) != tags.end()) return tags[tag];
    else return -1;
}

void Engine::ColliderManager::addRelation(int tag1, int tag2)
{
    if(tag1 == -1 || tag2 == -1) return;

    for(int i = 0; i < relations[tag1].size(); i++)
    {
        if(relations[tag1][i] == tag2) return;
    }
    
    relations[tag1].push_back(tag2);
    relations[tag2].push_back(tag1);
}

// call for initialization
void Engine::ColliderManager::initialize()
{
    tags["default"] = 0;
    relations[0].push_back(0);
    
    root = new QuadTree(AABB(0, 0, 100));
    BoxCollider::rootP = &root;
}

// start detecting collision
void Engine::ColliderManager::startDetection()
{
    std::vector<Node*> nodes;

    root->find(root->boundary, nodes);

    for(int i = 0; i < nodes.size(); i++)
    {
        narrowPhase(nodes[i]);
    }

    for(int i = 0; i < nodes.size(); i++)
    {
        dynamic_cast<BoxCollider*>(nodes[i]->object)->stackUpdate();
    }
}

// narrow phase collision detection
void Engine::ColliderManager::narrowPhase(Node* node)
{
    std::vector<Node*> potentialCollisions;
    node->parent->find(node->boundary, potentialCollisions);

    BoxCollider* collider = dynamic_cast<BoxCollider*>(node->object);

    for(int i = 0; i < potentialCollisions.size(); i++)
    {
        if(node == potentialCollisions[i]) continue;

        BoxCollider* collider1 = dynamic_cast<BoxCollider*>(potentialCollisions[i]->object);
        
        if(!hasRelation(collider->tag, collider1->tag)) continue;

        if(checkCollision(collider, collider1))
        {
            collisionDetected(collider, collider1);
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

// check if relation exist
bool Engine::ColliderManager::hasRelation(int tag1, int tag2)
{
    if(relations.find(tag1) == relations.end() || relations.find(tag2) == relations.end()) return false;

    for(int i = 0; i < relations[tag1].size(); i++) if(relations[tag1][i] == tag2) return true;
    
    return false;
}