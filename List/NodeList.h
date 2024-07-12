#ifndef NODELIST_H
#define NODELIST_H

typedef int Elem;
class NodeList
{
private:
	struct Node
	{
		Elem elem;
		Node* prev;
		Node* next;
	};
public:
	class Iterator
	{
	public:
		Elem& operator*();
		bool operator==(const Iterator& p)const;
		bool operator!=(const Iterator& p)const;
		Iterator operator+(int);
		Iterator& operator++();
		Iterator& operator--();
		friend class NodeList;
	private:
		Node* v;
		Iterator(Node* u);
	};

public:
	NodeList();
	NodeList(const NodeList& other);
	NodeList& operator=(const NodeList& other);
	~NodeList();
	int size() const;
	bool empty() const;
	Iterator begin() const;
	Iterator end() const;
	void insertFront(const Elem&);
	void insertBack(const Elem&);
	void insert(const Iterator&, const Elem&);
	void eraseFront();
	void eraseBack();
	void erase(const Iterator&);
private:
	int n;
	Node* header;
	Node* trailer;
};


#endif