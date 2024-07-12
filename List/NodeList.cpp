#include "NodeList.h"
using namespace std;
//for iterator
NodeList::Iterator::Iterator(Node* u)
{
	v = u;
}
Elem& NodeList::Iterator::operator*()
{
	return v->elem;
}
bool NodeList::Iterator::operator==(const Iterator& p) const
{
	return v == p.v;
}
bool NodeList::Iterator::operator!=(const Iterator& p) const
{
	return v != p.v;
}

NodeList::Iterator NodeList::Iterator::operator+(int k)
{
	Iterator it = *this;
	for (int i = 0; i < k; ++i) {
		++it; 
	}
	return it;
}
NodeList::Iterator& NodeList::Iterator::operator++()
{
	v = v->next;
	return *this;	
}
NodeList::Iterator& NodeList::Iterator::operator--()
{
	v = v->prev;
	return *this;
}
//for const iterator



//for the list
NodeList::NodeList()
{
	n = 0;
	header = new Node;
	trailer = new Node;
	header->next = trailer;
	trailer->prev = header;
}
NodeList::NodeList(const NodeList& other) : n(0), header(new Node), trailer(new Node) {
	header->next = trailer;
	trailer->prev = header;

	for (Iterator it = other.begin(); it != other.end(); ++it) {
		insertBack(*it);
	}
}
NodeList& NodeList::operator=(const NodeList& other)
{
	if (this != &other)
	{
		while (!empty())
		{
			eraseBack();
		}
		for (auto it : other)
		{
			insertBack(it);
		}
	}
	return *this;
}
int NodeList::size() const
{
	return n;
}
bool NodeList::empty() const
{
	return (n == 0);
}
NodeList::Iterator NodeList::begin() const
{
	return Iterator(header->next);
}
NodeList::Iterator NodeList::end() const
{
	return Iterator(trailer);
}
void NodeList::insert(const NodeList::Iterator& p, const Elem& e)
{
	Node* w = p.v;
	Node* u = w->prev;

	Node* v = new Node;
	v->elem = e;

	v->next = w;
	w->prev = v;

	v->prev = u;
	u->next = v;

	n++;
}
void NodeList::insertFront(const Elem& e)
{
	insert(begin(), e);
}
void NodeList::insertBack(const Elem& e)
{
	insert(end(), e);
}

void NodeList::erase(const Iterator& p)
{
	Node* v = p.v;
	Node* w = v->next;
	Node* u = v->prev;
	u->next = w;
	w->prev = u;
	delete v;
	n--;
}
void NodeList::eraseBack()
{
	erase(begin());
}
void NodeList::eraseFront()
{
	erase(--end());
}
NodeList::~NodeList()
{
	while (!empty())
	{
		eraseBack();
	}
}
