#include "Customer.h"
#include "Account.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
#include "MiscFunctions.h"
#include <iomanip>

int main() {

	//Array limits
	const int customerLimit = 10, checkingAccLimit = 5, savingAccLimit = 5;
	const double interestRate = 1.02, overdraftLimit = 50; 

	//Arrays
	Customer customerList[customerLimit];
	CheckingAccount checkingAccList[checkingAccLimit];
	SavingAccount savingAccList[savingAccLimit];
	//Transaction* transactions = new Transaction[transactionCount]; Not implemented yet, refer to Transaction.h for info
	
	//Indexes
	int totalCustomerCount = 0, customerIndex = 0, checkingAccIndex = 0, savingAccIndex = 0, transactionIndex = 0;

	//Flags
	bool customerFound = false;

	//Input variables
	int menuOpt, accountOpt, menuReturnOpt; 
	char existingOpt;

	//Customer info inputs
	string fname, lname, address, email, phoneNumber; 

	do
	{
		system("cls");
		cout << "======================================" << endl; //Main menu 
		cout << "Select one of the following options: " << endl;
		cout << "1. Create an account" << endl;
		cout << "2. Modify or delete accounts" << endl;
		cout << "3. View personal account information" << endl;
		cout << "4. View all customers" << endl;
		cout << "5. Exit program" << endl;
		cin >> menuOpt;
		while (menuOpt < 1 || menuOpt > 5) //Input validation
		{
			cout << "Invalid option. Please enter an option 1-5: ";
			cin >> menuOpt;
		}

		switch (menuOpt) 
		{
		case 1: //Option 1: Create an account
			system("cls");
			cout << "----------------------------------------" << endl;
			cout << "Is the user an existing customer? (Y/N): ";
			cin >> existingOpt;
			while (existingOpt != 'Y' && existingOpt != 'y' && existingOpt != 'N' && existingOpt != 'n') //Input validation
			{
				cout << "Invalid option." << endl;
				cout << "Is the user an existing customer? (Y/N): ";
				cin >> existingOpt;
			}

			if (existingOpt == 'N' || existingOpt == 'n') //If the user is a new customer, create a new customer
			{
				cout << "------------------------------------------------------------" << endl;
				cout << "Please enter the following information for the new customer: " << endl;
				cout << "Enter customer first name: ";
				cin >> fname;
				customerList[totalCustomerCount].setFname(fname);
				cout << "Enter customer last name: ";
				cin >> lname;
				customerList[totalCustomerCount].setLname(lname);
				cout << "Enter customer address: ";
				cin.ignore();
				getline(cin, address);
				//Ensure there are no duplicates here
				customerList[totalCustomerCount].setAddress(address);
				cout << "Enter customer email: ";
				cin >> email;
				//Ensure there are no duplicates here
				customerList[totalCustomerCount].setEmail(email);
				cout << "Enter customer phone number (digits only): ";
				cin >> phoneNumber;
				//Ensure there are no duplicates here
				customerList[totalCustomerCount].setPhone(phoneNumber);
				cout << "Customer successfully added to system." << endl;
				totalCustomerCount++;
			}
			else //If the user is an existing customer, enter their credentials
			{
				cout << "Please enter the following credentials:";
				cout << "Enter customer last name: ";
				cin >> lname;
				cout << "Enter customer phone number (digits only): ";
				cin >> phoneNumber;

				for (int i = 0; i < totalCustomerCount; i++) //Check every customer to find a match
				{
					if (customerList[i].getLname() == lname && customerList[i].getPhone() == phoneNumber)
					{
						customerFound = true;
						customerIndex = i;
						cout << "Customer found." << endl;
						break;
					}
				}
			}

			cout << "------------------------------------------------------" << endl; //Account creation
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
				cout << "-----------------------------------------------" << endl;
				savingAccList[savingAccIndex].setAll((savingAccIndex + 1), 0, 0, 0, &customerList[customerIndex], interestRate);
				cout << "You have successfully created a saving account." << endl;
				savingAccIndex++;
			}
			else
			{
				cout << "-------------------------------------------------" << endl;
				checkingAccList[checkingAccIndex].setAll((checkingAccIndex + 1), 0, &customerList[customerIndex], overdraftLimit);
				cout << "You have successfully created a checking account." << endl;
				checkingAccIndex++;
			}

			cout << "Press any key to return to menu: ";
			cin.ignore();
			cin.get();

			break;
		case 2: //Option 2: Modify or delete accounts
			system("cls");
			cout << "---------------------------------------" << endl;
			cout << "This part is under construction, please come back later." << endl;

			break;
		case 3: //Option 3: View personal account info
			system("cls");
			cout << "---------------------------------------" << endl;
			cout << "Please select one of the following options: " << endl;
			cout << "Please enter the following credentials: " << endl;
			cout << "Enter customer last name: ";
			cin >> lname;
			cout << "Enter customer phone number (digits only): ";
			cin >> phoneNumber;

			for (int i = 0; i < totalCustomerCount; i++) //Check every customer to find a match
			{
				if (customerList[i].getLname() == lname && customerList[i].getPhone() == phoneNumber)
				{
					customerFound = true;
					customerIndex = i;
					cout << "Customer found." << endl;
					break;
				}
			}
			
			while (customerFound == false) //If the customer does not exist, give the user the option to try again or return to menu
			{
				cout << "Error: Customer does not exist or credentials are wrong." << endl;
				cout << "Press 1 to try again or 2 to return to main menu: ";
				cin >> menuReturnOpt;
				while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
				{
					cout << "Invalid option." << endl;
					cout << "Press 1 to try again or 2 to return to main menu: ";
					cin >> menuReturnOpt;
				}

				if (menuReturnOpt == 1) //Re-enter credentials
				{
					system("cls");
					cout << "---------------------------------------" << endl;
					cout << "Please enter the following credentials: " << endl;
					cout << "Enter customer last name: ";
					cin >> lname;
					cout << "Enter customer phone number (digits only): ";
					cin >> phoneNumber;

					for (int i = 0; i < totalCustomerCount; i++) //Check every customer to find a match
					{
						if (customerList[i].getLname() == lname && customerList[i].getPhone() == phoneNumber)
						{
							customerFound = true;
							cout << "Customer found." << endl;
							break;
						}
					}
				}
				else
				{
					break;
				}
			}

			if (customerFound == true)
			{
				cout << "-------------------------------------------------------------------------------------------------" << endl;
				savingAccList[savingAccIndex].printInfo();
				cout << "Press any key to return to menu: ";
				cin.ignore();
				cin.get();
			}
			
			break;
		case 4: //Option 4: View all customers
			system("cls");
			cout << "-------------------------------------------------------------------------------------------------" << endl;

			if (totalCustomerCount == 0)
			{
				cout << "There are no existing customers in the system." << endl << endl;
			}
			else
			{
				cout << left << setw(20) << "First Name" << left << setw(20) << "Last Name" << left << setw(30) << "Address" << left << setw(20) << "Phone #" << left << setw(20) << "Email" << endl;
				cout << "-------------------------------------------------------------------------------------------------" << endl;

				for (int i = 0; i < totalCustomerCount; i++)
				{
					customerList[i].printInfoPartial();
				}
			}

			cout << "Press any key to return to menu: ";
			cin.ignore();
			cin.get();
			break;
		}

	} while (menuOpt != 5);

	cout << "Toodles." << endl;

	return 0;
}