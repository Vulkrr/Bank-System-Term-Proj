#include "SavingAccount.h"
#include <iostream>

SavingAccount::SavingAccount()
{
	accName = "";
	interestRate = 0;
}
SavingAccount::SavingAccount(int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _customerInfo, string _accName, double _interestRate) : Account(_ID, _withdrawCount, _depositCount, _bal, _customerInfo)
{
	accName = _accName;
	setInterestRate(_interestRate);
}

void SavingAccount::setAll(int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _customerInfo, string _accName, double _interestRate)
{
	Account::setAll(_ID, _withdrawCount, _depositCount, _bal, _customerInfo);
	accName = _accName;
	setInterestRate(_interestRate);
}
void SavingAccount::setInterestRate(double _interestRate)
{
	if (_interestRate >= 0)
	{
		interestRate = _interestRate;
	}
	else
	{
		interestRate = 0;
	}
}

string SavingAccount::getAccName() const
{
	return accName;
}
double SavingAccount::getInterestRate() const
{
	return interestRate;
}

void SavingAccount::payInterest()
{
	double tempBal = getBal();
	setBal(tempBal - (tempBal * interestRate - tempBal));
}
void SavingAccount::transfer(double _amount, SavingAccount & _destinationAccount)
{
	if (_amount <= _destinationAccount.getBal())
	{
		double tempBal = getBal();
		double tempDestinationBal = _destinationAccount.getBal();
		setBal(tempBal - _amount);
		_destinationAccount.setBal(tempDestinationBal + tempBal);
	}
	else
	{
		cout << "You do not have enough to funds to make this transaction." << endl;
	}
}