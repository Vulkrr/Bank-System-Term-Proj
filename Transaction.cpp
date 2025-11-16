#include "Transaction.h"
#include <iostream>

Transaction::Transaction()
{
	transactionType = "";
	transactionAmnt = 0;
	snapshotBal = 0;
}
Transaction::Transaction(string _transactionType, double _transactionAmnt, double _snapshotBal, Customer* _customerInfo)
{
	transactionType = _transactionType;
	setTransactionAmnt(_transactionAmnt);
	setSnapshotBal(_snapshotBal);
	customerInfo = _customerInfo;
}

void Transaction::setAll(string _transactionType, double _transactionAmnt, double _snapshotBal, Customer* _customerInfo)
{
	transactionType = _transactionType;
	setTransactionAmnt(_transactionAmnt);
	setSnapshotBal(_snapshotBal);
	customerInfo = _customerInfo;
}
void Transaction::setTransactionType(string _transactionType)
{
	transactionType = _transactionType;
}
void Transaction::setTransactionAmnt(double _transactionAmnt)
{
	if (_transactionAmnt > 0)
	{
		transactionAmnt = _transactionAmnt;
	}
	else
	{
		transactionAmnt = 0;
	}
}
void Transaction::setSnapshotBal(double _snapshotBal)
{
	if (_snapshotBal > 0)
	{
		snapshotBal = _snapshotBal;
	}
	else
	{
		_snapshotBal = 0;
	}
}
void Transaction::setCustomerInfo(Customer* _customerInfo)
{
	customerInfo = _customerInfo;
}

string Transaction::getTransactionType() const
{
	return transactionType;
}
double Transaction::getTransactionAmnt() const
{
	return transactionAmnt;
}
double Transaction::getSnapshotBal() const
{
	return snapshotBal;
}
Customer* Transaction::getCustomerInfo() const
{
	return customerInfo;
}

void Transaction::printTransaction()
{
	cout << "WIP." << endl;
}