#ifndef  BST_H
#define BST_H

#include "Binary Tree.h"



template <typename K, typename V >
class Entry {
public:
	typedef K Key; 
	typedef V Value; 
public: //
	Entry(const K& k = K(), const V& v = V()) 
		: key_(k), value_(v) { }

	const K& key() const { return key_; } 
	const V& value() const { return value_; } 

	void setKey(const K& k) { key_ = k; } 
	void setValue(const V& v) { value_ = v; } 
private:
	K key_; 
	V value_;
};

template<typename E >
class BST
{
public:
	typedef typename E::Key K;
	typedef typename E::Value V;
	class Iterator;
public:
	BST() :T(), n(0)
	{
		T.addRoot();
		T.expandExternal(T.root());
	}
	int size() const
	{
		return n;
	}
	bool empty() const { return size() == 0; }

	Iterator find(const K& k)
	{
		TPos v = finder(k, root());
		if (v.isInternal()) return Iterator(v);
		else return end();
	}
	Iterator insert(const K& k, const V& x)
	{
		TPos v = inserter(k, x);
		return Iterator(v);
	}
	void erase(const K& k)
	{
		TPos v = finder(k, root());
		if (v.isExternal())
			return;
		eraser(v);
	}
	void erase(const Iterator& p) { eraser(p); }

	Iterator begin()
	{
		TPos v = root();
		while (v.isInternal())
			v = v.left();
		return Iterator(v.parent());
	}

	Iterator end() { return Iterator(T.root()); }

protected:
	typedef  BinaryTree<E> BinaryTree;
	typedef typename BinaryTree::Position TPos;

	TPos root() const { return T.root().left(); }

	TPos finder(const K& k, const TPos& v)
	{
		if (v.isExternal()) return v;
		if (k < (*v).key()) return finder(k, v.left());
		else if ((*v).key() < k) return finder(k, v.right());
		else return v;
	}

	TPos inserter(const K& k, const V& x)
	{
		TPos v = finder(k, root());
		while (v.isInternal())
			v = finder(k, v.right());
		T.expandExternal(v);
		(*v).setKey(k); (*v).setValue(x);
		n++;
		return v;
	}

	TPos eraser(TPos& v)
	{
		TPos w;
		if (v.left().isExternal()) w = v.left();
		else if (v.right().isExternal()) w = v.right();
		else
		{
			w = v.right();
			do { w = w.left(); } while (w.isInternal());
			TPos u = w.parent();
			(*v).setKey((*v).key()); (*v).setValue((*v).value());
		}

		n--;
		return T.removeAboveExternal(w);
	}
	
private:
	BinaryTree T;
	int n;
public:
	class Iterator
	{
	private:
		TPos v;
	public:
		Iterator(const TPos& w = TPos()) : v{ w } {}
		const E& operator*() const { return *v; }
		bool operator==(const Iterator& p)const { return v == p.v; }
		Iterator& operator++()
		{
			TPos w = v.right();
			if (w.isInternal())
			{
				do { v = w; w = w.left(); } while (w.isInternal());
			}
			else
			{
				w = v.parent();
				while (v == w.right())
				{
					v = w; w = w.parent();
				}
				v = w;
			}
			return *this;
			
		}
		bool operator!=(const Iterator& p) const { return !(operator==(p)); }
		friend class BST;
	};
};


#endif // ! BST_H

