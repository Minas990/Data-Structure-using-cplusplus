#pragma once
#include "map.h"

template <typename K, typename V, typename H>
class Dictionary : public Map<K, V, H>
{
public:
	typedef typename Map<K, V, H>::Iterator Iterator;
	typedef typename Map<K, V, H>::Entry Entry;
	class Range
	{
	private:
		Iterator _begin;
		Iterator _end;
	public:
		Range(const Iterator& b, const Iterator& e)
			: _begin(b), _end(e) { }
		Iterator& begin() { return _begin; }
		Iterator& end() { return _end; }
	};

public: 
	Dictionary(int capacity = 100) :Map<K, V, H>(capacity) {}

	Range findAll(const K& k) // find all entries with key
	{
		Iterator b = this->finder(k);
		if (this->endOfBkt(b)) // If the iterator is at the end of the bucket, return an empty range
			return Range(b, b);

		Iterator p = b;
		++p; // Move to the next element
		while (p != this->end() && !this->endOfBkt(p) && (*p).key() == (*b).key())
			++p;

		return Range(b, p);
	}

	Iterator insert(const K& k, const V& v)
	{
		Iterator p = this->finder(k);
		Iterator q = this->inserter(p, Entry(k, v));
		return q;
	}
};

