#include <engine/quadtree.hpp>

Engine::AABB::AABB(float _x, float _y, float _expand) :
x(_x),
y(_y),
expand(_expand)
{
}

bool Engine::AABB::contains(AABB box)
{
    if(x - expand <= box.x - box.expand && x + expand >= box.x + box.expand
    && y - expand <= box.y - box.expand && y + expand >= box.y + box.expand) return true;
    else return false;
}

bool Engine::AABB::intersects(AABB box)
{
    return !(x - expand >= box.x + box.expand || x + expand <= box.x - box.expand
    || y + expand <= box.y - box.expand || y - expand >= box.y + box.expand);
}

Engine::Children::Children(Engine::Component* _object, Engine::AABB _boundary) :
boundary(_boundary)
{
    object = _object;
    parent = nullptr;
}

void Engine::Children::update(Engine::AABB _boundary)
{
    if(parent == nullptr) return;

    boundary = _boundary;

    parent->remove(this);
    parent = nullptr;
}

void Engine::Children::destroy()
{
    if(parent == nullptr) return;

    parent->remove(this);
    parent = nullptr;
}

Engine::QuadTree::QuadTree(Engine::AABB _boundary) :
devided(false),
boundary(_boundary)
{
}

bool Engine::QuadTree::insert(Children* children)
{
    if(children == nullptr || children->object == nullptr) return false;

    if(!boundary.contains(children->boundary)) return false;

    if(childrens.size() < capacity) 
    {
        childrens.push_back(children);
        children->parent = this;
        return true;
    }
    
    if(devided == false) subdevide();

    if(northEast->insert(children)) return true;
    else if(northWest->insert(children)) return true;
    else if(southEast->insert(children)) return true;
    else if(southWest->insert(children)) return true;
    else return false;
}


bool Engine::QuadTree::remove(Children* obj)
{
    if(obj == nullptr) return false;

    for(int i = 0; i < childrens.size(); i++)
    {
        if(childrens[i] == obj) childrens.erase(childrens.begin() + i);
        return true;
    }
    
    if(devided == false) return false; 

    if(northEast->remove(obj)) return true;
    else if(northWest->remove(obj)) return true;
    else if(southEast->remove(obj)) return true;
    else if(southWest->remove(obj)) return true;
    else return false;
}

void Engine::QuadTree::subdevide()
{
    devided = true;

    AABB ne(boundary.x + boundary.expand / 2.0, boundary.y + boundary.expand / 2.0, 
    boundary.expand / 2.0);
    AABB nw(boundary.x - boundary.expand / 2.0, boundary.y + boundary.expand / 2.0, 
    boundary.expand / 2.0);
    AABB se(boundary.x + boundary.expand / 2.0, boundary.y - boundary.expand / 2.0, 
    boundary.expand / 2.0);
    AABB sw(boundary.x - boundary.expand / 2.0, boundary.y - boundary.expand / 2.0, 
    boundary.expand / 2.0);
    
    northEast = new QuadTree(ne);
    northWest = new QuadTree(nw);
    southEast = new QuadTree(se);
    southWest = new QuadTree(sw);

    std::vector<Children*> notIncluded;

    for(int i = 0; i < childrens.size(); i++)
    {
        if(northEast->insert(childrens[i])) continue;
        else if(northWest->insert(childrens[i])) continue;
        else if(southEast->insert(childrens[i])) continue;
        else if(southWest->insert(childrens[i])) continue;
        notIncluded.push_back(childrens[i]);
    }

    childrens = notIncluded;
}

Engine::QuadTree* Engine::QuadTree::expand()
{
    AABB nBoundary(boundary.x + boundary.expand, boundary.y + boundary.expand, boundary.expand * 2.0f);
    QuadTree* nTree = new QuadTree(nBoundary);
    nTree->subdevide();
    delete nTree->southWest;
    nTree->southWest = this;

    return nTree;
}

void Engine::QuadTree::find(AABB _boundary, std::vector<Engine::Children*>& query)
{
    if(boundary.intersects(_boundary) == false) return;
    
    for(int i = 0; i < childrens.size(); i++)
    {
        if(_boundary.intersects(childrens[i]->boundary)) query.push_back(childrens[i]);
    }

    if(devided == false) return;
    
    northEast->find(_boundary, query);
    northWest->find(_boundary, query);
    southEast->find(_boundary, query);
    southWest->find(_boundary, query);
}