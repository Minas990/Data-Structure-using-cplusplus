#ifndef ARRAYVECTOR_H
#define ARRAYVECTOR_H
typedef int Elem;
class ArrayVector
{
public:
	class Iterator
	{
	public:
		Elem& operator*()
		{
			return *v;
		}
		int operator-(const Iterator& p) const { return (v - p.v); }
		bool operator==(const Iterator& p) const { return v == p.v; }
		bool operator!=(const Iterator& p) const { return v != p.v; }
		Iterator& operator++() { ++v; return *this; }
		Iterator& operator--() { --v; return *this; }
		friend ArrayVector;
	private:
		Iterator(Elem* u) :v{u} {}
		Elem* v;
	};
public:
	ArrayVector();
	ArrayVector(ArrayVector&);
	~ArrayVector();
	int size() const;
	bool empty() const;
	Elem& operator[](int i);
	Elem& at(int i);
	void erase(int i);
	void insert(int i, const Elem& e);
	void reserve(int N);
	Iterator begin() const
	{
		return Iterator(A);
	}
	Iterator end() const
	{
		return Iterator(&A[n]);
	}
private:
	int capacity;
	int n;
	Elem* A;
};

#endif