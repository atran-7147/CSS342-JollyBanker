#include "fund.h"

Fund::Fund()
{
	name_ = "Unnamed Fund";
	balance_ = 0;
}

Fund::~Fund()
{
}

string Fund::get_name() const
{
	return name_;
}

void Fund::set_name(string name)
{
	name_ = name;
}

int Fund::get_balance() const
{
	return balance_;
}

bool Fund::add_funds(int amount)
{
	balance_ += amount;
	return true;
}

bool Fund::remove_funds(int amount)
{
	balance_ -= amount;
	return true;
}

bool Fund::log_history(Transaction trns)
{
	history_.push_back(trns);
	return true;
}

void Fund::display_fund_history()
{
	for (int i = 0; i < history_.size(); i++)
	{
		cout << " " << history_[i] << endl;
	}
}

//Format how fund is displayed in output
ostream& operator<<(ostream& out_stream, Fund& rhs)
{
	out_stream << rhs.get_name() << ": $" << rhs.get_balance();
	return out_stream;
}