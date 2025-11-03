#include "Customer.h"
#include "Account.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
#include "MiscFunctions.h"


// Might be easiest to just build out a whole class in the respective cpp + header file then fill in main class shit later -CZL
// Got bored on the account.cpp file if you could finish the implementation and that should be all for today lowkey, two classes done :p


int main() {

	const int customerLimit = 10, checkingAccLimit = 5, savingAccLimit = 5; //Array limits
	const double interestRate = 1.02, overdraftLimit = 50; 
	int menuOpt, accountOpt; //Option inputs
	int checkingAccCount = 0, savingAccCount = 0, transactionCount = 0; //Array counters
	string fname, lname, address, email, phoneNumber; //Customer info inputs

	Customer customerList[customerLimit];
	CheckingAccount checkingAccList[checkingAccLimit];
	SavingAccount savingAccList[savingAccLimit];
	//Transaction* transactions = new Transaction[transactionCount]; //Dw abt this for now, refer to Transaction.h for info

	do
	{
		cout << "======================================" << endl;
		cout << "Select one of the following options: " << endl;
		cout << "1. Create an account" << endl;
		cout << "2. View account information" << endl;
		cout << "3. Modify or delete accounts" << endl;
		cout << "4. Exit program" << endl;
		cin >> menuOpt;
		while (menuOpt < 1 || menuOpt > 4)
		{
			cout << "Invalid option. Please enter an option 1-4: ";
			cin >> menuOpt;
		}

		switch (menuOpt)
		{
		case 1:
			cout << "======================================" << endl;
			cout << "Is the user an existing customer? (Y/N): ";


			cout << "Select which type of account you would like to create: " << endl;
			cout << "1. Saving account" << endl;
			cout << "2. Checking account" << endl;

			cin >> accountOpt;
			while (accountOpt < 1 || accountOpt > 2)
			{
				cout << "Invalid option. Please enter an option 1-2: ";
				cin >> accountOpt;
			}

			if (accountOpt == 1)
			{
				cout << "======================================" << endl;
				savingAccList[savingAccCount].setAll((savingAccCount + 1), 0, 0, 0, &customerList[0], interestRate);
				cout << "You have successfully created a saving account." << endl;
				savingAccCount++;
			}
			else
			{
				cout << "======================================" << endl;
				checkingAccList[checkingAccCount].setAll((checkingAccCount + 1), 0, &customerList[0], overdraftLimit);
				cout << "You have successfully created a checking account." << endl;
				checkingAccCount++;
			}

			break;
		case 2:
			cout << "======================================" << endl;
			cout << "This part is under construction, please come back later." << endl;
			break;
		case 3:
			cout << "======================================" << endl;
			cout << "This part is under construction, please come back later." << endl;
			break;
		}

	} while (menuOpt != 4);


	//Overdraft testing
	Customer chris("Christian", "Leslie", "JU", "cleslie@", "9402795022");
	CheckingAccount chrisAccount;
	chrisAccount.setAll(1, 600, &chris, 50);
	cout << chrisAccount.getOverdraftLimit() << endl;

	chrisAccount.withdraw(650);

	cout << chrisAccount.getOverdraftLimit() << endl;

	cout << "Toodles." << endl;

	return 0;
}