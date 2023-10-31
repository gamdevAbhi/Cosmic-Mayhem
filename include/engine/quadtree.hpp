#ifndef ENGINE_QUADTREE_HPP
#define ENGINE_QUADTREE_HPP

#include <glm/glm.hpp>
#include <engine/component.hpp>
#include <iostream>
#include <vector>

namespace Engine
{
    class AABB;
    class Node;
    class QuadTree;
    
    // AABB detection class
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

    // node class for QuadTree
    class Node
    {
    protected:
        Component* object;
        AABB boundary;
        QuadTree* parent;
        Node(Component* _object, AABB _boundary);
        void update(AABB _boundary, QuadTree* root);
        void destroy();
    friend class QuadTree;
    friend class SpriteRenderer;
    friend class Collider;
    friend class BoxCollider;
    friend class CircleCollider;
    friend class ColliderManager;
    };

    // QuadTree class
    class QuadTree
    {
    protected:
        inline static int capacity = 4;
        bool devided;
        AABB boundary;
        std::vector<Node*> nodes;
        QuadTree* northEast;
        QuadTree* northWest;
        QuadTree* southEast;
        QuadTree* southWest;
        QuadTree(AABB _boundary);
        bool insert(Node* node);
        bool remove(Node* node);
        void subdevide();
        QuadTree* expand(AABB _boundary);
        void find(AABB boundary, std::vector<Node*>& query);
    friend class Node;
    friend class SpriteRenderer;
    friend class Collider;
    friend class BoxCollider;
    friend class CircleCollider;
    friend class ColliderManager;
    };
}

#endif