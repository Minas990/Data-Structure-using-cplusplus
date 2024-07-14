#ifndef MAP_H
#define	MAP_H

#include <list>
#include <vector>

template <typename K, typename V>
class Entry { 
public: 
	Entry(const K& k = K(), const V& v = V())
		: _key(k), _value(v) { }
	const K& key() const { return _key; } 
	const V& value() const { return _value; }
	void set_key(const K& k) { _key = k; } 
	void set_value(const V& v) { _value = v; } 
private: 
	K _key; 
	V _value; 
};



template <typename K, typename V, typename H = less<V>>
class Map
{
public:
	typedef Entry<const K, V> Entry;//dont omit const key word
	class Iterator;
public:
	Map(int capacity = 100):n(0),B(capacity){}

	int size() const { return n; }
	bool empty() const { return n == 0; }

	Iterator find(const K& k)
	{
		Iterator p = finder(k);
		if (endOfBkt(p))
			return end();
		else
			return p;
	}

	Iterator put(const K& k, const V& v)
	{
		Iterator p = finder(k);
		if (endOfBkt(p))
			return inserter(p,Entry(k,v));

		else p.ent->set_value(v);
		return p;
	}

	V operator[](const K& k)
	{
		Iterator p = finder(k);
		if (endOfBkt(p))
			return inserter(p, Entry(k)).ent->value();
		else return p.ent->value();
	}

	void erase(const K& k)
	{
		Iterator p = finder(k);
		if (endOfBkt(p))
			return;
		eraser(p);
	}
	void erase(const Iterator& p)
	{
		eraser(p);
	}

	Iterator begin()
	{
		if (empty())return end();
		Bltor bkt = B.begin();
		while (bkt->empty())++bkt;
		return Iterator(B, bkt,bkt->begin());
	}
	Iterator end()
	{
		return Iterator(B, B.end());
	}
protected:
	typedef  std::list<Entry> Bucket;
	typedef std::vector<Bucket> BktArray;

	Iterator finder(const K& k)
	{
		int i = hash(k) % B.size();
		Bltor bkt = B.begin() + i; //  its possible because its random access iterators
		Iterator p(B, bkt, bkt->begin());
		while (!endOfBkt(p) && (*p).key() != k)
			nextEntry(p);
		return p;
	}

	Iterator inserter(const Iterator& p, const Entry& e)
	{
		Eltor ins = p.bkt->insert(p.ent, e);
		n++;
		return Iterator(B, p.bkt, ins);
	}

	void eraser(const Iterator& p)
	{
		p.bkt->erase(p.ent);
		n--;
	}
	typedef  typename BktArray::iterator Bltor;//vector iterator
	typedef  typename Bucket::iterator Eltor; // list iterator
	static void nextEntry(Iterator& p) { ++p.ent; }
	static bool endOfBkt(const Iterator& p)
	{
		return p.ent == p.bkt->end();
	}

private:
	int n;
	H hash;
	BktArray B;

public:
	class Iterator
	{
	private:
		Eltor ent;
		Bltor bkt;
		const BktArray* ba;
	public:
		Iterator(const BktArray& a, const Bltor& b, const Eltor& q = Eltor())
			: ent(q), bkt(b), ba(&a) { }
		Entry& operator*() const { return *ent; };
		bool operator== (const Iterator & p) const
		{
			if (ba != p.ba || bkt != p.bkt)
				return false;
			else if (bkt == ba->end())return true;
			else return (ent == p.ent);
		}
		bool operator!=(const Iterator& p) const
		{
			return !(*this == p);
		}
		Iterator& operator++()
		{
			++ent;
			if (endOfBkt(*this))
			{
				++bkt;
				while (bkt != ba->end() && bkt->empty())
					++bkt;
				if (bkt == ba->end())return *this;
				ent = bkt->begin();
			}
			return *this;
		}
		friend class Map;
	};

};

#endif