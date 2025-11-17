#include "Account.h"
#include <iostream>

Account::Account() {
	ID = 0;
	withdrawCount = 0;
	depositCount = 0;
	transferCount = 0;
	bal = 0;
	accName = "";
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
		cout << "Successfully deposited $" << _amount << " to " << accName << "." << endl;
		cout << "Account balance: $" << bal << endl;
		depositCount++;
	}
	else
	{
		cout << "Error: Cannot deposit a negative amount." << endl;
	}
}
void Account::withdraw(double _amount)
{
	if (_amount >= 0)
	{
		if (_amount <= bal)
		{
			bal -= _amount;
			cout << "Successfully withdrew $" << _amount << " from " << accName << "." << endl;
			cout << "Account balance: $" << bal << endl;
			withdrawCount++;
		}
		else
		{
			cout << "Error: Not enough funds in account." << endl;
		}
	}
	else
	{
		cout << "Error: Cannot withdraw a negative amount." << endl;
	}
}
void Account::transfer(double _amount, Account& _destinationAccount)
{
	if (_amount >= 0)
	{
		if (_amount <= bal)
		{
			bal -= _amount;
			_destinationAccount.setBal(_destinationAccount.getBal() + _amount);
			cout << "Successfully transferred $" << _amount << " from " << accName << " to " << _destinationAccount.getAccName() << "." << endl;
			cout << "Account balance: $" << bal << endl;
			transferCount++;
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
	cout << "Total Balance: " << "$" << bal << endl;
	cout << "Times deposited: " << depositCount << endl;
	cout << "Times withdrawn: " << withdrawCount << endl;
	cout << "Times transferred: " << transferCount << endl;
}

