#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H
#include <vector>
#include <iostream>
#include <utility>
using namespace std;

template <class T>
class BinaryHeap
{
public:
	explicit BinaryHeap(int capacity = 100) :currentSize{ 0 }, array(capacity + 1)
	{
		cout << "CONSTRUCTOR ON" << endl;
	}
	explicit BinaryHeap(const vector<T>& other)
		:currentSize{ (int)other.size() }, array(other.size() + 1)
	{
		for (int i = 0; i < other.size(); i++)
			array[i + 1] = other[i];
		build();
	}

	bool isEmpty() const { return currentSize == 0; }
	
	const T& findMin() const 
	{
		if (isEmpty())
			throw out_of_range("Heap is empty");
		return array[1];
	}

	void insert(T x)
	{
		if (currentSize == array.size() - 1)
			array.resize(array.size() * 2);

		int hole = ++currentSize;
		for (; hole > 1 && x < array[hole / 2]; hole /= 2)
			array[hole] = std::move(array[hole / 2]);
		array[hole] = std::move(x);
	}


	T deleteMin()
	{
		if(isEmpty())
			throw out_of_range("empty heap");

		T maintain = std::move(array[1]);

		array[1] = std::move(array[currentSize--]);

		percolateDown(1); 

		return maintain;
	}

	void makeEmpty()
	{
		currentSize = 0;
	}

	int getSize() const { return currentSize; }

private:
	int currentSize;
	vector<T> array;
	void build()
	{
		for (int i = currentSize / 2; i > 0; i--)
			percolateDown(i);
	}
	void percolateDown(int hole)
	{
		int child;
		T tmp = std::move(array[hole]);

		for (; hole * 2 <= currentSize; hole = child)
		{
			child = hole * 2;
			if (child != currentSize && array[child + 1] < array[child])
				++child;
			if (array[child] < tmp)
				array[hole] = std::move(array[child]);
			else
				break;
		}
		array[hole] = std::move(tmp);
	}
};
#endif
