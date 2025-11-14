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
	SavingAccount(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo, double _interestRate);

	void setAll(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo, double _interestRate);
	void setInterestRate(double _interestRate);

	double getInterestRate() const;

	void payInterest();
};

#endif // !_SAVINGACCOUNT_
