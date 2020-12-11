// binary_search_tree.h: This interface represents a BSTree that will hold accounts sorted by their ID number.
//
#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_
#include <iostream>
#include "account.h"
using namespace std;

class BinarySearchTree
{	
public:
	//Constructor-Destructors
	BinarySearchTree();
	~BinarySearchTree();

	//Actions
	bool isEmpty() const;
	void empty();
	void display() const;
	bool Retrieve(const int& acct_number, Account*& the_account);
	bool Insert(Account* the_account);

private:
	struct Node
	{
		Account* account = nullptr;
		Node* right = nullptr;
		Node* left = nullptr;
	};
	Node* root_;
	//Helpers
	void search_empty(Node* current);
	void search_display(Node* current) const;
};
#endif