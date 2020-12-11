// fund.h: This interface represents 1 of 10 funds linked to an account.
//
#ifndef FUND_H_
#define FUND_H_
#include <vector>
#include <string>
#include "transaction.h"

class Fund
{
	friend ostream& operator<<(ostream& out_stream, Fund& rhs);

public:
	//Constructor-Destructors
	Fund();
	~Fund();

	//Getter-Setters
	string get_name() const;
	void set_name(string name);
	int get_balance() const;

	//Actions
	bool add_funds(int amount);
	bool remove_funds(int amount);
	bool log_history(Transaction trns);
	void display_fund_history();

private:
	string name_;
	int balance_;
	vector<Transaction> history_;
};
#endif