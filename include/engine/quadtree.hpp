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
        bool contains(glm::vec2 point);
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
    friend class RendererManager;
    friend class SpriteRenderer;
    friend class Billboard;
    friend class ColliderManager;
    friend class Collider;
    friend class BoxCollider;
    friend class CircleCollider;
    friend class Button;
    friend class ButtonManager;
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
        void find(glm::vec2 point, std::vector<Node*>& query);
    friend class Node;
    friend class RendererManager;
    friend class SpriteRenderer;
    friend class Billboard;
    friend class ColliderManager;
    friend class Collider;
    friend class BoxCollider;
    friend class CircleCollider;
    friend class Button;
    friend class ButtonManager;
    };
}

#endif