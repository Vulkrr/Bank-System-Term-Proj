#include <iostream>
#include <string>
#include "Account.h"
#include "Customer.h"
#include "CheckingAccount.h"

using namespace std;
// Might be easiest to just build out a whole class in the respective cpp + header file then fill in main class shit later -CZL
// Got bored on the account.cpp file if you could finish the implementation and that should be all for today lowkey, two classes done :p

int main() {

	/*int opt;

	do
	{
		cout << "=====================" << endl;
		cout << "Select one of the following options: " << endl;
		cout << "1. Create a saving account" << endl;
		cout << "2. View account information" << endl;
		cout << "3. Modify or delete accounts" << endl;
		cout << "4. Exit program" << endl;
		cin >> opt;


	} while (opt != 4);*/

	Customer chris("Christian", "leslie", "JU", "cleslie@", "9402795022");
	CheckingAccount chrisAccount;
	chrisAccount.setAll(1, 600, &chris, 50);
	cout << chrisAccount.getOverdraftLimit();

	chrisAccount.withdraw(650);

	cout << chrisAccount.getOverdraftLimit();


	return 0;
}