#include "Account.h"
#include <iostream>

Account::Account() {
	ID = 0;
	withdrawCount = 0;
	depositCount = 0;
	bal = 0;
	customerInfo = nullptr;
}
Account::Account(int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _customerInfo) {
	setAll(_ID, _withdrawCount, _depositCount, _bal, _customerInfo);
}

void Account::setAll(int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _customerInfo) {
	ID = _ID;
	setWithdrawCount(_withdrawCount);
	setDepositCount(_depositCount);
	setBal(_bal);
	customerInfo = _customerInfo;
}
void Account::setID(int _ID)
{
	ID = _ID;
}
void Account::setWithdrawCount(int _withdrawCount)
{
	if (_withdrawCount >= 0)
	{
		withdrawCount = _withdrawCount;
	}
	else
	{
		withdrawCount = 0;
	}

}
void Account::setDepositCount(int _depositCount)
{
	if (_depositCount >= 0)
	{
		depositCount = _depositCount;
	}
	else
	{
		depositCount = 0;
	}
}
void Account::setBal(double _bal)
{
	if (_bal >= 0)
	{
		bal = _bal;
	}
	else
	{
		bal = 0;
	}
}
void Account::setCustomerInfo(Customer* _customerInfo)
{
	customerInfo = _customerInfo;
}

int Account::getID() const
{
	return ID;
}
int Account::getWithdrawCount() const
{
	return withdrawCount;
}
int Account::getDepositCount() const
{
	return depositCount;
}
double Account::getBal() const
{
	return bal;
}

void Account::deposit(double _amount)
{
	if (_amount >= 0)
	{
		bal += _amount;
		depositCount++;
	}
}
void Account::withdraw(double _amount)
{
	if (_amount >= 0 && _amount <= bal)
	{
		bal -= _amount;
		withdrawCount++;
	}
	else
	{
		cout << "You do not have enough funds to withdraw." << endl;
	}
}
void Account::printInfo()
{
	if (customerInfo != nullptr)
		customerInfo->printInfo();
	cout << "Account ID: " << ID << endl;
	cout << "Total Balance: " << bal << endl;
	cout << "Savings: " << savings << endl;
	cout << "Checking: " << checking << endl;
	cout << "Debt: " << debt << endl;
	cout << "Times deposited: " << depositCount << endl;
	cout << "Times withdrawn: " << withdrawCount << endl;
}
