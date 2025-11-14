#pragma once
#ifndef _ACCOUNT_
#define _ACCOUNT_
#include <string>
#include "Customer.h"
using namespace std;

class Account {
	int ID, withdrawCount, depositCount, transferCount;
	Customer* customerInfo;
protected:
	string accName;
	double bal, loan;
public:
	Account();
	Account(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo);

	void setAll(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string accName, Customer* _customerInfo);
	void setID(int _ID);
	void setWithdrawCount(int _withdrawCount);
	void setDepositCount(int _depositCount);
	void setTransferCount(int _transferCount);
	void setBal(double _bal);
	void setAccName(string _accName);
	void setCustomerInfo(Customer* _customerInfo);

	int getID() const;
	int getWithdrawCount() const;
	int getDepositCount() const;
	int getTransferCount() const;
	double getBal() const;
	double getLoan() const;
	string getAccName() const;
	Customer* getCustomerInfo() const;

	void deposit(double _amount);
	void withdraw(double _amount);
	void transfer(double _amount, Account& _destinationAcc);
	void printInfo();
};
#endif // !_ACCOUNT_
