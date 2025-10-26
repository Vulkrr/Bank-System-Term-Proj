#pragma once
#ifndef _SAVINGACCOUNT_
#define _SAVINGACCOUNT_
#include <string>
#include "Account.h"
using namespace std;

class SavingAccount : public Account {
	double interestRate;
public:
	SavingAccount();
	SavingAccount(int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _customerInfo, double _interestRate);

	void setInterestRate(double _interestRate);
	void setAll(int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _customerInfo, double _interestRate);
	double getInterestRate() const;

	void payInterest();
	void transfer(double _amount, SavingAccount & _destinationAccount);
};

#endif // !_SAVINGACCOUNT_