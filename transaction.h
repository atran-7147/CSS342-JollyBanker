// transaction.h: This interface represents a banking transaction.
//

#ifndef TRANSACTION_H_
#define TRANSACTION_H_
#include <iostream>
#include <string>
using namespace std;

class Transaction
{
	//iostream Overloads
	friend ostream& operator<<(ostream& out_stream, Transaction& rhs);
	friend istream& operator>>(istream& in_stream, Transaction& rhs);

public:
	//Constructor-Destructors
	Transaction();
	Transaction(char type, string first_name, string last_name, int account_id, int fund_id, int amount, int to_account_id, int to_fund_id, string error);
	~Transaction();

	//Getter-Setters
	char get_type() const;
	string get_first_name() const;
	string get_last_name() const;
	int get_account_id() const;
	int get_fund_id() const;
	int get_to_account_id() const;
	int get_to_fund_id() const;
	int get_amount() const;
	void set_error(string error);

private:
	char transaction_type_;
	string first_name_;
	string last_name_;
	int account_id_;
	int fund_id_;
	int to_account_id_;
	int to_fund_id_;
	int amount_;
	string error_;
};
#endif