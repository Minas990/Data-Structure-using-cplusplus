#pragma once
#include <vector>
#include <iostream>
using namespace std;


bool isPrime(int n) {
	if (n <= 1) return false;
	if (n <= 3) return true;
	if (n % 2 == 0 || n % 3 == 0) return false;
	for (int i = 5; i * i <= n; i += 6) {
		if (n % i == 0 || n % (i + 2) == 0) return false;
	}
	return true;
}

int nextPrime(int n) {
	if (n <= 1) return 2;
	int prime = n;
	bool found = false;

	while (!found) {
		prime++;
		if (isPrime(prime)) {
			found = true;
		}
	}
	return prime;
}

template <typename HashedObj>
class HashTable
{
public:
	explicit HashTable(int size = 101)
		:array(nextPrime(size)), currentSize{ 0 }
	{
		makeEmpty();
	}

	bool contains(const HashedObj& x) 
	{
		return isActive(findPos(x));
	}

	void makeEmpty()
	{
		for (HashEntry& entry : array)
			entry.info = EMPTY;
	
	}
	bool insert(const HashedObj& x)
	{
		int currentPos = findPos(x);
		if (isActive(currentPos)) 
			return false;

		array[currentPos].element = x;
		array[currentPos].info = ACTIVE;

		if (++currentSize > array.size() / 2)
			rehash();

		return true;
	}

	bool insert(HashedObj&& x)
	{
		int currentPos = findPos(x);
		if (isActive(currentPos)) 
			return false;

		array[currentPos].element = std::move(x);  
		array[currentPos].info = ACTIVE;

		if (++currentSize > array.size() / 2)
			rehash();

		return true;
	}

	bool remove(const HashedObj& x)
	{
		int currentPos = findPos(x);
		if (!isActive(currentPos))
			return false;

		array[currentPos].info = DELETED;
		return true;
	}

	enum EntryType {ACTIVE,EMPTY,DELETED};
private:
	struct HashEntry
	{
		HashedObj element;
		EntryType info;
		HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY )
			:element{ e }, info{ i } {}
	};

	vector<HashEntry> array;
	int currentSize;

	bool isActive(int currentPos) 
	{
		return array[currentPos].info == ACTIVE;
	}
	int findPos(const HashedObj& x) 
	{
		int offset = 1;
		int currentPos = static_cast<int>(myhash(x));
		while (array[currentPos].info != EMPTY
			&& array[currentPos].element != x)
		{
			currentPos += offset;
			offset += 2;
			if (currentPos >= array.size())
				currentPos -= array.size();
		}
		return currentPos;
	}
	void rehash()
	{
		vector<HashEntry> oldArray = array;
		array.resize(nextPrime(2 * oldArray.size()));
		for (auto& entry : array)
			entry.info = EMPTY;

		currentSize = 0;
		for (auto& entry : oldArray)
			if (entry.info == ACTIVE)
				insert(std::move(entry.element));
	}
	size_t myhash(const HashedObj& x)
	{
		return x % array.size();
	}
};