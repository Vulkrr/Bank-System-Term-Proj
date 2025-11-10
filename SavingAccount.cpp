#include "SavingAccount.h"
#include <iostream>

SavingAccount::SavingAccount()
{
	interestRate = 0;
}
SavingAccount::SavingAccount(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo,  double _interestRate) : Account(_ID, _withdrawCount, _depositCount, _transferCount, _bal, _accName, _customerInfo)
{
	setInterestRate(_interestRate);
}

void SavingAccount::setAll(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo, double _interestRate)
{
	Account::setAll(_ID, _withdrawCount, _depositCount, _transferCount, _bal, _accName, _customerInfo);
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


double SavingAccount::getInterestRate() const
{
	return interestRate;
}

void SavingAccount::payInterest()
{
	double tempBal = getBal();
	setBal(tempBal - (tempBal * interestRate - tempBal));
}
