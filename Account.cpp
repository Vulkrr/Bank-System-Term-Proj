#include "Account.h"
#include <iostream>

Account::Account() {
	ID = 0;
	withdrawCount = 0;
	depositCount = 0;
	transferCount = 0;
	bal = 0;
	customerInfo = nullptr;
}
Account::Account(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo) {
	setAll(_ID, _withdrawCount, _depositCount, _transferCount, _bal, _accName, _customerInfo);
}

void Account::setAll(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo) {
	ID = _ID;
	setWithdrawCount(_withdrawCount);
	setDepositCount(_depositCount);
	setTransferCount(_transferCount);
	setBal(_bal);
	setAccName(_accName);
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
void Account::setTransferCount(int _transferCount)
{
	if (_transferCount >= 0)
	{
		transferCount = _transferCount;
	}
	else
	{
		transferCount = 0;
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
void Account::setAccName(string _accName)
{
	accName = _accName;
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
string Account::getAccName() const
{
	return accName;
}
Customer* Account::getCustomerInfo() const
{
	return customerInfo;
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
void Account::transfer(double _amount, Account& _destinationAccount)
{
	if (_amount <= _destinationAccount.getBal())
	{
		bal += _destinationAccount.getBal();
		_destinationAccount.setBal(_destinationAccount.getBal() - _amount);
	}
	else
	{
		cout << "You do not have enough to funds to make this transaction." << endl;
	}
}
void Account::printInfo()
{
	if (customerInfo != nullptr)
		customerInfo->printInfoFull();
	cout << "-------------" << endl;
	cout << "Account ID: " << ID << endl;
	cout << "Balance: " << "$" << bal << endl;
	cout << "Savings: " << "$" << savings << endl;
	cout << "Checking: " << "$" << checking << endl;
	cout << "Times deposited: " << depositCount << endl;
	cout << "Times withdrawn: " << withdrawCount << endl;
	cout << "Times transferred: " << transferCount << endl;
}

void Account::getLoan(double _loan){
	if (_loan > 0) {
	bal += _loan;
	}
	else {
	cout << "You have entered an incorrect amount for your loan." << endl;
	}
}
