#pragma once
#ifndef _TRANSACTION_
#define _TRANSACTION_
#include "SavingAccount.h"
#include "CheckingAccount.h"

/*This is a WIP.The current idea I have is to use this for saving transaction history.
Here's my idea for how it works: 
Step 1: Create a dynamically allocated array of type transaction, it's size will be determined by a transaction counter that goes up every time the user makes a transaction.
Step 2: Every time the user makes a transaction:
	-Increase the transaction counter.
	-Create a new dynamically allocated array with the new counter as its size.
	-Copy every past transaction into the new array.
	-Add the new transaction into the array.
	-Delete the old array.
This process can be put into a function in the transaction cpp file and called every time the user makes a withdrawal, deposit, or transfer.

This lowkey makes the withdrawCounter and depositCounter useless so we can ask Sarraf if we are allowed to remove them
*/

class Transaction : public SavingAccount, public CheckingAccount {
	string transactionType; //The spelling and capitalization of this will be important for validation. It must be either "Withdrawal", "Deposit", or "Transfer" (we can add more later or change if needed)
	double transactionAmount, snapshotBalance; //Snapshot balance will just save what the balance was at the time of transaction
	bool overdraft; //If the transaction resulted in an overdraft, it will display info about that
public:
	Transaction();
	Transaction(string _transactionType, double transactionAmount, double snapshotBalance, bool overdraft);
};
#endif // !_ACCOUNT_
