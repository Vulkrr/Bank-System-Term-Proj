#pragma once
#ifndef _TRANSACTION_
#define _TRANSACTION_
#include "SavingAccount.h"
#include "CheckingAccount.h"

class Transaction : public SavingAccount, public CheckingAccount {
	string transactionType;
	double transactionAmount, snapshotBalance;
	bool overdraft;
public:
	Transaction()
	{
		transactionType = "";
		transactionAmount = 0;
		snapshotBalance = 0;
		overdraft = false;
	}

	Transaction(string _transactionType, double transactionAmount, double snapshotBalance, bool overdraft)
	{

	}
};
#endif // !_ACCOUNT_
