#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <list>

template<typename E>
class BinaryTree
{
public:
	class Position;
	class PositionList;
protected:
	struct Node
	{
		E elt;
		Node* par;
		Node* left;
		Node* right;
		Node() :elt(), par(NULL), left(NULL), right(NULL) {}
	};

public:
	class Position
	{
	private:
		Node* v;
	public:
		Position(Node* _v = NULL) :v{ _v } {}
		E& operator*() { return v->elt; }
		const E& operator*() const{ return v->elt; }
		Position left() const { return Position(v->left); }
		Position right() const { return Position(v->right); }
		Position parent() const { return Position(v->par); }
		bool isRoot() const { return v->par == NULL; }
		bool isExternal() const { return v->left == NULL && v->right == NULL; }
		bool isInternal() const { return !(isExternal()); }
		bool operator!=(const Position& other) const{ return this->v != other.v; }
		bool operator==(const Position& other) const { return this->v == other.v; }
		Node* operator->() const { return v; }  
		friend class BinaryTree;
	};
public:
	BinaryTree() : _root{ NULL }, n(0) {}
	int size() const { return n; }
	bool empty() const { return size() == 0; }
	Position root() const { return Position(_root); }
	void addRoot() { _root = new Node; n = 1; }
	PositionList positions()
	{
		PositionList pl;
		preorder(_root, pl);
		return  pl;
	}
	void expandExternal(const Position& p)
	{
		Node* v = p.v;
		v->left = new Node;
		v->left->par = v;
		v->right = new Node;
		v->right->par = v;
		n += 2;
	}

	Position removeAboveExternal(const Position& p)
	{
		Node* w = p.v;
		Node* v = w->par;
		Node* sib = (w == v->right ? v->left : v->right);
		if (_root == v)
		{
			_root = sib;
			sib->par = NULL;
		}
		else
		{
			Node* gpar = v->par;
			if (v == gpar->left)
			{
				gpar->left = sib;
			}
			else
			{
				gpar->right = sib;
			}
			sib->par = gpar;
		}
		delete w; delete v;
		n -= 2;
		return Position(sib);
	}

private:
	Node* _root;
	int n;
protected:
	void preorder(Node* v, PositionList& pl)
	{
		pl.push_back(Position(v));
		if (v->left != NULL)
		{
			preorder(v->left, pl);
		}
		if (v->right != NULL)
		{
			preorder(v->right, pl);
		}
	}
public:
	class PositionList : public std::list<Position>
	{
	public:
		PositionList() : std::list<Position>() {}
	};
};
#endif

