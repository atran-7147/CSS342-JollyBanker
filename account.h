// account.h: This interface represents an account for a user at a bank.
//
#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#include <vector>
#include <string>
#include <iostream>
#include "fund.h"
#include "transaction.h"
using namespace std;

class Account
{
	friend ostream& operator<<(ostream& out_stream, Account& rhs);
public:
	//Constructor-Destructors
	Account();
	Account(string first_name, string last_name, int id);
	~Account();

	//Getter-Setters
	string get_first_name() const;
	string get_last_name() const;
	int get_id() const;

	//Actions
	void deposit_funds(int fund, int amount, Transaction trns);
	bool withdraw_funds(int fund, int amount, Transaction trns);
	bool withdraw_linked_funds(int fund1, int fund2, int amount, Transaction trns);
	void display_account_history();
	void display_fund_history(int fund);

private:
	string first_name_;
	string last_name_;
	int account_id_;
	vector<Fund> funds_;
};
#endif