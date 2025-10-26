#pragma once
#ifndef _ACCOUNT_
#define _ACCOUNT_
#include <string>
#include "Customer.h"
using namespace std;

class Account {
	int ID, withdrawCount, depositCount;
	double bal;
	Customer* customerInfo;
public:
	Account();
	Account(int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _customerInfo);

	void setAll(int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _customerInfo);
	void setID(int _ID);
	void setWithdrawCount(int _withdrawCount);
	void setDepositCount(int _depositCount);
	void setBal(double _bal);

	int getID() const;
	int getWithdrawCount() const;
	int getDepositCount() const;
	double getBal() const;

	void deposit(double _amount);
	void withdraw(double _amount);
	void printInfo();
	void increaseWithdrawCount();
};
#endif // !_ACCOUNT_
