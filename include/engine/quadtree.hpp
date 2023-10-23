#ifndef ENGINE_QUADTREE_HPP
#define ENGINE_QUADTREE_HPP

#include <glm/glm.hpp>
#include <engine/component.hpp>
#include <iostream>
#include <vector>

namespace Engine
{
    class AABB;
    class Children;
    class QuadTree;
    
    class AABB
    {
    public:
        float x;
        float y;
        float expand;
        AABB(float _x, float _y, float _expand);
        bool contains(AABB box);
        bool intersects(AABB box);
    };

    class Children
    {
    protected:
        Component* object;
        AABB boundary;
        QuadTree* parent;
        Children(Component* _object, AABB _boundary);
        void update(AABB _boundary);
        void destroy();
    friend class QuadTree;
    friend class SpriteRenderer;
    friend class ColliderManager;
    };

    class QuadTree
    {
    protected:
        inline static int capacity = 4;
        bool devided;
        AABB boundary;
        std::vector<Children*> childrens;
        QuadTree* northEast;
        QuadTree* northWest;
        QuadTree* southEast;
        QuadTree* southWest;
        QuadTree(AABB _boundary);
        bool insert(Children* children);
        bool remove(Children* children);
        void subdevide();
        QuadTree* expand();
        void find(AABB boundary, std::vector<Children*>& query);
    friend class Children;
    friend class SpriteRenderer;
    friend class ColliderManager;
    };
}

#endif