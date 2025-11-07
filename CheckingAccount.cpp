#include "CheckingAccount.h"
#include <iostream>

void CheckingAccount::setOverdraftLimit(double _overdraftlimit) {
	if (_overdraftlimit < 0) {
		overdraftLimit = 0;
	}
	else {
		overdraftLimit = _overdraftlimit;
	}
}
double CheckingAccount::getOverdraftLimit() const {
	return overdraftLimit;
}
CheckingAccount::CheckingAccount() :Account() {
	overdraftLimit = 0;
}
CheckingAccount::CheckingAccount(int _ID, double _bal, Customer* _customerInfo, double _overdraftLimit) {
	setAll(_ID, _bal, _customerInfo, _overdraftLimit);
}
void CheckingAccount::setAll(int _ID, double _bal, Customer* _customerInfo, double _overdraftLimit) {
	Account::setID(_ID);
	Account::setBal(_bal);
	setOverdraftLimit(_overdraftLimit);
}
void CheckingAccount::withdraw(double _amount) {
	if (_amount >= 0)
		if (bal >= _amount)
		{
			tempBal -= _amount;
			setBal(tempBal);
			cout << "You have successfully withdrawn $" << _amount << "." << endl;
		}
		else
		{
			if (abs(tempBal - _amount) <= overdraftLimit)
			{
				double overdraftAmount = abs(tempBal - _amount);
				tempBal -= _amount;
				tempBal -= 20; //Overdraft fee
				setBal(tempBal);
				setOverdraftLimit(getOverdraftLimit() - overdraftAmount);
				setWithdrawCount(getWithdrawCount() + 1);
				cout << "You have successfully withdrawn $" << _amount << " with an overdraft of " << overdraftAmount << "." << endl;
				cout << "A $20 overdraft fee has been charged to your account." << endl;
				cout << "Balance: " << getBal() << endl;
			}
			else
			{
				cout << "You do not have enough Overdraft Protection to make this transaction." << endl;
			}
		}
	}
	else
	{
		cout << "Error, cannot withdraw a negative amount." << endl;
	}
}