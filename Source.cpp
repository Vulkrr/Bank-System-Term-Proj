#include "Customer.h"
#include "Account.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
#include "MiscFunctions.h"


// Might be easiest to just build out a whole class in the respective cpp + header file then fill in main class shit later -CZL
// Got bored on the account.cpp file if you could finish the implementation and that should be all for today lowkey, two classes done :p


int main() {

	//Array limits
	const int customerLimit = 10, checkingAccLimit = 5, savingAccLimit = 5;
	const double interestRate = 1.02, overdraftLimit = 50; 

	//Input variables
	int menuOpt, accountOpt; 
	char existingOpt;

	//Counters
	int newCustomerCount = 0, customerCount = 0, checkingAccCount = 0, savingAccCount = 0, transactionCount = 0; 

	//Customer info inputs
	string fname, lname, address, email, phoneNumber; 

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
			cin >> existingOpt;
			
			while (existingOpt != 'Y' && existingOpt != 'y' && existingOpt != 'N' && existingOpt != 'n')
			{
				cout << "Invalid option." << endl;
				cout << "Is the user an existing customer? (Y/N): ";
				cin >> existingOpt;
			}

			if (existingOpt == 'N' || existingOpt == 'n')
			{
				cout << "====================NEW CUSTOMER INFO====================" << endl;
				cout << "Welcome. Please enter the following information: " << endl;
				cout << "Enter customer first name: ";
				cin >> fname;
				customerList[customerCount].setFname(fname);
				cout << "Enter customer last name: ";
				cin >> fname;
				customerList[customerCount].setLname(lname);
				cout << "Enter customer address: ";
				cin.ignore();
				getline(cin, address);
				customerList[customerCount].setAddress(address);
				cout << "Enter customer email: ";
				cin >> email;
				customerList[customerCount].setEmail(email);
				cout << "Enter customer phone number (digits only): ";
				cin >> phoneNumber;
				customerList[customerCount].setPhone(phoneNumber);
				
			}
			
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
				savingAccList[savingAccCount].setAll((savingAccCount + 1), 0, 0, 0, &customerList[customerCount], interestRate);
				cout << "You have successfully created a saving account." << endl;
				savingAccCount++;
			}
			else
			{
				cout << "======================================" << endl;
				checkingAccList[checkingAccCount].setAll((checkingAccCount + 1), 0, &customerList[customerCount], overdraftLimit);
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