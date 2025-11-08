#pragma once
#ifndef _SAVINGACCOUNT_
#define _SAVINGACCOUNT_
#include <string>
#include "Account.h"
using namespace std;

class SavingAccount : public Account {
	string accName;
	double interestRate;
public:
	SavingAccount();
	SavingAccount(int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _customerInfo, string _accName, double _interestRate);

	void setAll(int _ID, int _withdrawCount, int _depositCount, double _bal, Customer* _customerInfo, string _accName, double _interestRate);
	void setAccName(string _accName);
	void setInterestRate(double _interestRate);
	
	string getAccName() const;
	double getInterestRate() const;

	void payInterest();
	void transfer(double _amount, SavingAccount & _destinationAccount);
};

#endif // !_SAVINGACCOUNT_