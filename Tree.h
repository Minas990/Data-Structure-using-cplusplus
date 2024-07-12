#pragma once
#include <list>
#include <memory>
#include <iostream> 

template <typename E>
class Tree {
public:
    class Position;
    class PositionList;
private:
    struct Node {
        E element;
        std::shared_ptr<Node> parent;
        std::list<std::shared_ptr<Node>> children;
        Node(const E& e, std::shared_ptr<Node> p = nullptr) : element(e), parent(p) {}
    };
    std::shared_ptr<Node> rootNode;
    int nodeCount;
public:
    Tree() : rootNode(nullptr), nodeCount(0) {}
    int size() const { return nodeCount; }
    bool empty() const { return size() == 0; }
    Position root() const { return Position(rootNode); }
    PositionList positions() const;
    void addRoot(const E& e);
    Position addChild(const Position& p, const E& e);
    void postorderPrint(const Position& p) const;
    int diskSpace(const Position& p)
    {
        E s = *p;
        if (!p.isExternal())
        {
            PositionList ch = p.children();
            for (auto q = ch.begin(); q != ch.end(); ++q)
            {
                s += diskSpace(*q);
            }
            std::cout << "this is a child or what : " << s << std::endl;
        }
        return s;
    }

public:
    class Position {
    private:
        std::shared_ptr<Node> node;
    public:
        Position(std::shared_ptr<Node> n = nullptr) : node(n) {}
        E& operator*() { return node->element; }
        const E& operator*() const { return node->element; } // Added const version
        Position parent() const { return Position(node->parent); }
        PositionList children() const;
        bool isRoot() const { return node->parent == nullptr; }
        bool isExternal() const { return node->children.empty(); }
        friend class Tree;
    };


    class PositionList : public std::list<Position> {
    public:
        PositionList() : std::list<Position>() {}
    };
};

template <typename E>
typename Tree<E>::PositionList Tree<E>::positions() const {
    PositionList pl;
    if (!empty()) {
        std::list<std::shared_ptr<Node>> fringe;
        fringe.push_back(rootNode);
        while (!fringe.empty()) {
            std::shared_ptr<Node> v = fringe.front();
            fringe.pop_front();
            pl.push_back(Position(v));
            for (auto child : v->children) {
                fringe.push_back(child);
            }
        }
    }
    return pl;
}

template <typename E>
void Tree<E>::addRoot(const E& e) {
    if (rootNode != nullptr)
        throw std::runtime_error("Root already exists");
    rootNode = std::make_shared<Node>(e);
    nodeCount = 1;
}

template <typename E>
typename Tree<E>::Position Tree<E>::addChild(const Position& p, const E& e) {
    std::shared_ptr<Node> parent = p.node;
    if (parent == nullptr)
        throw std::runtime_error("Parent node is null");
    std::shared_ptr<Node> child = std::make_shared<Node>(e, parent);
    parent->children.push_back(child);
    nodeCount++;
    return Position(child);
}

template <typename E>
typename Tree<E>::PositionList Tree<E>::Position::children() const {
    PositionList pl;
    for (auto child : node->children) {
        pl.push_back(Position(child));
    }
    return pl;
}

template <typename E>
void Tree<E>::postorderPrint(const Position& p) const {
    PositionList ch = p.children();
    for (auto q = ch.begin(); q != ch.end(); ++q) {
        postorderPrint(*q);
        std::cout << " ";
    }
    std::cout << *p; // print element
}