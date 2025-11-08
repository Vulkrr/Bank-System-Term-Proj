#pragma once
#ifndef _ACCOUNT_
#define _ACCOUNT_
#include <string>
#include "Customer.h"
using namespace std;

class Account {
	int ID, withdrawCount, depositCount, transferCount;
	 //New variables not implemented yet
	//"savings" and "checking" will be used for printInfo, it will just say how much of your balance is in savings and how much is in checking.
	Customer* customerInfo;
protected:
	double bal, savings, checking;
public:
	Account();
	Account(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, Customer* _customerInfo);

	void setAll(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, Customer* _customerInfo);
	void setID(int _ID);
	void setWithdrawCount(int _withdrawCount);
	void setDepositCount(int _depositCount);
	void setTransferCount(int _transferCount);
	void setBal(double _bal);
	void setCustomerInfo(Customer* _customerInfo);

	int getID() const;
	int getWithdrawCount() const;
	int getDepositCount() const;
	int getTransferCount() const;
	double getBal() const;

	void deposit(double _amount);
	void withdraw(double _amount);
	void printInfo();
};
#endif // !_ACCOUNT_
