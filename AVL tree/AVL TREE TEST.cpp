#include <iostream>
#include "AVL TREE.h"
int main()
{
	AVL<int> mina;
	mina.insert(0);
	mina.insert(1);
	mina.insert(2);
	mina.insert(3);
	mina.insert(4);
	mina.insert(5);
	mina.insert(6);
	mina.insert(7);
	mina.insert(8);
	mina.insert(9);
	mina.printTree();
	mina.printTreeLikeTree();

	cout << endl << endl;
	mina.remove(3);
	mina.printTreeLikeTree();
	cout << endl << endl;

	mina.remove(4);
	mina.printTreeLikeTree();
	cout << endl << endl;

	mina.remove(5);
	mina.printTreeLikeTree();
	cout << endl << endl;

	mina.remove(8);
	mina.printTreeLikeTree();
	cout << endl << endl;

	mina.remove(9);
	mina.printTreeLikeTree();
	cout << endl << endl;

	mina.remove(6);
	mina.printTreeLikeTree();
	cout << endl << endl;


	mina.remove(1);
	mina.printTreeLikeTree();
	cout << endl << endl;


	mina.remove(2);
	mina.printTreeLikeTree();
	cout << endl << endl;



	mina.remove(7);
	mina.printTreeLikeTree();
	cout << endl << endl;


	mina.remove(0);
	mina.printTreeLikeTree();
	cout << endl << endl;

	//search and range bases for loob
	mina.insert(0);
	mina.insert(1);
	mina.insert(2);
	mina.insert(200);
	for (auto i : mina)
		cout << i << " ";
	cout << endl;
	cout << (mina.search(200) != mina.end()) <<" ";
	cout << (mina.search(1) != mina.end()) << " ";
	cout << (mina.search(2) != mina.end()) << " ";
	cout << (mina.search(20) != mina.end()) << " ";
	cout << endl;

}
