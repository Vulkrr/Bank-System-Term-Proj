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


	//Don't worry about this for now, I was rewriting it to see if there's an easier way to write this part but idek if it works cause there's an error somewhere else and I can't see debugging shit
	if (_amount >= 0)
	{
		double tempBal = getBal();
		if (tempBal >= _amount)
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

	/*if (tempBal - _amount < 0) {
		_amount -= tempBal;
		if (tempBal >= overdraftLimit) {

			tempBal -= _amount;

			setOverdraftLimit(-tempBal);
			Account::setBal(tempBal);
			increaseWithdrawCount();
			cout << "You have successfully withdrawn $" << _amount << ", a $20 overdraft fee has been taken out, your new Account Balance is: $"
				<< Account::getBal() << " Overdraft protection is now: $" << getOverdraftLimit() << endl;
		}
		else if (tempBal < overdraftLimit) {
			cout << "You do not have enough Overdraft Protection to make this transaction, have a nice day." << endl;
		}
		else {
			cout << "Error, not enough funds or Overdraft Protection" << endl;
		}
	}
	else if (tempBal - _amount >= 0) {
		Account::setBal(tempBal);
		Account::setWithdrawCount(+1);
		cout << "You have successfully withdrawn $" << _amount << " your new Account Balance is: $" << Account::getBal() << endl;
	}
	else {
		cout << "An error has occured on our end, please try again" << endl;
	}*/
}