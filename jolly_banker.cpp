#include "jolly_banker.h"

JollyBanker::JollyBanker()
{
}

JollyBanker::~JollyBanker()
{
}

//Read from a file to create transactions and insert them into a queue.
bool JollyBanker::read_transactions(string file_name)
{
    ifstream in_file;
    in_file.open(file_name);
    if (in_file.is_open())
    {
        while (!in_file.eof())
        {
            Transaction trns;
            in_file >> trns;
            list_.push(trns);
        }
        in_file.close();
        return true;
    }
    else
    {
        cout << "file: " << file_name << " not found." << endl;
        return false;
    }
    return false;
}

//Determines the transaction type and executes each one accordingly
void JollyBanker::execute_transactions()
{
    while (!list_.empty())
    {
        if (list_.front().get_type() == 'O')
        {
            accounts_.Insert(new Account(list_.front().get_first_name(), list_.front().get_last_name(), list_.front().get_account_id()));
        }
        else if (list_.front().get_type() == 'D')
        {
            Account* deposit_to;
            if (accounts_.Retrieve(list_.front().get_account_id(), deposit_to))
            {
                deposit_to->deposit_funds(list_.front().get_fund_id(), list_.front().get_amount(), list_.front());
            }
            else if (list_.front().get_account_id() < 1000 || list_.front().get_account_id() > 9999)
            {
                if (list_.front().get_account_id() > 99 && list_.front().get_account_id() < 1000)
                {
                    cerr << "ERROR: Deposits to Account ID #" << list_.front().get_account_id() << list_.front().get_fund_id() << " must specify Fund ID. Transaction refused." << endl;
                }
                else if (list_.front().get_account_id() < 100)
                {
                    cerr << "ERROR: " << list_.front().get_account_id() << abs(list_.front().get_fund_id()) << " is not a valid account number. Transaction refused." << endl;
                }
                else
                {
                    cerr << "ERROR: " << list_.front().get_account_id() << " is not a valid account number. Transaction refused." << endl;
                }
            }
            else
            {
                cerr << "ERROR: Account " << list_.front().get_account_id() << " not found. Funds not deposited." << endl;
            }
        }
        else if (list_.front().get_type() == 'W')
        {
            Account* withdraw_from;
            if (accounts_.Retrieve(list_.front().get_account_id(), withdraw_from))
            {
                withdraw_from->withdraw_funds(list_.front().get_fund_id(), list_.front().get_amount(), list_.front());
            }
            else if (list_.front().get_account_id() < 1000 || list_.front().get_account_id() > 9999)
            {
                if (list_.front().get_account_id() > 99 && list_.front().get_account_id() < 1000)
                {
                    cerr << "ERROR: Withdrawls from Account ID #" << list_.front().get_account_id() << list_.front().get_fund_id() << " must specify Fund ID. Transaction refused." << endl;
                }
                else if (list_.front().get_account_id() < 100)
                {
                    cerr << "ERROR: " << list_.front().get_account_id() << abs(list_.front().get_fund_id()) << " is not a valid account number. Transaction refused." << endl;
                }
                else
                {
                    cerr << "ERROR: " << list_.front().get_account_id() << " is not a valid account number. Transaction refused." << endl;
                }
            }
            else
            {
                cerr << "ERROR: Account " << list_.front().get_account_id() << " not found. Funds not withdrawn." << endl;
            }
        }
        else if (list_.front().get_type() == 'T')
        {
            Account* withdraw_from;
            Account* deposit_to;
            if (accounts_.Retrieve(list_.front().get_account_id(), withdraw_from) && accounts_.Retrieve(list_.front().get_to_account_id(), deposit_to))
            {
                if (withdraw_from->withdraw_funds(list_.front().get_fund_id(), list_.front().get_amount(), list_.front()))
                {
                    deposit_to->deposit_funds(list_.front().get_to_fund_id(), list_.front().get_amount(), list_.front());
                }
            }
            else if (list_.front().get_account_id() < 1000 || list_.front().get_account_id() > 9999)
            {
                if (list_.front().get_account_id() > 99 && list_.front().get_account_id() < 1000)
                {
                    cerr << "ERROR: Transfers from Account ID #" << list_.front().get_account_id() << list_.front().get_fund_id() << " must specify Fund ID. Transaction refused." << endl;
                }
                else if (list_.front().get_account_id() < 100)
                {
                    cerr << "ERROR: " << list_.front().get_account_id() << abs(list_.front().get_fund_id()) << " is not a valid account number. Transaction refused." << endl;
                }
                else
                {
                    cerr << "ERROR: " << list_.front().get_account_id() << " is not a valid account number. Transaction refused." << endl;
                }
            }
            else if (list_.front().get_to_account_id() < 1000 || list_.front().get_to_account_id() > 9999)
            {
                if (list_.front().get_to_account_id() > 99 && list_.front().get_to_account_id() < 1000)
                {
                    cerr << "ERROR: Transfers to Account ID #" << list_.front().get_to_account_id() << list_.front().get_to_fund_id() << " must specify Fund ID. Transaction refused." << endl;
                }
                else if (list_.front().get_to_account_id() < 100)
                {
                    cerr << "ERROR: " << list_.front().get_to_account_id() << abs(list_.front().get_to_fund_id()) << " is not a valid account number. Transaction refused." << endl;
                }
                else
                {
                    cerr << "ERROR: " << list_.front().get_to_account_id() << " is not a valid account number. Transaction refused." << endl;
                }
            }
            else if (accounts_.Retrieve(list_.front().get_to_account_id(), deposit_to))
            {
                cerr << "ERROR: Account " << list_.front().get_account_id() << " not found. Transferal refused." << endl;
            }
            else
            {
                cerr << "ERROR: Account " << list_.front().get_to_account_id() << " not found. Transferal refused." << endl;
            }
        }
        else if (list_.front().get_type() == 'H')
        {
            Account* print;
            if (accounts_.Retrieve(list_.front().get_account_id(), print))
            {
                if (list_.front().get_fund_id() != -1)
                {
                    print->display_fund_history(list_.front().get_fund_id());
                    cout << endl;
                }
                else
                {
                    print->display_account_history();
                    cout << endl;
                }
            }
            else if (list_.front().get_account_id() < 1000 || list_.front().get_account_id() > 9999)
            {
                if (list_.front().get_account_id() < 1000)
                {
                    cerr << "ERROR: " << list_.front().get_account_id() << abs(list_.front().get_fund_id()) << " is not a valid account number. Transaction refused." << endl;
                }
                else
                {
                    cerr << "ERROR: " << list_.front().get_account_id() << " is not a valid account number. Transaction refused." << endl;
                }
            }
            else
            {
                cerr << "ERROR: Account " << list_.front().get_account_id() << " not found. Cannot display history." << endl;
            }
        }
        list_.pop();
    }
}

//Displays a list of all accounts and the balances in each of their funds.
void JollyBanker::display()
{
    cout << endl;
    cout << "Processing Done. Final Balances:" << endl;
    accounts_.display();
}