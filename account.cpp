#include "account.h"

Account::Account()
{
	first_name_ = "Unnamed Account";
	last_name_ = "";
	account_id_ = -1;
	funds_.resize(10);
	funds_[0].set_name("Money Market");
	funds_[1].set_name("Prime Money Market");
	funds_[2].set_name("Long-Term Bond");
	funds_[3].set_name("Short-Term Bond");
	funds_[4].set_name("500 Index Fund");
	funds_[5].set_name("Capital Value Fund");
	funds_[6].set_name("Growth Equity Fund");
	funds_[7].set_name("Growth Index Fund");
	funds_[8].set_name("Value Fund");
	funds_[9].set_name("Value Stock Index");
}

Account::Account(string first_name, string last_name, int id)
{
	first_name_ = first_name;
	last_name_ = last_name;
	account_id_ = id;
	funds_.resize(10);
	funds_[0].set_name("Money Market");
	funds_[1].set_name("Prime Money Market");
	funds_[2].set_name("Long-Term Bond");
	funds_[3].set_name("Short-Term Bond");
	funds_[4].set_name("500 Index Fund");
	funds_[5].set_name("Capital Value Fund");
	funds_[6].set_name("Growth Equity Fund");
	funds_[7].set_name("Growth Index Fund");
	funds_[8].set_name("Value Fund");
	funds_[9].set_name("Value Stock Index");
}

Account::~Account()
{
}

string Account::get_first_name() const
{
	return first_name_;
}

string Account::get_last_name() const
{
	return last_name_;
}

int Account::get_id() const
{
	return account_id_;
}

//Deposits funds and records the transaction.
//Prints to cerr if minimum deposit is not met.
void Account::deposit_funds(int fund, int amount, Transaction trns)
{
	if (amount < 0)
	{
		cerr << "ERROR: Deposit to " << first_name_ << " " << last_name_ << "'s " << funds_[fund].get_name() << " must be positive. $" << amount << " not deposited." << endl;
		trns.set_error("Deposit");
	    funds_[fund].log_history(trns);
	}
	else
	{
		funds_[fund].add_funds(amount);
		funds_[fund].log_history(trns);
	}
}

//Withdraws funds and records the transaction.
//Prints to cerr if minimum withdrawl is not met.
bool Account::withdraw_funds(int fund, int amount, Transaction trns)
{
	if (amount < 0)
	{
		cerr << "ERROR: Withdrawl from " << first_name_ << " " << last_name_ << "'s " << funds_[fund].get_name() << " must be positive. $" << amount << " not withdrawn." << endl;
		trns.set_error("Withdraw");
		funds_[fund].log_history(trns);
		return false;
	}
	if (funds_[fund].get_balance() >= amount)
	{
		funds_[fund].remove_funds(amount);
		funds_[fund].log_history(trns);
		return true;
	}
	else if (fund <= 1 && funds_[0].get_balance() + funds_[1].get_balance() >= amount)
	{
		if (fund == 0)
		{
			return withdraw_linked_funds(0, 1, amount, trns);
		}
		else if (fund == 1)
		{
			return withdraw_linked_funds(1, 0, amount, trns);
		}
	}
	else if (fund <= 3 && funds_[2].get_balance() + funds_[3].get_balance() >= amount)
	{
		if (fund == 2)
		{
			return withdraw_linked_funds(2, 3, amount, trns);
		}
		else if (fund == 3)
		{
			return withdraw_linked_funds(3, 2, amount, trns);
		}
	}
	else
	{
		{
			cerr << "ERROR: Not enough funds to withdraw $" << amount << " from " << first_name_ << " " << last_name_ << " " << funds_[fund].get_name() << "." << endl;
			trns.set_error("Withdraw");
			funds_[fund].log_history(trns);
			return false;
		}
	}
	return false;
}

//Withdraws all funds from primary linked fund and necessary funds to cover full requested withdrawl from secondary linked fund.
//Logs transactions as withdrawls.
bool Account::withdraw_linked_funds(int fund1, int fund2, int amount, Transaction trns)
{
	if (trns.get_type() == 'T' && trns.get_to_fund_id() == fund2) {
		cerr << "ERROR: Not enough funds to withdraw $" << amount << " from " << first_name_ << " " << last_name_ << " " << funds_[fund1].get_name() << "." << endl;
		trns.set_error("Linked Transfer");
		funds_[fund1].log_history(trns);
		return false;
	}
	int remainder = amount - funds_[fund1].get_balance();
	Transaction linked_withdraw_fund1('T', "", "", account_id_, fund2, remainder, account_id_, fund1, "");
	funds_[fund1].remove_funds(funds_[fund1].get_balance());
	funds_[fund1].log_history(linked_withdraw_fund1);
	funds_[fund2].log_history(linked_withdraw_fund1);
	funds_[fund2].remove_funds(remainder);
	funds_[fund1].log_history(trns);
	return true;
}

//Displays history of each fund in an account
void Account::display_account_history()
{
	cout << "Transaction History for " << first_name_ << " " << last_name_ << " " << "By Fund:" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << funds_[i] << endl;
		funds_[i].display_fund_history();
	}
}

//Displays the history of a single fund
void Account::display_fund_history(int fund)
{
	cout << "Transaction History for " << first_name_ << " " << last_name_ << " " << funds_[fund].get_name() << ": $" << funds_[fund].get_balance() << endl;
	funds_[fund].display_fund_history();
}

//Formats the output to display account holder's name, ID, and balances for each fund.
ostream& operator<<(ostream& out_stream, Account& rhs)
{
	out_stream << rhs.first_name_ << " " << rhs.last_name_ << " - Account ID: " << rhs.account_id_ << endl;
	for (int i = 0; i < 10; i++)
	{
		out_stream << "    " << rhs.funds_[i] << endl;
	}
	return out_stream;
}