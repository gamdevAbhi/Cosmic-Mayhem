#include <engine/boxcollider.hpp>

// call when added in actor
void Engine::BoxCollider::start()
{
    left = 1.f;
    right = 1.f;
    up = 1.f;
    down = 1.f;
    transform = getActor()->getComponent<Transform>();
    boxColliders.push_back(this);
}

// set boundary of collider (all float should be positive)
void Engine::BoxCollider::setBoundary(float left, float right, float up, float down)
{
    this->left = left;
    this->right = right;
    this->up = up;
    this->down = down;
}

// get width of the collider (left, right)
glm::vec2 Engine::BoxCollider::getWidth()
{
    float scale_x = transform->getScale(true).x;
    return glm::vec2(left * scale_x, right * scale_x);
}

// get height of the collider (up, down)
glm::vec2 Engine::BoxCollider::getHeight()
{
    float scale_y = transform->getScale(true).y;
    return glm::vec2(up * scale_y, down * scale_y);
}

// set the trigger
void Engine::BoxCollider::setTrigger(bool isTrigger)
{
    this->isTrigger = isTrigger;
}

// call when component is removed
void Engine::BoxCollider::onDestroy()
{
    for(int i = 0; i < boxColliders.size(); i++)
    {
        if(boxColliders[i] != this) continue;
        boxColliders.erase(boxColliders.begin() + i);
        break;
    }
}

// call collider related functions
void Engine::BoxCollider::call(BoxCollider* collider, glm::vec3 axis)
{
    bool exist = false;

    if(colliders.find(collider) != colliders.end()) 
    {
        colliders[collider] = true;
        exist = true;
    }
    else colliders[collider] = true;

    if(collider->isTrigger == false && isTrigger == false)
    {
        for(int i = 0; i < getActor()->components.size(); i++)
        {
            if(exist == false) getActor()->components[i]->onCollisionEnter(collider);
            else getActor()->components[i]->onCollisionStay(collider);
        }

        transform->setPosition(true, transform->getPosition(true) + axis);
    }
    else if(isTrigger == true && collider->isTrigger == false)
    {
        for(int i = 0; i < getActor()->components.size(); i++)
        {
            if(exist == false) getActor()->components[i]->onTriggerEnter(collider);
            else getActor()->components[i]->onTriggerStay(collider);
        }
    }
}

// updating colliders stack
void Engine::BoxCollider::stackUpdate()
{
    std::vector<BoxCollider*> notFounds;

    for(auto i = colliders.begin(); i != colliders.end(); i++)
    {
        if(i->second == false) notFounds.push_back(i->first);
        i->second = false;
    }

    for(int i = 0; i < notFounds.size(); i++)
    {
        colliders.erase(notFounds[i]);

        if(notFounds[i]->isTrigger == false && isTrigger == false)
        {
            for(int j = 0; j < getActor()->components.size(); j++)
            {
                getActor()->components[j]->onCollisionExit(notFounds[i]);
            }
        }
        else if(isTrigger == true && notFounds[i]->isTrigger == false)
        {
            for(int j = 0; j < getActor()->components.size(); j++)
            {
                getActor()->components[j]->onTriggerExit(notFounds[i]);
            }
        }
    }
}

// get the vertices
std::vector<glm::vec3> Engine::BoxCollider::getVertices()
{
    glm::vec2 width = getWidth();
    glm::vec2 height = getHeight();

    glm::vec3 up_left_vertex = transform->getWorldPosAt(glm::vec3(-width.x, height.x, 0.0f));
    glm::vec3 up_right_vertex = transform->getWorldPosAt(glm::vec3(width.y, height.x, 0.0f));
    glm::vec3 down_left_vertex = transform->getWorldPosAt(glm::vec3(-width.x, -height.y, 0.0f));
    glm::vec3 down_right_vertex = transform->getWorldPosAt(glm::vec3(width.y, -height.y, 0.0f));

    std::vector<glm::vec3> vertices;
    
    vertices.push_back(up_left_vertex);
    vertices.push_back(up_right_vertex);
    vertices.push_back(down_left_vertex);
    vertices.push_back(down_right_vertex);

    return vertices;
}

// get edge axis
std::vector<glm::vec3> Engine::BoxCollider::getAxis()
{
    std::vector<glm::vec3> vertices = getVertices();

    std::vector<glm::vec3> axis;
    
    glm::vec3 x_axis = glm::vec3(-(vertices[0].y - vertices[2].y), vertices[0].x - vertices[2].x, 0.0f);
    glm::vec3 y_axis = glm::vec3(-(vertices[1].y - vertices[0].y), vertices[1].x - vertices[0].x, 0.0f);

    x_axis = glm::normalize(x_axis);
    y_axis = glm::normalize(y_axis);

    axis.push_back(x_axis);
    axis.push_back(y_axis);

    return axis;
}

// get projection
glm::vec2 Engine::BoxCollider::getProjection(glm::vec3 axis)
{
    std::vector<glm::vec3> vertices = getVertices();

    double min = glm::dot(axis, vertices[0]);
    double max = min;

    for(int i = 1; i < vertices.size(); i++)
    {
        double p = glm::dot(axis, vertices[i]);

        if(p < min) min = p;
        else if(p > max) max = p;
    }

    return glm::vec2(min, max);
}

// check if two projection is overlap or not
bool Engine::BoxCollider::isOverLap(glm::vec2 project1, glm::vec2 project2)
{
    return !(project1.y < project2.x || project2.y < project1.x);
}

double Engine::BoxCollider::getOverLap(glm::vec2 project1, glm::vec2 project2)
{
    if(project1.y > project2.x) return project1.y - project2.x;
    else return project2.y - project1.x;
}