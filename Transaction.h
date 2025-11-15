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

class Transaction {
	string transactionType; //The spelling and capitalization of this will be important for validation. It must be either "Withdrawal", "Deposit", or "Transfer" (we can add more later or change if needed)
	double transactionAmnt, snapshotBal; //Snapshot balance will just save what the balance was at the time of transaction
public:
	Transaction();
	Transaction(string _transactionType, double _transactionAmnt, double _snapshotBal);

	void setAll(string _transactionType, double _transactionAmnt, double _snapshotBal);
	void setTransactionType(string _transactionType);
	void setTransactionAmnt(double _transactionAmnt);
	void setSnapshotBal(double _snapshotBal);

	string getTransactionType() const;
	double getTransactionAmnt() const;
	double getSnapshotBal() const;

	void printTransaction();
};
#endif // !_ACCOUNT_
