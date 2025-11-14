#include "Transaction.h"
#include <iostream>

Transaction::Transaction()
{
	transactionType = "";
	transactionAmnt = 0;
	snapshotBal = 0;
	overdraft = false;
}
Transaction::Transaction(string _transactionType, double _transactionAmnt, double _snapshotBal, bool _overdraft)
{
	transactionType = _transactionType;
	setTransactionAmnt(_transactionAmnt);
	setSnapshotBal(_snapshotBal);
	overdraft = _overdraft;
}

void Transaction::setAll(string _transactionType, double _transactionAmnt, double _snapshotBal, bool _overdraft)
{
	transactionType = _transactionType;
	setTransactionAmnt(_transactionAmnt);
	setSnapshotBal(_snapshotBal);
	overdraft = _overdraft;
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
void Transaction::setOverdraft(bool _overdraft)
{
	overdraft = _overdraft;
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
bool Transaction::getOverdraft() const
{
	return overdraft;
}

void printTransaction()
{
	cout << "Printing transactions is WIP." << endl;
}