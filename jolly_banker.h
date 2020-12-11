// jolly_banker.h: This interface represents a banker.
//                 It will read, store, and execute a list of transactions.
//                 It will also store a list of accounts that were opened.
//
#ifndef JOLLY_BANKER_H_
#define JOLLY_BANKER_H_
#include <queue>
#include <fstream>
#include <iostream>
#include <string>
#include "binary_search_tree.h"
#include "transaction.h"
using namespace std;

class JollyBanker
{
public:
	//Constructor-Destructors
	JollyBanker();
	~JollyBanker();

	//Actions
	bool read_transactions(string file_name);
	void execute_transactions();
	void display();

private:
	queue<Transaction> list_;
	BinarySearchTree accounts_;
};
#endif