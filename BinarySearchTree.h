#ifndef BST_H
#define BST_H

#include <iostream>
#include <utility>
#include <stack>
using namespace std;

template<typename TT>
class BinarySearchTree
{
public:
    BinarySearchTree() : root{ nullptr } {}

    BinarySearchTree(const BinarySearchTree& rhs)
        : root{ clone(rhs.root) } {}

    BinarySearchTree(BinarySearchTree&& rhs) noexcept
        : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    ~BinarySearchTree()
    {
        makeEmpty();
    }

    const TT& findMin() const
    {
        if (isEmpty()) throw runtime_error("The tree is empty.");
        return (findMin(root))->element;
    }

    const TT& findMax() const
    {
        if (isEmpty()) throw runtime_error("The tree is empty.");
        return (findMax(root))->element;
    }

    bool contains(const TT& x) const
    {
        return contains(x, root);
    }

    bool isEmpty() const { return root == nullptr; }

    void printTree(ostream& out = cout) const
    {
        if (!isEmpty())
        {
            printTree(root, out);
        }
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }

    void insert(const TT& x)
    {
        insert(x, root);
    }

    void insert(TT&& x)
    {
        insert(move(x), root);
    }

    void remove(const TT& x)
    {
        remove(x, root);
    }

    BinarySearchTree& operator=(const BinarySearchTree& rhs)
    {
        if (this != &rhs)
        {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

    BinarySearchTree& operator=(BinarySearchTree&& rhs) noexcept
    {
        if (this != &rhs)
        {
            makeEmpty();
            root = rhs.root;
            rhs.root = nullptr;
        }
        return *this;
    }

    // Iterator for preorder traversal
    class preorder_iterator
    {
    public:
        explicit preorder_iterator(typename BinarySearchTree<TT>::BinaryNode* node) : current(node) {}

        TT& operator*() const { return current->element; }

        preorder_iterator& operator++()
        {
            if (current == nullptr && !nodeStack.empty())
            {
                current = nodeStack.top();
                nodeStack.pop();
            }
            else if (current != nullptr)
            {
                if (current->right != nullptr)
                    nodeStack.push(current->right);
                if (current->left != nullptr)
                    current = current->left;
                else if (!nodeStack.empty())
                {
                    current = nodeStack.top();
                    nodeStack.pop();
                }
                else
                {
                    current = nullptr;
                }
            }
            else
            {
                current = nullptr;
            }
            return *this;
        }

        bool operator!=(const preorder_iterator& other) const
        {
            return current != other.current;
        }

    private:
        typename BinarySearchTree<TT>::BinaryNode* current;
        std::stack<typename BinarySearchTree<TT>::BinaryNode*> nodeStack;//dont remove typename here 
    };

    // Begin and End methods 
    preorder_iterator begin() const
    {
        return preorder_iterator(root);
    }

    preorder_iterator end() const
    {
        return preorder_iterator(nullptr);
    }

private:
    struct BinaryNode
    {
        TT element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const TT& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ theElement }, left{ lt }, right{ rt } {}

        BinaryNode(TT&& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{ move(theElement) }, left{ lt }, right{ rt } {}
    };

    BinaryNode* root;

    void insert(const TT& x, BinaryNode*& t)
    {
        if (t == nullptr)
        {
            t = new BinaryNode(x, nullptr, nullptr);
        }
        else if (x < t->element)
        {
            insert(x, t->left);
        }
        else if (x > t->element)
        {
            insert(x, t->right);
        }
    }

    void insert(TT&& x, BinaryNode*& t)
    {
        if (t == nullptr)
        {
            t = new BinaryNode(move(x), nullptr, nullptr);
        }
        else if (x < t->element)
        {
            insert(move(x), t->left);
        }
        else if (x > t->element)
        {
            insert(move(x), t->right);
        }
    }

    void remove(const TT& x, BinaryNode*& t)
    {
        if (t == nullptr) return;

        if (x < t->element)
        {
            remove(x, t->left);
        }
        else if (t->element < x)
        {
            remove(x, t->right);
        }
        else if (t->left != nullptr && t->right != nullptr)
        {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            BinaryNode* oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
    }

    BinaryNode* findMin(BinaryNode* t) const
    {
        if (t == nullptr) return nullptr;

        while (t->left != nullptr)
        {
            t = t->left;
        }
        return t;
    }

    BinaryNode* findMax(BinaryNode* t) const
    {
        if (t == nullptr) return nullptr;

        while (t->right != nullptr)
        {
            t = t->right;
        }
        return t;
    }

    bool contains(const TT& x, BinaryNode* t) const
    {
        if (t == nullptr) return false;

        if (x < t->element)
        {
            return contains(x, t->left);
        }
        else if (x > t->element)
        {
            return contains(x, t->right);
        }
        else
        {
            return true;
        }
    }

    void makeEmpty(BinaryNode*& t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printTree(BinaryNode* t, ostream& out) const
    {
        if (t != nullptr)
        {
            printTree(t->left, out);
            out << t->element << " ";
            printTree(t->right, out);
        }
    }

    BinaryNode* clone(BinaryNode* t) const
    {
        if (t == nullptr) return nullptr;

        return new BinaryNode(t->element, clone(t->left), clone(t->right));
    }
};

#endif
