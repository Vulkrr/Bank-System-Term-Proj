#pragma once
#ifndef _CHECKING_ACCOUNT_
#define _CHECKING_ACCOUNT_
#include <string>
#include "Account.h"
using namespace std;

class CheckingAccount :public Account {
	double overdraftLimit;
public:
	CheckingAccount();
	CheckingAccount(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo,  double _overdraftLimit);

	void setAll(int _ID, int _withdrawCount, int _depositCount, int _transferCount, double _bal, string _accName, Customer* _customerInfo, double _overdraftLimit);
	void setOverdraftLimit(double _limit);

	double getOverdraftLimit() const;
	
	void withdraw(double _amount);
};
#endif // !_CHECKING_ACCOUNT_
