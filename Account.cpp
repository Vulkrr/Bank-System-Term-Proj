#include "Account.h"
#include <iostream>

Account::Account() {
	ID = 0;
	withdrawCount = 0;
	depositCount = 0;
	transferCount = 0;
	bal = 0;
	loan = 0;
	customerInfo = nullptr;
}
Account::Account(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo) {
	setID(_ID);
	setWithdrawCount(_withdrawCount);
	setDepositCount(_depositCount);
	setTransferCount(_transferCount);
	setBal(_bal);
	setAccName(_accName);
	customerInfo = _customerInfo;
}

void Account::setAll(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo) {
	setID(_ID);
	setWithdrawCount(_withdrawCount);
	setDepositCount(_depositCount);
	setTransferCount(_transferCount);
	setBal(_bal);
	setAccName(_accName);
	customerInfo = _customerInfo;
}
void Account::setID(int _ID)
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
void Account::setWithdrawCount(int _withdrawCount)
{
	if (_withdrawCount > 0)
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
	if (_depositCount > 0)
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
	if (_transferCount > 0)
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
	if (_bal > 0)
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
int Account::getTransferCount() const
{
	return transferCount;
}
double Account::getBal() const
{
	return bal;
}
double Account::getLoan() const
{
	return loan;
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
	if (_amount > 0)
	{
		if (_amount <= _destinationAccount.getBal())
		{
			bal += _destinationAccount.getBal();
			_destinationAccount.setBal(_destinationAccount.getBal() - _amount);
		}
		else
		{
			cout << "Error: Not enough funds in account." << endl;
		}
	}
	else
	{
		cout << "Error: Cannot transfer a negative amount." << endl;
	}
	
}
void Account::printInfo()
{
	if (customerInfo != nullptr)
		customerInfo->printInfoFull();
	cout << "-------------" << endl;
	cout << "Total Balance: " << "$" << bal << endl;
	cout << "Times deposited: " << depositCount << endl;
	cout << "Times withdrawn: " << withdrawCount << endl;
	cout << "Times transferred: " << transferCount << endl;
}

