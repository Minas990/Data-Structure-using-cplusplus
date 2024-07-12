#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <stack>
#include <queue>
using namespace std;
template<typename T>
class AVL
{
private:
	struct TreeNode 
	{
		int height;
		T value;
		TreeNode* right;
		TreeNode* left;
		TreeNode(T value = T(), TreeNode* left = nullptr, TreeNode* right=nullptr, int height = 0)
			:value{ value }, left{ left }, right{ right }, height{ height } {}
	};
	TreeNode* root;
public:

	AVL() :root{ nullptr }
	{
		cout << "constructor is on" << endl;
	}

	~AVL()
	{
		cout << "destructor is on" << endl;
		clear(root);
		root = nullptr;
	}
	
	void clear(TreeNode*& root)
	{
		if (root)
		{
			clear(root->left);
			clear(root->right);
			delete root;
			root = nullptr;
		}
	}

	void insert(T val)
	{
		insert(root, val);
	}

	void printTree()
	{
		preorder(root);
	}

	void printTreeLikeTree()
	{
		printTreeLikeTree(root,0);
	}

	void remove(T val)
	{
		remove(root, val);
	}

	
public:

	class Iterator
	{
	public:
		Iterator(TreeNode*root)
		{
			//cout << "ITERATOR CONSTRUCTOR HAS RUN" << endl;
			pushAllLeft(root);
		}

		T operator*() const 
		{
			if (!mina.empty())
				return mina.top()->value;
			throw out_of_range("Iterator dereferenced past end");
		}
		Iterator& operator++() 
		{
			if (!mina.empty())
			{
				TreeNode* node = mina.top();
				mina.pop();
				pushAllLeft(node->right);
			}
			return *this;
		}
		Iterator operator++(int ) 
		{
			auto minaana = *this;
			if (!mina.empty())
			{
				TreeNode* node = mina.top();
				mina.pop();
				pushAllLeft(node->right);
			}
			return minaana;
		}

		bool operator==(const Iterator& other) const
		{
			if (mina.empty() && other.mina.empty())
				return true;
			if (mina.empty() || other.mina.empty())
				return false;
			return mina.top() == other.mina.top();
		}

		bool operator!=(const Iterator& other) const
		{
			return !(*this == other);
		}
	private:
		stack<TreeNode*> mina;
		void pushAllLeft(TreeNode* root)
		{
			while(root)
			{
				mina.push(root);
				root = root->left;
			}
		}
	};
	Iterator begin()
	{
		return Iterator(root);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}

public:

	Iterator search(int x)
	{
		return search(root,x);
	}

	TreeNode* findMin(TreeNode* root)
	{
		while (root && root->left)
			root = root->left;
		return root;
	}
	TreeNode* findMax(TreeNode* root)
	{
		while (root && root->right)
			root = root->right;
		return root;
	}

private:
	Iterator search(TreeNode* root, int x)
	{
		if (!root)
			return Iterator(nullptr);
		if (root->value == x)
			return Iterator(root);
		else if (root->value > x)
			return search(root->left, x);
		else return search(root->right, x);
	}
	void remove(TreeNode*& root, T val)
	{
		if (!root )
			return;   

		if (val < root->value)
			remove( root->left, val);

		else if (root->value < val)
			remove( root->right,val );

		else if (root->right && root->left)
		{
			root->value = findMin(root->right)->value;
				remove(root->right, root->value);
		}
		else
		{
			TreeNode* oldNode = root;
			root = (root->left) ? root->left : root->right;
			delete oldNode;
		}
		balance(root);
	}

	void preorder(TreeNode* mina)
	{
		if (mina)
		{
			cout << left << "VALUE IS: " << setw(4) << mina->value
				<< "HEIGHT IS: " << setw(4) << mina->height << endl;
			preorder(mina->left);
			preorder(mina->right);
		}
	}
	void insert(TreeNode*& root, T val)
	{
		if (!root)
			root = new TreeNode(val);
		else if (root->value > val)
			insert(root->left, val);
		else if (root->value < val)
			insert(root->right, val);

		balance(root);
		root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

	}

	void balance(TreeNode*& root)
	{
		if (!root) return;

		// Left subtree is taller
		if (getHeight(root->left) - getHeight(root->right) > 1) {
			if (getHeight(root->left->left) >= getHeight(root->left->right))
				RightRotation(root);
			else
				LeftRightRotation(root);
		}
		// Right subtree is taller
		else if (getHeight(root->right) - getHeight(root->left) > 1) {
			if (getHeight(root->right->right) >= getHeight(root->right->left))
				LeftRotation(root);
			else
				RightLeftRotation(root);
		}
		root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	}

	void RightRotation(TreeNode*& k2) // we can call it rotate with left child 
	{
		TreeNode* k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
		k1->height = max(getHeight(k1->left), getHeight(k2)) + 1;
		k2 = k1;
		cout << "RIGHT ROTATION HAS DONE" << endl;
	}

	void LeftRotation(TreeNode*& k2)//we can call it rotate with right child
	{
		TreeNode* k1 = k2->right;
		k2->right = k1->left;
		k1->left = k2;
		k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
		k1->height = max(getHeight(k1->right), getHeight(k2)) + 1;
		k2 = k1;
		cout << "LEFT ROTATION HAS DONE" << endl;
	}

	void LeftRightRotation(TreeNode*& k2) //LR Rotation 
	{
		LeftRotation(k2->left);
		RightRotation(k2);
		cout << "LEFT RIGHT ROTATION HAS DONE" << endl;
	}
	void RightLeftRotation(TreeNode*& k2) //RL Rotation 
	{
		RightRotation(k2->right);
		LeftRotation(k2);
		cout << "RIGHT LEFT ROTATION HAS DONE" << endl;
	}

	int getHeight(TreeNode* root)
	{
		return root ? root->height : -1;
	}

	void printTreeLikeTree(TreeNode* root, int indent) const
	{
		if (root == nullptr)
			return;

		const int spaces_per_level = 5;
		if (root->right)
			printTreeLikeTree(root->right, indent + spaces_per_level);

		for (int i = 0; i < indent; i++)
			cout << " ";
		cout << root->value << endl;
		/*cout << setw(indent) << root->value << endl;*/

		if (root->left)
			printTreeLikeTree(root->left, indent + spaces_per_level);
	}


};
#endif