#include <iostream>
#include "Binary Tree.h"
#include "BST.h"
using namespace std;




int main()
{

	BST<Entry<int, int>> mina;
	cout << mina.size() << endl;
	cout << mina.empty() << endl;
	mina.insert(10, 10);
	mina.insert(10, 100);
	mina.insert(10, 1000);
	mina.insert(10, 10000);
	mina.erase(10);

	for (auto i : mina)
		cout << i.key() << " " << i.value()<<endl;
	cout << endl << endl;
	auto it = mina.find(10);
	cout << it.operator*().key() << " " << it.operator*().value() << endl;
	mina.insert(243, 340);
	mina.insert(3, 33440);
	mina.insert(43, 40);
	mina.insert(1, 30);
	for (auto i : mina)
		cout << i.key() << " " << i.value() << endl;
	
	
}

