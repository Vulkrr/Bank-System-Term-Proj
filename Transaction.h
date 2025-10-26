#pragma once
#ifndef _TRANSACTION_
#define _TRANSACTION_
#include "Account.h"

class Account {
	int ID, withdrawCount, depositCount;
	double bal;
	Customer * accCustomer;
public:
	Account();
	Account(string _fname, string _lname, string _address, string _email, string _phone, int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _accCustomer);

	void setAll(string _fname, string _lname, string _address, string _email, string _phone, int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _accountCustomer);
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
};
#endif // !_ACCOUNT_
