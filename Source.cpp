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

	//vector<Transaction> transactionList[]; Not implemented yet, refer to Transaction.h for info
	
	//Indexes
	int totalCustomerCount = 0, customerIndex = 0, checkingAccIndex = 0, savingAccIndex = 0, transactionIndex = 0;

	//Flags
	bool customerFound = false, duplicateInfo = false;

	//Input variables
	int menuOpt, subMenuOpt, modifyOpt, menuReturnOpt; 
	char existingOpt;

	//Info inputs
	string fname, lname, address, email, phoneNumber, accName; 

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
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << "Invalid option. Please enter an option 1-5: ";
			cin >> menuOpt;
		}

		switch (menuOpt) 
		{
		case 1: //Option 1: Create an account (NEED TO SIMPLIFY THIS WITH SUB MENU)
			system("cls");
			cout << "------------------------------------------------------------" << endl;

			if (totalCustomerCount == 0) //If there are no customers in the system, instantly make a new customer
			{
				cout << "Please enter the following information for the new customer: " << endl;
				cout << "Enter customer first name: ";
				cin >> fname;
				cout << "Enter customer last name: ";
				cin >> lname;
				do //Ensure there are no duplicates
				{
					duplicateInfo = false;
					cout << "Enter customer address: ";
					cin.ignore();
					getline(cin, address);
					for (int i = 0; i < totalCustomerCount; i++)
					{
						if (address == customerList[i].getAddress())
						{
							duplicateInfo = true;
							cout << "Error: Duplicate address already exists." << endl;
							break;
						}
					}
				} while (duplicateInfo);
				do //Ensure there are no duplicates
				{
					duplicateInfo = false;
					cout << "Enter customer phone number (digits only): ";
					cin >> phoneNumber;
					for (int i = 0; i < totalCustomerCount; i++)
					{
						if (phoneNumber == customerList[i].getPhone())
						{
							duplicateInfo = true;
							cout << "Error: Duplicate phone number already exists." << endl;
							break;
						}
					}
				} while (duplicateInfo);
				do //Ensure there are no duplicates
				{
					duplicateInfo = false;
					cout << "Enter customer email: ";
					cin >> email;
					for (int i = 0; i < totalCustomerCount; i++)
					{
						if (email == customerList[i].getEmail())
						{
							duplicateInfo = true;
							cout << "Error: Duplicate email already exists." << endl;
							break;
						}
					}
				} while (duplicateInfo);
				customerList[totalCustomerCount].setAll(fname, lname, address, phoneNumber, email);
				cout << "Customer successfully added to system." << endl;
				totalCustomerCount++;
				customerFound = true;
			}
			else
			{
				cout << "Is the user an existing customer? (Y/N): "; //If there are customers in the system, ask if the user is an existing customer
				cin >> existingOpt;
				while (existingOpt != 'Y' && existingOpt != 'y' && existingOpt != 'N' && existingOpt != 'n') //Input validation
				{
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
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
					cout << "Enter customer last name: ";
					cin >> lname;
					do //Ensure there are no duplicates
					{
						duplicateInfo = false;
						cout << "Enter customer address: ";
						cin.ignore();
						getline(cin, address);
						for (int i = 0; i < totalCustomerCount; i++)
						{
							if (address == customerList[i].getAddress())
							{
								duplicateInfo = true;
								cout << "Error: Duplicate address already exists." << endl;
								break;
							}
						}
					} while (duplicateInfo);
					do //Ensure there are no duplicates
					{
						duplicateInfo = false;
						cout << "Enter customer phone number (digits only): ";
						cin >> phoneNumber;
						for (int i = 0; i < totalCustomerCount; i++)
						{
							if (phoneNumber == customerList[i].getPhone())
							{
								duplicateInfo = true;
								cout << "Error: Duplicate phone number already exists." << endl;
								break;
							}
						}
					} while (duplicateInfo);
					do //Ensure there are no duplicates
					{
						duplicateInfo = false;
						cout << "Enter customer email: ";
						cin >> email;
						for (int i = 0; i < totalCustomerCount; i++)
						{
							if (email == customerList[i].getEmail())
							{
								duplicateInfo = true;
								cout << "Error: Duplicate email already exists." << endl;
								break;
							}
						}
					} while (duplicateInfo);
					customerList[totalCustomerCount].setAll(fname, lname, address, phoneNumber, email);
					cout << "Customer successfully added to system." << endl;
					totalCustomerCount++;
					customerFound = true;
				}
				else //If the user is an existing customer, enter their credentials
				{
					do
					{
						cout << "----------------------------------------" << endl;
						cout << "Please enter the following credentials:" << endl;
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
								break;
							}
						}

						if (customerFound == false)
						{
							cout << "Error: Customer does not exist or credentials are wrong." << endl; //If customer isn't found, try again or exit
							cout << "Press 1 to try again or 2 to return to main menu: ";
							cin >> menuReturnOpt;
							while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
							{
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
								}
								cout << "Invalid option." << endl;
								cout << "Press 1 to try again or 2 to return to main menu: ";
								cin >> menuReturnOpt;
							}
							if (menuReturnOpt == 2)
							{
								break;
							}
						}
					} while (customerFound == false);
				}
			}

			if (customerFound)
			{
				cout << "------------------------------------------------------" << endl; //Account creation selection
				cout << "Customer found." << endl;
				cout << "Select which type of account you would like to create: " << endl;
				cout << "1. Checking account" << endl;
				cout << "2. Saving account" << endl;
				cin >> subMenuOpt;

				while (subMenuOpt < 1 || subMenuOpt > 2) //Input validation
				{
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "Invalid option. Please enter an option 1-2: ";
					cin >> subMenuOpt;
				}

				if (subMenuOpt == 1) 
				{
					cout << "-----------------------------------------------" << endl;
					cout << "Enter a name for this account: ";
					cin.ignore();
					getline(cin, accName);
					checkingAccList[checkingAccIndex].setAll((checkingAccIndex + 1), 0, &customerList[customerIndex], accName, overdraftLimit); //Checking account creation
					cout << "You have successfully created a saving account named " << "\"" << accName << "\"." << endl;
					checkingAccIndex++;
				}
				else
				{
					cout << "-------------------------------------------------" << endl;
					cout << "Enter a name for this account: ";
					cin.ignore();
					getline(cin, accName);
					savingAccList[savingAccIndex].setAll((savingAccIndex + 1), 0, 0, 0, &customerList[customerIndex], accName, interestRate); //Saving account creation
					cout << "You have successfully created a saving account named " << "\"" << accName << "\"." << endl;
					savingAccIndex++;
				}

				cout << "Press any key to return to menu: ";
				cin.ignore();
				cin.get();
			}
			customerFound = false; //Reset flag

			break;
		case 2: //Option 2: Modify or delete accounts (WIP)
			system("cls");
			cout << "---------------------------------------" << endl;

			if (totalCustomerCount == 0) //If there are no existing customers, exit
			{
				cout << "There are no accounts to modify/delete." << endl;
			}
			else
			{
				do
				{
					cout << "Please enter the following credentials:" << endl; //Credentials
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
							break;
						}
					}

					if (customerFound == false)
					{
						cout << "Error: Customer does not exist or credentials are wrong." << endl; //If customer isn't found, try again or exit
						cout << "Press 1 to try again or 2 to return to main menu: ";
						cin >> menuReturnOpt;
						while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							cout << "Invalid option." << endl;
							cout << "Press 1 to try again or 2 to return to main menu: ";
							cin >> menuReturnOpt;
						}
						if (menuReturnOpt == 2)
						{
							break;
						}
					}
				} while (customerFound == false);

				if (customerFound) 
				{
					system("cls");
					cout << "-------------------------------------------" << endl; //Modification sub-menu
					cout << "Customer found." << endl;
					cout << "Please select one of the following options:" << endl;
					cout << "1. Deposit" << endl;
					cout << "2. Withdraw" << endl;
					cout << "3. Transfer" << endl;
					cout << "4. Delete an account" << endl;
					cout << "5. Return to main menu" << endl;
					cin >> subMenuOpt;

					while (subMenuOpt < 1 || subMenuOpt > 5) //Input validation
					{
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
						cout << "Invalid option." << endl;
						cout << "Please select an option 1-5: ";
						cin >> subMenuOpt;
					}

					if (subMenuOpt == 1) //Deposit money
					{
						system("cls");
						cout << "Select which type of account to deposit from: " << endl; //Checking/Saving selection
						cout << "1. Checking" << endl;
						cout << "2. Saving" << endl;
						cin >> modifyOpt;
						while (modifyOpt < 1 || modifyOpt > 2) //Input validation
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							cout << "Invalid option." << endl;
							cout << "Please select an option 1-2: ";
							cin >> modifyOpt;
						}

						if (modifyOpt == 1)
						{
							system("cls");
							cout << "Select an account to deposit from: " << endl << endl; //Display checking accounts
							cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl;
							cout << "--------------------------------------------------------------" << endl;
							for (int i = 0; i < checkingAccIndex; i++)
							{
								cout << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
							}
							cout << "This part is under construction, please come back later." << endl << endl;
							cout << "Press any key to return to menu: ";
							cin.ignore();
							cin.get();
						}
					}
				}
			}
			customerFound = false;
			

			break;
		case 3: //Option 3: View personal account info
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
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
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

