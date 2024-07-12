#pragma once
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <algorithm> 

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


//func object
class my_string_hash
{
public:
	size_t operator()(const string& key) const // dont forget const
	{
		size_t hashVal = 0;
		for (char ch : key)
			hashVal = 37* hashVal +ch;
		return hashVal;
	}
};


template <typename HashedObj>
class HashTable
{
public:
	explicit HashTable(int size = 101)
		: theLists(size), currentSize(0) {}



	bool contains(const HashedObj& x) const
	{
		auto& whichList = theLists[myhash(x)];
		return find(begin(whichList), end(whichList), x) != end(whichList);
	}
	void makeEmpty()
	{
		for (auto& thisList : theLists)
		{
			thisList.clear();
		}
	}
	bool insert(const HashedObj& x)
	{
		auto& whichList = theLists[myhash(x)];
		if (find(begin(whichList), end(whichList), x) != end(whichList))
			return false;
		whichList.push_back(x);

		if (++currentSize > theLists.size())
			rehash();

		return true;
	}
	bool insert(const HashedObj&& x) // for r values 
	{
		auto& whichList = theLists[myhash(x)];
		if (find(begin(whichList), end(whichList), x) != end(whichList))
			return false;
		whichList.push_back(x);

		if (++currentSize > theLists.size())
			rehash();


		return true;
	}
	bool remove(const HashedObj& x)
	{
		auto& whichList = theLists[myhash(x)];
		auto itr = find(begin(whichList), end(whichList), x);

		if (itr == end(whichList))
			return false;

		whichList.erase(itr);
		--currentSize;
		return true;

	}


private:
	vector<list<HashedObj>> theLists;
	int currentSize;
	void rehash()
	{
		vector<list<HashedObj>> oldList = theLists;
		theLists.resize(nextPrime(2 * oldList.size()));
		for (auto& thisList : theLists)
			thisList.clear();

		currentSize = 0;
		for (auto thisList : oldList)
			for (auto& x; thisList)
				insert(std::move(x));
	}
	size_t myhash(const HashedObj& x) const
	{
		
		static my_string_hash hf;
		return hf(x) % theLists.size();
		
	}

};


