/*

	this implementation from Mark Allen Weiss Book:
	Data Structures and Algorithm Analysis in C++ (Fourth Edition)

*/

#ifndef BINOMIALQUEUE_H
#define BINOMIALQUEUE_H
#include <stdexcept>
#include <vector>
#include <iostream>   

template<class T>
class Binomial
{
public:
	Binomial() :theTrees(1)
	{
		for (auto& r: theTrees)
			r = nullptr;
		currentSize = 0;
	}
	Binomial(const T& item)
		:theTrees(1),currentSize{1}
	{
		theTrees[0] = new Node(item, nullptr, nullptr);
	}

	bool isEmpty() const
	{
		return currentSize == 0;
	}

	const T& findMin() const
	{
		if (isEmpty())
			throw std::runtime_error("empty");
		return theTrees[findMinIndex()]->element;
	}

	void insert(const T& x)
	{
		Binomial oneItem{ x }; merge(oneItem);
	}

	void deleteMin()
	{
		T x;
		deleteMin(x);
	}

	void deleteMin(T& minItem)
	{
		if (isEmpty())
			throw std::runtime_error("empty");

		int minIndex = findMinIndex();
		minItem = theTrees[minIndex]->element;

		Node* oldRoot = theTrees[minIndex];
		Node* deletedTree = oldRoot->leftChild;
		delete oldRoot;

		Binomial deletedQueue;
		deletedQueue.theTrees.resize(minIndex);
		deletedQueue.currentSize = (1 << minIndex) - 1;

		for (int j = minIndex - 1; j >= 0; --j)
		{
			deletedQueue.theTrees[j] = deletedTree;
			deletedTree = deletedTree->nextSibling;
			deletedQueue.theTrees[j]->nextSibling = nullptr;
		}

		theTrees[minIndex] = nullptr;
		currentSize -= deletedQueue.currentSize + 1;

		merge(deletedQueue);
	}


	void merge(Binomial& rhs)
	{
		if (this == &rhs)    
			return;

		currentSize += rhs.currentSize;

		if (currentSize > capacity())
		{
			int oldNumTrees = (int) theTrees.size();
			int newNumTrees = (int) std::max(theTrees.size(), rhs.theTrees.size()) + 1;
			theTrees.resize(newNumTrees);
			for (int i = oldNumTrees; i < newNumTrees; ++i)
				theTrees[i] = nullptr;
		}

		Node* carry = nullptr;
		for (int i = 0, j = 1; j <= currentSize; ++i, j *= 2)
		{
			Node* t1 = theTrees[i];
			Node* t2 = i < rhs.theTrees.size() ? rhs.theTrees[i] : nullptr;

			int whichCase = t1 == nullptr ? 0 : 1;
			whichCase += t2 == nullptr ? 0 : 2;
			whichCase += carry == nullptr ? 0 : 4;

			switch (whichCase)
			{
			case 0: 
			case 1: 
				break;
			case 2: 
				theTrees[i] = t2;
				rhs.theTrees[i] = nullptr;
				break;
			case 4: 
				theTrees[i] = carry;
				carry = nullptr;
				break;
			case 3: 
				carry = combineTrees(t1, t2);
				theTrees[i] = rhs.theTrees[i] = nullptr;
				break;
			case 5: 
				carry = combineTrees(t1, carry);
				theTrees[i] = nullptr;
				break;
			case 6: 
				carry = combineTrees(t2, carry);
				rhs.theTrees[i] = nullptr;
				break;
			case 7:
				theTrees[i] = carry;
				carry = combineTrees(t1, t2);
				rhs.theTrees[i] = nullptr;
				break;
			}
		}

		for (auto& root : rhs.theTrees)
			root = nullptr;
		rhs.currentSize = 0;
	}


	~Binomial() {
		for (auto& root : theTrees)
			makeEmpty(root);
	}
	void print() const {
		for (int i = 0; i < theTrees.size(); ++i) {
			std::cout << "Tree " << i << ": ";
			if (theTrees[i])
				printTree(theTrees[i]);
			std::cout << std::endl;
		}
	}
	
private:
	struct Node
	{
		T element;
		Node* leftChild;
		Node* nextSibling;
		Node(const T& e, Node* lt, Node* rt)
			: element{ e }, leftChild{ lt }, nextSibling{ rt } { }
	};

	std::vector<Node*> theTrees;
	int currentSize;

	void printTree(Node* t) const {
		if (t) {
			std::cout << t->element << " ";
			printTree(t->leftChild);
			printTree(t->nextSibling);
		}
	}

	int findMinIndex()
	{
		int minIndex;
		int i = 0;
		while (!theTrees[i])
			i++;
		for (minIndex = i; i < theTrees.size(); i++)
			if (theTrees[i] && theTrees[i]->element < theTrees[minIndex]->element)
				minIndex = i;
		
		return minIndex;
	}

	int capacity() const
	{
		return (1 << theTrees.size()) - 1;
	}

	Node* combineTrees(Node* t1, Node* t2)
	{
		if (t2->element < t1->element)
			return combineTrees(t2, t1);
		t2->nextSibling = t1->leftChild;
		t1->leftChild = t2;
		return t1;
	}

	void makeEmpty(Node*& t)
	{
		if (t)
		{
			makeEmpty(t->leftChild);
			makeEmpty(t->nextSibling);
			delete t;
			t = nullptr;
		}
	}
};

#endif
