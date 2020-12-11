// Bank.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "jolly_banker.h"

int main()
{
    JollyBanker teller;
    if (teller.read_transactions("BankTransIn.txt"))
    {
        teller.execute_transactions();
        teller.display();
    }
    return 0;
}