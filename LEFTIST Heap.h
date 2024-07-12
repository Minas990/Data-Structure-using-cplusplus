#ifndef LEFTIST_H
#define LEFTIST_H
#include <stdexcept>
#include <stack>
class LEFTIST
{
public:
	LEFTIST() :root{ nullptr } {}
	~LEFTIST() { make_empty(root); root = nullptr; }

	bool isEmpty() const
	{
		return root == nullptr;
	}

	const int& minimum() const { return isEmpty() ? throw std::out_of_range("empty heap") : root->element; }

	void insert(int x)
	{
		root = merge(new Node(x), root);
	}

	void merge(LEFTIST& rhs)
	{
		if (this != &rhs)
		{
			root = merge(root,rhs.root);
			rhs.root = nullptr;
		}
	}

	int remove() //	always removing root by merging its right and left subtree
	{
		if (isEmpty())
			throw std::runtime_error("empty");
		Node* dummy = root;
		root = merge(root->left, root->right);
		int value = std::move(dummy->element);
		delete dummy;
		return value;

	}
	void print()
	{
		print(root);
	}

private:
	struct Node
	{
		int element;
		Node* right;
		Node* left;
		int npl;
		Node(const int& e, Node* l = nullptr, Node* r = nullptr, int np = 0)
			:element{ e }, left{ l }, right{ r }, npl{ np } {}

	};
	Node* root;

	void print(Node* root)
	{
		if (root)
		{
			std::cout << root->element << " ";
			print(root->left);
			print(root->right);
		}
	}

	Node* merge(Node* h1, Node* h2)
	{
		if (!h1)
			return h2;
		if (!h2)
			return h1;
		return h1->element < h2->element ? _merge(h1, h2) : _merge(h2, h1);
	}
	Node* _merge(Node* h1, Node* h2)
	{
		if (!h1->left)
			h1->left = h2;
		else
		{
			h1->right = merge(h1->right, h2);
			if(h1->left->npl < h1->right->npl)
				std::swap(h1->right, h1->left);
			h1->npl = h1->right->npl + 1;
		}
		return h1;
	}

	void make_empty(Node* t)
	{
		if (t != nullptr)
		{
			make_empty(t->left);
			make_empty(t->right);
			delete t;
		}
	}
public:
	class Iterator
	{
	public:
		Iterator(Node* root)
		{
			if (root)
				stk.push(root);
		}
		bool operator!=(const Iterator& other) const
		{
			return !(*this == other);
		}
		bool operator==(const Iterator& other) const
		{
			return stk.empty() == other.stk.empty();
		}

		std::pair<int,int>& operator*()
		{
			current_pair.first = stk.top()->element;
			current_pair.second = stk.top()->npl;
			return current_pair;
		}

		Iterator& operator++()
		{
			Node* node = stk.top();
			stk.pop();
			if (node->right)
				stk.push(node->right);
			if (node->left)
				stk.push(node->left);
			return *this;
		}

	private:
		std::stack<Node*> stk;
		std::pair<int, int> current_pair;

	};
	Iterator begin() const
	{
		return Iterator(root);
	}

	Iterator end() const
	{
		return Iterator(nullptr);
	}

};

#endif