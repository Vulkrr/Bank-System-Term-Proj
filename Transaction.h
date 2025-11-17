#pragma once
#ifndef _TRANSACTION_
#define _TRANSACTION_
#include "SavingAccount.h"
#include "CheckingAccount.h"

class Transaction {
	string transactionType, accName;
	int ID;
	double transactionAmnt, snapshotBal; //Save what the balance was at the time of transaction
	Customer* customerInfo;
public:
	Transaction();
	Transaction(int _ID, string _accName, string _transactionType, double _transactionAmnt, double _snapshotBal, Customer * _customerInfo);

	void setAll(int _ID, string _accName, string _transactionType, double _transactionAmnt, double _snapshotBal, Customer* _customerInfo);
	void setID(int _ID);
	void setAccName(string _accName);
	void setTransactionType(string _transactionType);
	void setTransactionAmnt(double _transactionAmnt);
	void setSnapshotBal(double _snapshotBal);
	void setCustomerInfo(Customer* _customerInfo);

	string getTransactionType() const;
	double getTransactionAmnt() const;
	double getSnapshotBal() const;
	Customer* getCustomerInfo() const;

	void printTransaction();
};
#endif // !_ACCOUNT_
