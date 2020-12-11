#include "transaction.h"

Transaction::Transaction()
{
	transaction_type_ = ' ';
	account_id_ = -1;
	fund_id_ = -1;
	amount_ = -1;
	to_account_id_ = -1;
	to_fund_id_ = -1;
	first_name_ = "";
	last_name_ = "";
	error_ = "";
}

Transaction::Transaction(char type, string first_name, string last_name, int account_id, int fund_id, int amount, int to_account_id, int to_fund_id, string error)
{
	transaction_type_ = type;
	first_name_ = first_name;
	last_name_ = last_name;
	account_id_ = account_id;
	fund_id_ = fund_id;
	amount_ = amount;
	to_account_id_ = to_account_id;
	to_fund_id_ = to_fund_id;
	error_ = error;
}

Transaction::~Transaction()
{
}

char Transaction::get_type() const
{
	return transaction_type_;
}

string Transaction::get_first_name() const
{
	return first_name_;
}

string Transaction::get_last_name() const
{
	return last_name_;
}

int Transaction::get_account_id() const
{
	return account_id_;
}

int Transaction::get_fund_id() const
{
	return fund_id_;
}

int Transaction::get_to_account_id() const
{
	return to_account_id_;
}

int Transaction::get_to_fund_id() const
{
	return to_fund_id_;
}

int Transaction::get_amount() const
{
	return amount_;
}

void Transaction::set_error(string error)
{
	error_ = error;
}

//Format transactions when printed. Adds failed tag if transaction failed.
ostream& operator<<(ostream& out_stream, Transaction& rhs)
{
	if (rhs.transaction_type_ == 'W' || rhs.transaction_type_ == 'D')
	{
		out_stream << " " << rhs.transaction_type_ << " " << rhs.account_id_ << rhs.fund_id_ << " " << rhs.amount_;
	}
	else if (rhs.transaction_type_ == 'T')
	{
		out_stream << " " << rhs.transaction_type_ << " " << rhs.account_id_ << rhs.fund_id_ << " " << rhs.amount_ << " " << rhs.to_account_id_ << rhs.to_fund_id_;
	}

	if (!rhs.error_.empty())
	{
		out_stream << " (Failed)";
	}
	return out_stream;
}

//Reads a line of text and converts into a transaction object.
istream& operator>>(istream& in_stream, Transaction& rhs)
{
	char transaction_type = ' ';
	in_stream >> transaction_type;
	rhs.transaction_type_ = toupper(transaction_type);
	int id = -1;
	int to_id = -1;
	string first_name_ = "";
	string last_name_ = "";
	string error = "";
	if (rhs.transaction_type_ == 'O')
	{
		in_stream >> rhs.last_name_;
		in_stream >> rhs.first_name_;
		in_stream >> rhs.account_id_;
	}
	else if (rhs.transaction_type_ == 'W'|| rhs.transaction_type_ == 'D')
	{
		in_stream >> id;
		in_stream >> rhs.amount_;
		rhs.account_id_ = id / 10;
		rhs.fund_id_ = id % 10;
	}
	else if (rhs.transaction_type_ == 'T')
	{
		in_stream >> id;
		in_stream >> rhs.amount_;
		in_stream >> to_id;
		rhs.account_id_ = id / 10;
		rhs.fund_id_ = id % 10;
		rhs.to_account_id_ = to_id / 10;
		rhs.to_fund_id_ = to_id % 10;
	}
	else if (rhs.transaction_type_ == 'H')
	{
		in_stream >> id;
		if (id > 9999 && id < 100000)
		{
			rhs.account_id_ = id / 10;
			rhs.fund_id_ = id % 10;
		}
		else
		{
			rhs.account_id_ = id;
		}
	}
	else
	{
		cerr << "Invalid Transaction Type" << endl;
	}
	return in_stream;
}