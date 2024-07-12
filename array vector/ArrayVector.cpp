#include "ArrayVector.h"
#include <stdexcept>
using namespace std;

int max(int i, int j) 
{
	if (i > j)
	{
		return i;
	}
	else 
	{
		return j;
	}
}

ArrayVector::ArrayVector()
	:capacity{0},n{0},A{nullptr}{}

ArrayVector::ArrayVector(ArrayVector& other)
	: capacity(other.capacity), n(other.n), A(new Elem[other.capacity])
{
	for (int i = 0; i < n; ++i)
	{
		A[i] = other.A[i];
	}
}



ArrayVector::~ArrayVector()
{
	delete[] A;
}

int ArrayVector::size() const
{
	return n;
}

bool ArrayVector::empty() const
{
	return n == 0;
}

Elem& ArrayVector::operator[](int i)
{
	return A[i];
}

Elem& ArrayVector::at(int i)
{
	if (i < 0 || i >= n) 
	{
		throw out_of_range("illegal index in function at()");
	}

	return A[i];
}

void ArrayVector::erase(int i)
{
	for (int j = i; j < n - 1; ++j)
	{
		A[j] = A[j + 1];
	}
	--n;
}


void ArrayVector::reserve(int N)
{
	if (capacity >= N)
	{
		return;
	}
	Elem* B = new Elem[N];
	for (int j = 0; j < n; j++)
	{
		B[j] = A[j];
	}
	if (A != NULL)
	{
		delete[] A;
	}
	A = B;
	capacity = N;
}

void ArrayVector::insert(int i, const Elem& e)
{
	if (n >= capacity)
	{
		reserve(max(1, 2 * capacity));
	}
	for (int j = n - 1; j >= i; --j)
	{
		A[j + 1] = A[j];
	}
	A[i] = e;
	++n;
}
