#pragma once
#ifndef _TRANSACTION_
#define _TRANSACTION_
#include "SavingAccount.h"
#include "CheckingAccount.h"

/*This is a WIP.
Step 1: Create a vector of type transaction.
Step 2: Every time the user makes a transaction:
	-Increase the vector size
	-Add new transaction info into the vector slot.
This process can be put into a function in the transaction cpp file and called every time the user makes a withdrawal, deposit, or transfer.
*/

class Transaction : public SavingAccount, public CheckingAccount {
	string transactionType; //The spelling and capitalization of this will be important for validation. It must be either "Withdrawal", "Deposit", or "Transfer" (we can add more later or change if needed)
	double transactionAmount, snapshotBalance; //Snapshot balance will just save what the balance was at the time of transaction
	bool overdraft; //If the transaction resulted in an overdraft, it will display info about that
public:
	Transaction();
	
};
#endif // !_ACCOUNT_
