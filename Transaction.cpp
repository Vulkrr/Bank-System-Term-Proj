#include "Transaction.h"
#include <iostream>
#include <iomanip>

Transaction::Transaction()
{
	ID = 0;
	accName = "";
	transactionType = "";
	transactionAmnt = 0;
	snapshotBal = 0;
}
Transaction::Transaction(int _ID, string _accName, string _transactionType, double _transactionAmnt, double _snapshotBal, Customer* _customerInfo)
{
	setID(_ID);
	accName = _accName;
	transactionType = _transactionType;
	setTransactionAmnt(_transactionAmnt);
	setSnapshotBal(_snapshotBal);
	customerInfo = _customerInfo;
}

void Transaction::setAll(int _ID, string _accName, string _transactionType, double _transactionAmnt, double _snapshotBal, Customer* _customerInfo)
{
	setID(_ID);
	accName = _accName;
	transactionType = _transactionType;
	setTransactionAmnt(_transactionAmnt);
	setSnapshotBal(_snapshotBal);
	customerInfo = _customerInfo;
}
void Transaction::setID(int _ID)
{
	if (_ID > 0)
	{
		ID = _ID;
	}
	else
	{
		ID = 0;
	}
}
void Transaction::setAccName(string _accName)
{
	accName = _accName;
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
	snapshotBal = _snapshotBal;	
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
	cout << right << setw(10) << ID << right << setw(30) << accName << right << setw(20) << transactionType << right << setw(15) << transactionAmnt << right << setw(20) << snapshotBal << endl;
}