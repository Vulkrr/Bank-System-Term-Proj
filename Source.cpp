#include "Customer.h"
#include "Account.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
#include "MiscFunctions.h"
#include <iomanip>
#include <vector>
using namespace std;

//Need to display account ID in some parts
//Need to remove checking/saving selection sub-menu and instead just display all of them per transaction

int main()
{
	//Bank limits
	const double interestRate = 1.02, overdraftLimit = 500, accNameLimit = 30;

	//Array limits
	const int customerLimit = 10, checkingAccLimit = 30, savingAccLimit = 30;

	//Arrays
	Customer customerList[customerLimit];
	CheckingAccount checkingAccList[checkingAccLimit];
	SavingAccount savingAccList[savingAccLimit];

	//Transaction history vector
	vector<Transaction> transactionList;

	//Customer pointer
	Customer* customerPtr = nullptr;

	//Counters/Indexes
	int totalCustomerCount = 0, customerIndex = 0,
		checkingAccCount = 0, checkingAccIndex = 0,
		savingAccCount = 0, savingAccIndex = 0,
		transferPullIndex = 0, transferPushIndex = 0,
		transactionCount = 0;

	//Flags
	bool customerFound = false, accFound = false, duplicateInfo = false, hasCheckingAcc = false, hasSavingAcc = false, hasTransactions = false;

	//Option inputs
	int mainMenuOpt, subMenuOpt, accTypeOpt, menuReturnOpt = 2;
	char confirmOpt;

	//Info inputs
	string fname, lname, address, email, phoneNumber, accName;

	//Amount inputs
	double depositAmnt, withdrawAmnt, transferAmnt;

	//Misc
	int uniqueID = 800;

	do
	{
		system("cls");
		cout << "========================BANK TELLER MENU========================" << endl << endl; //MAIN MENU
		cout << "----------------------------------------------------------------" << endl;
		cout << "1. Create an account" << endl;
		cout << "2. Make a transaction" << endl;
		cout << "3. Modify or delete accounts" << endl;
		cout << "4. View personal customer information" << endl;
		cout << "5. View all customers" << endl;
		cout << "6. Apply interest to a customer" << endl;
		cout << "7. Exit program" << endl;
		cout << "----------------------------------------------------------------" << endl << endl;
		cout << "================================================================" << endl;
		cout << "Please select one of the above options: ";
		cin >> mainMenuOpt;
		while (mainMenuOpt < 1 || mainMenuOpt > 7) //Input validation
		{
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cout << "Invalid option. Please enter an option 1-5: ";
			cin >> mainMenuOpt;
		}

		switch (mainMenuOpt)
		{
		case 1: //OPTION 1: CREATE AN ACCOUNT
			system("cls");

			cout << "========================BANK TELLER MENU========================" << endl << endl;
			cout << "----------------------------------------------------------------" << endl;
			cout << "1. Create a new customer profile" << endl;
			cout << "2. Create an account for an existing customer" << endl;
			cout << "3. Return to main menu" << endl;
			cout << "----------------------------------------------------------------" << endl << endl;
			cout << "================================================================" << endl;
			cout << "Please select one of the above options: ";
			cin >> subMenuOpt;
			while (subMenuOpt < 1 || subMenuOpt > 3) //Input validation
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << "Error: Invalid option. Please enter an option 1-2: ";
				cin >> subMenuOpt;
			}
			system("cls");
			
			if (subMenuOpt == 1) //CREATE A NEW CUSTOMER PROFILE
			{
				
				cout << "====================CREATE A CUSTOMER PROFILE===================" << endl << endl;
				
				cout << "Please enter the following information for the new customer:" << endl;
				cout << "----------------------------------------------------------------" << endl;
				cout << "Enter customer first name: ";
				cin >> fname;
				cout << "Enter customer last name: ";
				cin >> lname;
				cin.ignore();
				do //Ensure there are no duplicate addresses
				{
					duplicateInfo = false;
					cout << "Enter customer address: ";
					getline(cin, address);
					for (int i = 0; i < totalCustomerCount; i++)
					{
						if (address == customerList[i].getAddress())
						{
							duplicateInfo = true;
							cout << "----------------------------------------------------------------" << endl;
							cout << "Error: Duplicate address already exists." << endl;
							break;
						}
					}
				} while (duplicateInfo);
				do //Ensure there are no duplicate phone numbers
				{
					duplicateInfo = false;
					cout << "Enter customer phone number (digits only): ";
					cin >> phoneNumber;
					for (int i = 0; i < totalCustomerCount; i++)
					{
						if (phoneNumber == customerList[i].getPhone())
						{
							duplicateInfo = true;
							cout << "----------------------------------------------------------------" << endl;
							cout << "Error: Duplicate phone number already exists." << endl;
							break;
						}
					}
				} while (duplicateInfo);
				do //Ensure there are no duplicate emails
				{
					duplicateInfo = false;
					cout << "Enter customer email: ";
					cin >> email;
					for (int i = 0; i < totalCustomerCount; i++)
					{
						if (email == customerList[i].getEmail())
						{
							duplicateInfo = true;
							cout << "----------------------------------------------------------------" << endl;
							cout << "Error: Duplicate email already exists." << endl;
							break;
						}
					}
				} while (duplicateInfo);

				customerList[totalCustomerCount].setAll(fname, lname, address, phoneNumber, email); //Add customer to system
				system("cls");
				cout << "====================CREATE A CUSTOMER PROFILE===================" << endl << endl;
		
				cout << "Customer successfully added to system." << endl;
				cout << "----------------------------------------------------------------" << endl;
				totalCustomerCount++;
				cout << "Press any key to return to main menu: ";
				cin.ignore();
				cin.get();
			}
			else if (subMenuOpt == 2) //CREATE AN ACCOUNT FOR AN EXISTING CUSTOMER
			{
				if (totalCustomerCount > 0) //If there are no customers in the system, don't show this menu
				{
					do
					{
						system("cls");
						cout << "========================CREATE AN ACCOUNT=======================" << endl << endl;
						cout << "Please enter the following customer credentials:" << endl; //Get customer credentials (by last name and phone number)
						cout << "----------------------------------------------------------------" << endl;
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
								customerPtr = &customerList[customerIndex];
								break;
							}
						}

						system("cls");
						cout << "========================CREATE AN ACCOUNT=======================" << endl << endl;

						if (customerFound == false) //If customer isn't found, prompt user to try again or exit
						{		
							cout << "Error: Customer does not exist or was not found." << endl; 
							cout << "----------------------------------------------------------------" << endl;
							cout << "Press 1 to try again or 2 to return to main menu: ";
							cin >> menuReturnOpt;
							while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
							{
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
								}
								cout << "----------------------------------------------------------------" << endl;
								cout << "Error: Invalid option." << endl;
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
						do
						{
							system("cls");
							cout << "========================CREATE AN ACCOUNT=======================" << endl << endl;
							cout << "----------------------------------------------------------------" << endl; //Account creation selection
							cout << "1. Checking account" << endl;
							cout << "2. Saving account" << endl;
							cout << "----------------------------------------------------------------" << endl;
							cout << "Please select which type of account you would like to create: ";
							cin >> accTypeOpt;
							while (accTypeOpt < 1 || accTypeOpt > 2) //Input validation
							{
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
								}
								cout << "----------------------------------------------------------------" << endl;
								cout << "Error: Invalid option. Please enter an option 1-2: ";
								cin >> accTypeOpt;
							}
							cin.ignore();

							system("cls");
							cout << "========================CREATE AN ACCOUNT=======================" << endl << endl;

							cout << "----------------------------------------------------------------" << endl;
							if (accTypeOpt == 1) //CREATE A CHECKING ACCOUNT
							{
								do
								{
									duplicateInfo = false;
									cout << "Enter a name for this account: (No spaces or special characters) ";
									getline(cin, accName);
									while (accName.length() > accNameLimit) //Input validation
									{
										cout << "Error: Account name must be 30 characters or less. Please try again." << endl;
										cout << "Enter a name for this account: ";
										getline(cin, accName);
									}

									for (int i = 0; i < checkingAccCount; i++) //Ensure there are no checking account name duplicates
									{
										if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName()) 
										{
											duplicateInfo = true;
											cout << "----------------------------------------------------------------" << endl;
											cout << "Error: An account with this name already exists. Please use a unique name." << endl;
											break;
										}
									}

									for (int i = 0; i < savingAccCount; i++) //Ensure there are no saving account name duplicates
									{
										if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
										{
											duplicateInfo = true;
											cout << "----------------------------------------------------------------" << endl;
											cout << "Error: An account with this name already exists. Please use a unique name." << endl;
											break;
										}
									}
								} while (duplicateInfo);
								
								system("cls");
								cout << "========================CREATE AN ACCOUNT=======================" << endl << endl;

								checkingAccList[checkingAccCount].setAll(uniqueID, 0, 0, 0, 0, accName, &customerList[customerIndex], overdraftLimit); //Add a checking account to system
								cout << "----------------------------------------------------------------" << endl;
								cout << "You have successfully created a checking account named " << accName << "." << endl << endl;
								checkingAccCount++;
								uniqueID++;
							}
							else //CREATE A SAVING ACCOUNT
							{
								do
								{
									duplicateInfo = false;
									cout << "Enter a name for this account: ";
									getline(cin, accName);
									while (accName.length() > accNameLimit) //Input validation
									{
										cout << "----------------------------------------------------------------" << endl;
										cout << "Error: Account name must be 30 characters or less. Please try again." << endl;
										cout << "Enter a name for this account: ";
										getline(cin, accName);
									}

									for (int i = 0; i < checkingAccCount; i++) //Ensure there are no checking account name duplicates
									{
										if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
										{
											duplicateInfo = true;
											cout << "----------------------------------------------------------------" << endl;
											cout << "Error: An account with this name already exists. Please use a unique name." << endl;
											break;
										}
									}

									for (int i = 0; i < savingAccCount; i++) //Ensure there are no saving account name duplicates
									{
										if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
										{
											duplicateInfo = true;
											cout << "----------------------------------------------------------------" << endl;
											cout << "Error: An account with this name already exists. Please use a unique name." << endl;
											break;
										}
									}
								} while (duplicateInfo);

								system("cls");
								cout << "========================CREATE AN ACCOUNT=======================" << endl << endl;

								savingAccList[savingAccCount].setAll(uniqueID, 0, 0, 0, 0, accName, &customerList[customerIndex], interestRate); //Add a saving account to system
								cout << "----------------------------------------------------------------" << endl;
								cout << "You have successfully created a saving account named " << accName << "." << endl << endl;
								savingAccCount++;
								uniqueID++;
							}
							cout << "Press 1 to make a new account or 2 to return to main menu: ";
							cin >> menuReturnOpt;
							while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
							{
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
									cout << "----------------------------------------------------------------" << endl;
									cout << "Error: Invalid option. Please enter an option 1-2: ";
									cin >> menuReturnOpt;
								}
							}
						} while (menuReturnOpt == 1);
					}
					else
					{
						system("cls");
						cout << "========================CREATE AN ACCOUNT=======================" << endl << endl;
						cout << "----------------------------------------------------------------" << endl;
						cout << "Error: Customer does not exist or was not found." << endl;
					}
				}
				else
				{
					cout << "----------------------------------------------------------------" << endl;
					cout << "Error: There are no customers in the system." << endl << endl;
					cout << "Press any key to return to main menu: ";
					cin.ignore();
					cin.get();
				}
			}
			customerFound = false; //Reset flag

			break;
		case 2: //OPTION 2: MAKE A TRANSACTION
			if (totalCustomerCount > 0) //If there are no existing customers, exit this menu
			{
				do
				{
					system("cls");
					cout << "========================TRANSACTION MENU========================" << endl << endl;
					cout << "Please enter the following customer credentials:" << endl; //Get credentials
					cout << "----------------------------------------------------------------" << endl;
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
							customerPtr = &customerList[customerIndex];
							break;
						}
					}

					if (customerFound == false)  //If customer isn't found, prompt user to try again or exit
					{
						cout << "----------------------------------------------------------------" << endl;
						cout << "Error: Customer does not exist or credentials are wrong." << endl << endl;
						cout << "Press 1 to try again or 2 to return to main menu: ";
						cin >> menuReturnOpt;
						while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							cout << "----------------------------------------------------------------" << endl;
							cout << "Error: Invalid option. Please select an option 1-2: ";
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
					for (int i = 0; i < checkingAccCount; i++) //Ensure the customer has checking accounts
					{
						if (customerPtr == checkingAccList[i].getCustomerInfo())
						{
							hasCheckingAcc = true;
							checkingAccIndex = i;
							break;
						}
					}

					for (int i = 0; i < savingAccCount; i++) //Ensure the customer has saving accounts
					{
						if (customerPtr == savingAccList[i].getCustomerInfo())
						{
							hasSavingAcc = true;
							savingAccIndex = i;
							break;
						}
					}
				
					if (hasCheckingAcc || hasSavingAcc)
					{
						do
						{		
							system("cls"); 
							cout << "========================TRANSACTION MENU========================" << endl << endl; //TRANSACTION SUB-MENU
							cout << "----------------------------------------------------------------" << endl;
							cout << "1. Deposit" << endl;
							cout << "2. Withdraw" << endl;
							cout << "3. Transfer" << endl;
							cout << "4. Take Loan" << endl;
							cout << "5. Return to main menu" << endl;
							cout << "----------------------------------------------------------------" << endl;
							cout << "Please select one of the above options: ";
							cin >> subMenuOpt;
							while (subMenuOpt < 1 || subMenuOpt > 5) //Input validation
							{
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
								}
								cout << "Error: Invalid option. Please select an option 1-5: ";
								cin >> subMenuOpt;
							}

							system("cls");
							if (subMenuOpt == 1) //SUB-OPTION 1: DEPOSIT 
							{
								cout << "=============================DEPOSIT============================" << endl << endl;  //Checking/Saving selection
								cout << "----------------------------------------------------------------" << endl;
								cout << "1. Checking" << endl;
								cout << "2. Saving" << endl;
								cout << "----------------------------------------------------------------" << endl;
								cout << "Select which type of account to deposit to: " << endl;
								cin >> accTypeOpt;
								while (accTypeOpt < 1 || accTypeOpt > 2) //Input validation
								{
									if (cin.fail())
									{
										cin.clear();
										cin.ignore(numeric_limits<streamsize>::max(), '\n');
									}
									cout << "----------------------------------------------------------------" << endl;
									cout << "Error: Invalid option. Please select an option 1-2: ";
									cin >> accTypeOpt;
								}

								system("cls");
								if (accTypeOpt == 1) //DEPOSIT TO CHECKING ACCOUNT
								{
									cout << "=============================DEPOSIT============================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; 
									cout << "----------------------------------------------------------------" << endl;

									for (int i = 0; i < checkingAccCount; i++) //Display checking accounts
									{
										if (customerPtr == checkingAccList[i].getCustomerInfo())
										{
											cout << left << setw(20) << checkingAccList[i].getID() << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
										}
									}
									cout << "----------------------------------------------------------------" << endl;
									cout << "Enter the name of the account to deposit to: ";
									cin.ignore();
									getline(cin, accName);

									for (int i = 0; i < checkingAccCount; i++) //Find a name match for the account
									{
										if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
										{
											accFound = true;
											checkingAccIndex = i;
											break;
										}
									}

									system("cls");
									cout << "=============================DEPOSIT============================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									if (accFound)
									{									
										cout << "Enter amount to deposit: ";
										cin >> depositAmnt;
										while (depositAmnt < 0) //Input validation
										{
											if (cin.fail())
											{
												cin.clear();
												cin.ignore(numeric_limits<streamsize>::max(), '\n');
											}
											cout << "----------------------------------------------------------------" << endl;
											cout << "Error: Invalid amount. Please try again." << endl;
											cout << "Enter amount to deposit: ";
											cin >> depositAmnt;
										}

										system("cls");
										cout << "=============================DEPOSIT============================" << endl << endl;
										cout << "----------------------------------------------------------------" << endl;
										cout << "Are you sure you want to deposit $" << depositAmnt << " to " << accName << "? (Y/N): "; //Confirmation message
										cin >> confirmOpt;
										while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
										{
											cout << "----------------------------------------------------------------" << endl;
											cout << "Invalid response. Please selection an option Y/N: ";
											cin >> confirmOpt;
										}

										if (confirmOpt == 'Y' || confirmOpt == 'y')
										{
											system("cls");
											cout << "=============================DEPOSIT============================" << endl << endl;
											cout << "----------------------------------------------------------------" << endl;
											checkingAccList[checkingAccIndex].deposit(depositAmnt); //Deposit money
											cout << endl;

											Transaction t("Deposit", depositAmnt, checkingAccList[checkingAccIndex].getBal(), customerPtr); //Create a new transaction object (for transaction history)
											transactionList.push_back(t); //Add the object to transaction list
											transactionCount++;
										}
									}
									else
									{
										cout << "Error: Account does not exist or was not found." << endl;
									}
								}
								else //DEPOSIT TO SAVING ACCOUNT
								{
									cout << "=============================DEPOSIT============================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl;
									cout << "----------------------------------------------------------------" << endl;

									for (int i = 0; i < savingAccCount; i++) //Display saving accounts
									{
										if (customerPtr == savingAccList[i].getCustomerInfo())
										{
											cout << left << setw(20) << savingAccList[i].getID() << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
										}
									}
									cout << "----------------------------------------------------------------" << endl;
									cout << "Enter the name of the account to deposit to: ";  //Enter the name of saving account
									cin >> accName;

									for (int i = 0; i < savingAccCount; i++) //Find a name match for the account
									{
										if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
										{
											accFound = true;
											savingAccIndex = i;
											break;
										}
									}
								
									system("cls");
									cout << "=============================DEPOSIT============================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									if (accFound)
									{									
										cout << "Enter amount to deposit: ";
										cin >> depositAmnt;
										while (depositAmnt < 0) //Input validation
										{
											if (cin.fail())
											{
												cin.clear();
												cin.ignore(numeric_limits<streamsize>::max(), '\n');
											}
											cout << "----------------------------------------------------------------" << endl;
											cout << "Error: Invalid amount. Please try again." << endl;
											cout << "Enter amount to deposit: ";
											cin >> depositAmnt;
										}

										system("cls");
										cout << "=============================DEPOSIT============================" << endl << endl;
										cout << "----------------------------------------------------------------" << endl;
										cout << "Are you sure you want to deposit $" << depositAmnt << " to \"" << accName << "\"? (Y/N): "; //Confirmation message
										cin >> confirmOpt;
										while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
										{
											cout << "Invalid response. Please selection an option Y/N: ";
											cin >> confirmOpt;
										}

										if (confirmOpt == 'Y' || confirmOpt == 'y')
										{
											cout << "=============================DEPOSIT============================" << endl << endl;
											cout << "----------------------------------------------------------------" << endl;
											savingAccList[savingAccIndex].deposit(depositAmnt); //Deposit money
											cout << endl;
											Transaction t("Deposit", depositAmnt, savingAccList[savingAccIndex].getBal(), customerPtr); //Create a new transaction object (for transaction history)
											transactionList.push_back(t); //Add the object to transaction list
											transactionCount++;
										}
									}
									else
									{
										cout << "Error: Account does not exist or was not found." << endl;
									}
								}
							}
							else if (subMenuOpt == 2) //SUB-OPTION 2: WITHDRAW
							{
								cout << "=============================WITHDRAW===========================" << endl << endl;
								cout << "----------------------------------------------------------------" << endl;
								cout << "1. Checking" << endl;
								cout << "2. Saving" << endl;
								cout << "----------------------------------------------------------------" << endl;
								cout << "Select which type of account to withdraw from: " << endl;
								cin >> accTypeOpt;
								while (accTypeOpt < 1 || accTypeOpt > 2) //Input validation
								{
									if (cin.fail())
									{
										cin.clear();
										cin.ignore(numeric_limits<streamsize>::max(), '\n');
									}
									cout << "Invalid option." << endl;
									cout << "Please select an option 1-2: ";
									cin >> accTypeOpt;
								}

								system("cls");
								if (accTypeOpt == 1) //WITHDRAW FROM CHECKING
								{									
									cout << "=============================WITHDRAW===========================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display checking accounts
									cout << "----------------------------------------------------------------" << endl;
									for (int i = 0; i < checkingAccCount; i++) //Only display the customer's accounts
									{
										if (customerPtr == checkingAccList[i].getCustomerInfo())
										{
											cout << left << setw(20) << checkingAccList[i].getID() << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
										}
									}
									cout << "--------------------------------------------------------------" << endl;
									cout << "Enter the name of the account to withdraw from: ";
									cin.ignore();
									getline(cin, accName);

									for (int i = 0; i < checkingAccCount; i++) //Find a name match for the account
									{
										if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
										{
											accFound = true;
											checkingAccIndex = i;
											break;
										}
									}
									cout << "--------------------------------------------------------------" << endl;

									system("cls");
									cout << "=============================WITHDRAW===========================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									if (accFound)
									{										
										cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display selected checking account
										cout << "----------------------------------------------------------------" << endl;
										cout << left << setw(20) << checkingAccList[checkingAccIndex].getID() << left << setw(40) << checkingAccList[checkingAccIndex].getAccName() << left << setw(20) << checkingAccList[checkingAccIndex].getBal() << endl;
										cout << "----------------------------------------------------------------" << endl;
										cout << "Enter amount to withdraw: ";
										cin >> withdrawAmnt;
										while (withdrawAmnt < 0) //Input validation
										{
											if (cin.fail())
											{
												cin.clear();
												cin.ignore(numeric_limits<streamsize>::max(), '\n');
											}
											cout << "----------------------------------------------------------------" << endl;
											cout << "Error: Invalid amount. Please try again." << endl;
											cout << "Enter amount to withdraw: ";
											cin >> withdrawAmnt;
										}

										system("cls");
										cout << "=============================WITHDRAW===========================" << endl << endl;
										cout << "----------------------------------------------------------------" << endl;
										cout << "Are you sure you want to withdraw $" << withdrawAmnt << " from " << accName << "? (Y/N): "; //Withdrawal confirmation
										cin >> confirmOpt;
										while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
										{
											cout << "Invalid response. Please selection an option Y/N: ";
											cin >> confirmOpt;
										}

										if (confirmOpt == 'Y' || confirmOpt == 'y')
										{
											system("cls");
											cout << "=============================WITHDRAW===========================" << endl << endl;
											cout << "----------------------------------------------------------------" << endl;
											checkingAccList[checkingAccIndex].withdraw(withdrawAmnt); //Withdraw money
											cout << endl;

											Transaction t("Withdrawal", withdrawAmnt, checkingAccList[checkingAccIndex].getBal(), customerPtr); //Create a new transaction object (for transaction history)
											transactionList.push_back(t); //Add the object to transaction list
											transactionCount++;
										}
									}
									else
									{
										cout << "Error: Account does not exist or was not found." << endl;
									}
								}
								else //WITHDRAW FROM SAVING
								{
									cout << "=============================WITHDRAW===========================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display saving accounts
									cout << "----------------------------------------------------------------" << endl;
									for (int i = 0; i < savingAccCount; i++) //Only display the customer's accounts
									{
										if (customerPtr == checkingAccList[i].getCustomerInfo())
										{
											cout << left << setw(20) << savingAccList[i].getID() << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
										}
									}
									cout << "--------------------------------------------------------------" << endl;
									cout << "Enter the name of the account to withdraw from: ";
									cin.ignore();
									getline(cin, accName);

									for (int i = 0; i < savingAccCount; i++) //Find a name match for the account
									{
										if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
										{
											accFound = true;
											savingAccIndex = i;
											break;
										}
									}

									system("cls");
									cout << "=============================WITHDRAW===========================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									if (accFound)
									{
										
										cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display selected checking account
										cout << "----------------------------------------------------------------" << endl;
										cout << left << setw(20) << savingAccList[savingAccIndex].getID() << left << setw(40) << savingAccList[savingAccIndex].getAccName() << left << setw(20) << savingAccList[savingAccIndex].getBal() << endl;
										cout << "----------------------------------------------------------------" << endl;
										cout << "Enter amount to withdraw: ";
										cin >> withdrawAmnt;
										while (withdrawAmnt < 0) //Input validation
										{
											if (cin.fail())
											{
												cin.clear();
												cin.ignore(numeric_limits<streamsize>::max(), '\n');
											}
											cout << "----------------------------------------------------------------" << endl;
											cout << "Error: Invalid amount. Please try again." << endl;
											cout << "Enter amount to withdraw: ";
											cin >> withdrawAmnt;
										}

										system("cls");
										cout << "=============================WITHDRAW===========================" << endl << endl;										
										cout << "----------------------------------------------------------------" << endl;
										cout << "Are you sure you want to withdraw $" << withdrawAmnt << " from " << accName << "? (Y/N): "; //Withdrawal confirmation
										cin >> confirmOpt;
										while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
										{
											cout << "Invalid response. Please selection an option Y/N: ";
											cin >> confirmOpt;
										}

										if (confirmOpt == 'Y' || confirmOpt == 'y')
										{
											system("cls");
											cout << "=============================WITHDRAW===========================" << endl << endl;
											cout << "----------------------------------------------------------------" << endl;
											savingAccList[savingAccIndex].withdraw(withdrawAmnt); //Withdraw money
											cout << endl;

											Transaction t("Withdrawal", withdrawAmnt, savingAccList[savingAccIndex].getBal(), customerPtr); //Create a new transaction object (for transaction history)
											transactionList.push_back(t); //Add the object to transaction list
											transactionCount++;
										}
									}
									else
									{
										cout << "Error: Account does not exist or was not found." << endl;
									}
								}
							}
							else if (subMenuOpt == 3) //SUB-OPTION 3: TRANSFER
							{
								cout << "=============================TRANSFER===========================" << endl << endl; 
								cout << "----------------------------------------------------------------" << endl;
								int generalAccCount = 0;

								for (int i = 0; i < generalAccCount; i++) //Ensure that the customer has at least 2 accounts to make transfers
								{
									if (customerPtr == checkingAccList[i].getCustomerInfo())
									{
										generalAccCount++;
										break;
									}

									if (customerPtr == savingAccList[i].getCustomerInfo())
									{
										generalAccCount++;
										break;
									}
								}
								
								if (generalAccCount >= 2)
								{														
									cout << "1. Checking" << endl;
									cout << "2. Saving" << endl;
									cout << "----------------------------------------------------------------" << endl;
									cout << "Select which type of account to transfer from: " << endl; //Transfer pull selection
									cin >> accTypeOpt;
									while (accTypeOpt < 1 || accTypeOpt > 2) //Input validation
									{
										if (cin.fail())
										{
											cin.clear();
											cin.ignore(numeric_limits<streamsize>::max(), '\n');
										}
										cout << "Invalid option." << endl;
										cout << "Please select an option 1-2: ";
										cin >> accTypeOpt;
									}

									system("cls");
									cout << "=============================TRANSFER===========================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									if (accTypeOpt == 1) //TRANSFER FROM CHECKING
									{
										cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; 
										cout << "----------------------------------------------------------------" << endl;
										for (int i = 0; i < checkingAccCount; i++) //Display checking accounts
										{
											if (customerPtr == checkingAccList[i].getCustomerInfo())
											{
												cout << left << setw(20) << checkingAccList[i].getID() << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
											}
										}
										cout << "----------------------------------------------------------------" << endl;
										cout << "Enter the name of the account to transfer from: ";
										cin.ignore();
										getline(cin, accName);

										for (int i = 0; i < checkingAccCount; i++) //Find a name match for the account
										{
											if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
											{
												accFound = true;
												transferPullIndex = i;
												break;
											}
										}

										system("cls");
										cout << "=============================TRANSFER===========================" << endl << endl;
										cout << "----------------------------------------------------------------" << endl;
										if (accFound)
										{											
											cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display selected checking account
											cout << "-------------------------------------------------------------------------------------" << endl;
											cout << left << setw(20) << checkingAccList[transferPullIndex].getID() << left << setw(40) << checkingAccList[transferPullIndex].getAccName() << left << setw(20) << checkingAccList[transferPullIndex].getBal() << endl;
											cout << "-------------------------------------------------------------------------------------" << endl;
											cout << "Enter amount to transfer: ";
											cin >> transferAmnt;
											while (transferAmnt > checkingAccList[transferPullIndex].getBal()) //Funds validation
											{
												cout << "----------------------------------------------------------------" << endl;
												cout << "Error: Not enough funds in account. Please try again." << endl;
												cout << "Enter amount to transfer: ";
												cin >> transferAmnt;
											}
											while (transferAmnt < 0) //Input validation
											{
												if (cin.fail())
												{
													cin.clear();
													cin.ignore(numeric_limits<streamsize>::max(), '\n');
												}
												cout << "----------------------------------------------------------------" << endl;
												cout << "Error: Invalid amount. Please try again." << endl;
												cout << "Enter amount to transfer: ";
												cin >> transferAmnt;
											}

											system("cls");
											cout << "=============================TRANSFER===========================" << endl << endl; //Transfer push selection
											cout << "----------------------------------------------------------------" << endl;											
											cout << "1. Checking" << endl;
											cout << "2. Saving" << endl;
											cout << "----------------------------------------------------------------" << endl;
											cout << "Select which type of account to transfer to: " << endl; 
											cin >> accTypeOpt;
											while (accTypeOpt < 1 || accTypeOpt > 2) //Input validation
											{
												if (cin.fail())
												{
													cin.clear();
													cin.ignore(numeric_limits<streamsize>::max(), '\n');
												}
												cout << "----------------------------------------------------------------" << endl;
												cout << "Error: Invalid option. Please select an option 1-2: ";
												cin >> accTypeOpt;
											}

											system("cls");
											cout << "=============================TRANSFER===========================" << endl << endl; 
											cout << "----------------------------------------------------------------" << endl;
											if (accTypeOpt == 1) //TRANSFER FROM CHECKING TO CHECKING
											{								
												cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; 
												cout << "----------------------------------------------------------------" << endl;
												for (int i = 0; i < checkingAccCount; i++) //Display checking accounts
												{
													if (customerPtr == checkingAccList[i].getCustomerInfo())
													{
														cout << left << setw(20) << checkingAccList[i].getID() << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
													}
												}
												cout << "----------------------------------------------------------------" << endl;
												cout << "Enter the name of the account to transfer to: ";
												cin.ignore();
												getline(cin, accName);

												for (int i = 0; i < checkingAccCount; i++) //Find a name match for the account
												{
													if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
													{
														accFound = true;
														transferPushIndex = i;
														break;
													}
												}

												system("cls");
												cout << "=============================TRANSFER===========================" << endl << endl;
												cout << "----------------------------------------------------------------" << endl;
												cout << "Are you sure you want to transfer $" << transferAmnt << " from \"" << checkingAccList[transferPullIndex].getAccName() << "\" to \"" << checkingAccList[transferPushIndex].getAccName() << "\"? (Y/N): "; //Confirmation message
												cin >> confirmOpt;
												while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
												{
													cout << "Error: Invalid response. Please selection an option Y/N: ";
													cin >> confirmOpt;
												}

												if (confirmOpt == 'Y' || confirmOpt == 'y')
												{
													system("cls");
													cout << "=============================TRANSFER===========================" << endl << endl;
													cout << "----------------------------------------------------------------" << endl;
													checkingAccList[transferPullIndex].transfer(transferAmnt, checkingAccList[transferPushIndex]); //Transfer
													cout << endl;

													Transaction t("Transfer", transferAmnt, checkingAccList[transferPullIndex].getBal(), customerPtr); //Create a new transaction object
													transactionList.push_back(t); //Add the object to transaction list
													transactionCount++;
												}
											}
											else //TRANSFER FROM CHECKING TO SAVING
											{
												cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; 
												cout << "----------------------------------------------------------------" << endl;
												for (int i = 0; i < savingAccCount; i++) //Display saving accounts
												{
													if (customerPtr == savingAccList[i].getCustomerInfo())
													{
														cout << left << setw(20) << savingAccList[i].getID() << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
													}
												}
												cout << "----------------------------------------------------------------" << endl;
												cout << "Enter the name of the account to transfer to: ";
												cin >> accName;

												for (int i = 0; i < savingAccCount; i++) //Find a name match for the account
												{
													if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
													{
														accFound = true;
														transferPushIndex = i;
														break;
													}
												}
												system("cls");
												cout << "=============================TRANSFER===========================" << endl << endl;
												cout << "----------------------------------------------------------------" << endl;
												cout << "Are you sure you want to transfer $" << transferAmnt << " from \"" << checkingAccList[transferPullIndex].getAccName() << "\" to \"" << savingAccList[transferPushIndex].getAccName() << "\"? (Y/N): "; //Confirmation message
												cin >> confirmOpt;
												while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
												{
													cout << "Error: Invalid response. Please selection an option Y/N: ";
													cin >> confirmOpt;
												}

												if (confirmOpt == 'Y' || confirmOpt == 'y')
												{
													system("cls");
													cout << "=============================TRANSFER===========================" << endl << endl;
													
													cout << "----------------------------------------------------------------" << endl;
													checkingAccList[transferPullIndex].transfer(transferAmnt, checkingAccList[transferPushIndex]); //Transfer
													cout << endl;

													Transaction t("Transfer", transferAmnt, checkingAccList[transferPullIndex].getBal(), customerPtr); //Create a new transaction object
													transactionList.push_back(t); //Add the object to transaction list
													transactionCount++;
												}
											}
										}
										else
										{
											cout << "Error: Account does not exist or was not found." << endl;
										}
									}
									else //TRANSFER FROM SAVING
									{

										cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl;
										cout << "----------------------------------------------------------------" << endl;
										for (int i = 0; i < savingAccCount; i++) //Display saving accounts
										{
											if (customerPtr == savingAccList[i].getCustomerInfo())
											{
												cout << left << setw(20) << savingAccList[i].getID() << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
											}
										}
										cout << "----------------------------------------------------------------" << endl;
										cout << "Enter the name of the account to transfer from: ";
										cin.ignore();
										getline(cin, accName);

										for (int i = 0; i < savingAccCount; i++) //Find a name match for the account
										{
											if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
											{
												accFound = true;
												transferPullIndex = i;
												break;
											}
										}

										system("cls");
										cout << "=============================TRANSFER===========================" << endl << endl;
										cout << "----------------------------------------------------------------" << endl;
										if (accFound)
										{
											cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display selected saving account
											cout << "-------------------------------------------------------------------------------------" << endl;
											cout << left << setw(20) << savingAccList[transferPullIndex].getID() << left << setw(40) << savingAccList[transferPullIndex].getAccName() << left << setw(20) << savingAccList[transferPullIndex].getBal() << endl;
											cout << "-------------------------------------------------------------------------------------" << endl;
											cout << "Enter amount to transfer: ";
											cin >> transferAmnt;
											while (transferAmnt > savingAccList[transferPullIndex].getBal()) //Funds validation
											{
												cout << "----------------------------------------------------------------" << endl;
												cout << "Error: Not enough funds in account. Please try again." << endl;
												cout << "Enter amount to transfer: ";
												cin >> transferAmnt;
											}
											while (transferAmnt < 0) //Input validation
											{
												if (cin.fail())
												{
													cin.clear();
													cin.ignore(numeric_limits<streamsize>::max(), '\n');
												}
												cout << "----------------------------------------------------------------" << endl;
												cout << "Error: Invalid amount. Please try again." << endl;
												cout << "Enter amount to transfer: ";
												cin >> transferAmnt;
											}

											system("cls");
											cout << "=============================TRANSFER===========================" << endl << endl; //Transfer push selection
											cout << "----------------------------------------------------------------" << endl;
											cout << "1. Checking" << endl;
											cout << "2. Saving" << endl;
											cout << "----------------------------------------------------------------" << endl;
											cout << "Select which type of account to transfer to: " << endl;
											cin >> accTypeOpt;
											while (accTypeOpt < 1 || accTypeOpt > 2) //Input validation
											{
												if (cin.fail())
												{
													cin.clear();
													cin.ignore(numeric_limits<streamsize>::max(), '\n');
												}
												cout << "----------------------------------------------------------------" << endl;
												cout << "Error: Invalid option. Please select an option 1-2: ";
												cin >> accTypeOpt;
											}

											system("cls");
											cout << "=============================TRANSFER===========================" << endl << endl;
											cout << "----------------------------------------------------------------" << endl;
											if (accTypeOpt == 1) //TRANSFER FROM SAVING TO CHECKING
											{
												cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl;
												cout << "----------------------------------------------------------------" << endl;
												for (int i = 0; i < checkingAccCount; i++) //Display checking accounts
												{
													if (customerPtr == checkingAccList[i].getCustomerInfo())
													{
														cout << left << setw(20) << checkingAccList[i].getID() << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
													}
												}
												cout << "----------------------------------------------------------------" << endl;
												cout << "Enter the name of the account to transfer to: ";
												cin.ignore();
												getline(cin, accName);

												for (int i = 0; i < checkingAccCount; i++) //Find a name match for the account
												{
													if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
													{
														accFound = true;
														transferPushIndex = i;
														break;
													}
												}

												system("cls");
												cout << "=============================TRANSFER===========================" << endl << endl;
												cout << "----------------------------------------------------------------" << endl;
												cout << "Are you sure you want to transfer $" << transferAmnt << " from \"" << checkingAccList[transferPullIndex].getAccName() << "\" to \"" << checkingAccList[transferPushIndex].getAccName() << "\"? (Y/N): "; //Confirmation message
												cin >> confirmOpt;
												while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
												{
													cout << "Error: Invalid response. Please selection an option Y/N: ";
													cin >> confirmOpt;
												}

												if (confirmOpt == 'Y' || confirmOpt == 'y')
												{
													system("cls");
													cout << "=============================TRANSFER===========================" << endl << endl;
													cout << "----------------------------------------------------------------" << endl;
													checkingAccList[transferPullIndex].transfer(transferAmnt, checkingAccList[transferPushIndex]); //Transfer
													cout << endl;

													Transaction t("Transfer", transferAmnt, checkingAccList[transferPullIndex].getBal(), customerPtr); //Create a new transaction object
													transactionList.push_back(t); //Add the object to transaction list
													transactionCount++;
												}
											}
											else //TRANSFER FROM SAVING TO SAVING
											{
												cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl;
												cout << "----------------------------------------------------------------" << endl;
												for (int i = 0; i < savingAccCount; i++) //Display saving accounts
												{
													if (customerPtr == savingAccList[i].getCustomerInfo())
													{
														cout << left << setw(20) << savingAccList[i].getID() << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
													}
												}
												cout << "----------------------------------------------------------------" << endl;
												cout << "Enter the name of the account to transfer to: ";
												cin >> accName;

												for (int i = 0; i < savingAccCount; i++) //Find a name match for the account
												{
													if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
													{
														accFound = true;
														transferPushIndex = i;
														break;
													}
												}
												system("cls");
												cout << "=============================TRANSFER===========================" << endl << endl;
												cout << "----------------------------------------------------------------" << endl;
												cout << "Are you sure you want to transfer $" << transferAmnt << " from \"" << checkingAccList[transferPullIndex].getAccName() << "\" to \"" << savingAccList[transferPushIndex].getAccName() << "\"? (Y/N): "; //Confirmation message
												cin >> confirmOpt;
												while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
												{
													cout << "Error: Invalid response. Please selection an option Y/N: ";
													cin >> confirmOpt;
												}

												if (confirmOpt == 'Y' || confirmOpt == 'y')
												{
													system("cls");
													cout << "=============================TRANSFER===========================" << endl << endl;
													cout << "----------------------------------------------------------------" << endl;
													checkingAccList[transferPullIndex].transfer(transferAmnt, checkingAccList[transferPushIndex]); //Transfer
													cout << endl;

													Transaction t("Transfer", transferAmnt, checkingAccList[transferPullIndex].getBal(), customerPtr); //Create a new transaction object
													transactionList.push_back(t); //Add the object to transaction list
													transactionCount++;
												}
											}
										}
										else
										{
											cout << "Error: Account does not exist or was not found." << endl;
										}
									}
								}
								else
								{
									cout << "-------------------------------------------------------------------------------------" << endl;
									cout << "Error: Customer must have at least 2 accounts to make transfers." << endl;
								}
							}
							else  //SUB-OPTION 4: LOAN (WIP)
							{
								cout << "==============================LOAN==============================" << endl << endl;
								cout << "----------------------------------------------------------------" << endl;
								cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display checking accounts
								cout << "----------------------------------------------------------------" << endl;
								for (int i = 0; i < checkingAccCount; i++) //Only display the customer's accounts
								{
									if (customerPtr == checkingAccList[i].getCustomerInfo())
									{
										cout << left << setw(20) << checkingAccList[i].getID() << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
									}
								}
								cout << "----------------------------------------------------------------" << endl;
								cout << "Enter the name of the account to apply a loan to: ";
								cin.ignore();
								getline(cin, accName);

								for (int i = 0; i < checkingAccCount; i++) //Find a name match for the account
								{
									if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
									{
										accFound = true;
										transferPushIndex = i;
										break;
									}
								}

								system("cls");
								cout << "==============================LOAN==============================" << endl << endl;
								cout << "----------------------------------------------------------------" << endl;
								if (accFound)
								{
									int loanOpt;
									double loan1 = 1000, loan2 = 25000, loan3 = 200000;
									cout << "1. $1000 " << endl;
									cout << "2. $25000" << endl;
									cout << "3. $200,000" << endl;
									cout << "----------------------------------------------------------------" << endl;
									cout << "Select one of the above options by entering the loan amount: ";
									cin >> loanOpt;
									while (loanOpt < 1 || loanOpt > 3) //Input validation
									{
										if (cin.fail())
										{
											cin.clear();
											cin.ignore(numeric_limits<streamsize>::max(), '\n');
										}
										cout << "----------------------------------------------------------------" << endl;
										cout << "Error: Invalid option. Please select an option 1-3: ";
										cin >> loanOpt;
									}

									system("cls");
									cout << "==============================LOAN==============================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									cout << "Are you sure you want to add loan" << loanOpt << " to " << checkingAccList[checkingAccIndex].getAccName() << "? (Y/N): ";
									cin >> confirmOpt;
									while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
									{
										cout << "----------------------------------------------------------------" << endl;
										cout << "Invalid response. Please selection an option Y/N: ";
										cin >> confirmOpt;
									}

									if (confirmOpt == 'Y' || confirmOpt == 'y')
									{
										cout << "----------------------------------------------------------------" << endl;
										cout << " Congrats your debt has grown! " << endl;
										if (loanOpt == 1)
										{
											checkingAccList[checkingAccIndex].deposit(loan1);
										}
										else if (loanOpt == 2)
										{
											checkingAccList[checkingAccIndex].deposit(loan2);
										}
										else if (loanOpt == 3)
										{
											checkingAccList[checkingAccIndex].deposit(loan3);
										}

										Transaction t("Loan", loanOpt, checkingAccList[checkingAccIndex].getBal(), customerPtr); //Create a new transaction object
										transactionList.push_back(t); //Add the object to transaction list
										transactionCount++; //Increase transaction counter
									}
								}
								else
								{
									cout << "Error: Account does not exist or was not found." << endl;
								}
							}
							cout << "----------------------------------------------------------------" << endl;
							cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
							cin >> menuReturnOpt;
							while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
							{
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
									cout << "----------------------------------------------------------------" << endl;
									cout << "Error: Invalid option. Please select an option 1-2: ";
									cin >> menuReturnOpt;
								}
							}

							if (menuReturnOpt == 2)
							{
								break;
							}
						} while (subMenuOpt != 5);
					}
					else
					{
						system("cls");
						cout << "========================TRANSACTION MENU========================" << endl << endl;
						cout << "----------------------------------------------------------------" << endl;
						cout << "Error: This customer has no accounts." << endl << endl;
						cout << "Press any key to return to menu: ";
						cin.ignore();
						cin.get();
					}
				}
			}
			else
			{
				system("cls");
				cout << "========================TRANSACTION MENU========================" << endl << endl;
				cout << "----------------------------------------------------------------" << endl;
				cout << "Error: There are no customers in the system." << endl << endl;
				cout << "Press any key to return to menu: ";
				cin.ignore();
				cin.get();		 
			}
			customerFound = false; //Reset flag

			break;
		case 3: //OPTION 3: MODIFY OR DELETE ACCOUNTS
			if (totalCustomerCount > 0) 
			{
				do
				{
					system("cls");
					cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
					cout << "----------------------------------------------------------------" << endl;
					cout << "Please enter the following credentials:" << endl; //Get credentials
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
							customerPtr = &customerList[customerIndex];
							break;
						}
					}

					if (customerFound == false)  //If customer isn't found, prompt user to try again or exit
					{
						cout << "----------------------------------------------------------------" << endl;
						cout << "Error: Customer does not exist or was not found." << endl << endl;
						cout << "Press 1 to try again or 2 to return to main menu: ";
						cin >> menuReturnOpt;
						while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							cout << "----------------------------------------------------------------" << endl;
							cout << "Error: Invalid option. Please select an option 1-2: ";
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
					for (int i = 0; i < checkingAccCount; i++) //Ensure the customer has checking accounts
					{
						if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
						{
							hasCheckingAcc = true;
							checkingAccIndex = i;
							break;
						}
					}

					for (int i = 0; i < savingAccCount; i++) //Ensure the customer has saving accounts
					{
						if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
						{
							hasSavingAcc = true;
							savingAccIndex = i;
							break;
						}
					}

					system("cls");
					cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl; //Display sub menu
					cout << "----------------------------------------------------------------" << endl; 
					cout << "1. Change an account name" << endl;
					cout << "2. Delete an account" << endl;
					cout << "----------------------------------------------------------------" << endl;
					cout << "Please select one of the above options: ";
					cin >> subMenuOpt;

					while (subMenuOpt < 1 || subMenuOpt > 2)
					{
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
						cout << "----------------------------------------------------------------" << endl;
						cout << "Invalid option. Please select an option 1-2: " << endl;
						cin >> subMenuOpt;
					}

					
					if (subMenuOpt == 1) //SUB-OPTION 1: CHANGE AN ACCOUNT NAME
					{		
						do
						{
							system("cls");
							cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;

							//Display all checking accounts
							cout << "-------------------------------" << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname() << "'s Checking Accounts--------------------------------" << endl;
							cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display checking accounts
							cout << "----------------------------------------------------------------" << endl;
							for (int i = 0; i < checkingAccCount; i++) //Only display the customer's accounts
							{
								if (customerPtr == checkingAccList[i].getCustomerInfo())
								{
									cout << left << setw(20) << checkingAccList[i].getID() << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
								}
							}
							cout << endl << endl;

							//Display all saving accounts
							cout << "-------------------------------" << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname() << "'s Saving Accounts--------------------------------" << endl;
							cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display saving accounts
							cout << "----------------------------------------------------------------" << endl;
							for (int i = 0; i < savingAccCount; i++) //Only display the customer's accounts
							{
								if (customerPtr == savingAccList[i].getCustomerInfo())
								{
									cout << left << setw(20) << savingAccList[i].getID() << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
								}
							}
							cout << "----------------------------------------------------------------" << endl;
							cout << "Enter the name of the account you would like to edit: ";
							cin.ignore();
							getline(cin, accName);

							bool checkingAccFound = false;
							bool savingAccFound = false;

							for (int i = 0; i < checkingAccCount; i++) //Find a name match for checking accounts
							{
								if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
								{
									checkingAccFound = true;
									checkingAccIndex = i;
									transferPushIndex = i;
									break;
								}
							}

							for (int i = 0; i < savingAccCount; i++) //Find a name match for saving accounts
							{
								if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
								{
									savingAccFound = true;
									savingAccIndex = i;
									transferPushIndex = i;
									break;
								}
							}

							system("cls");
							cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
							cout << "----------------------------------------------------------------" << endl;
							if (checkingAccFound)
							{
								cout << "Are you sure you want to edit " << accName << "? (Y/N): ";
								cin >> confirmOpt;
								while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
								{
									cout << "----------------------------------------------------------------" << endl;
									cout << "Invalid response. Please selection an option Y/N: ";
									cin >> confirmOpt;
								}

								if (confirmOpt == 'Y' || confirmOpt == 'y')
								{
									system("cls");
									cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									do
									{
										duplicateInfo = false;
										cout << "Enter a new name for this account: ";
										cin.ignore();
										getline(cin, accName);
										while (accName.length() >= accNameLimit) //Input validation
										{
											cout << "----------------------------------------------------------------" << endl;
											cout << "Error: Account name must be 30 characters or less. Please try again." << endl;
											cout << "Enter a new name for this account: ";
											getline(cin, accName);
										}

										for (int i = 0; i < checkingAccCount; i++) //Ensure there are no checking account name duplicates
										{
											if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
											{
												duplicateInfo = true;
												cout << "----------------------------------------------------------------" << endl;
												cout << "Error: An account with this name already exists. Please use a unique name." << endl;
												break;
											}
										}

										for (int i = 0; i < savingAccCount; i++) //Ensure there are no saving account name duplicates
										{
											if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
											{
												duplicateInfo = true;
												cout << "----------------------------------------------------------------" << endl;
												cout << "Error: An account with this name already exists. Please use a unique name." << endl;
												break;
											}
										}
									} while (duplicateInfo);

									system("cls");
									cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									checkingAccList[checkingAccIndex].setAccName(accName);
									cout << "Successfully renamed account to " << accName << "." << endl;
								}
							}
							else if (savingAccFound)
							{
								cout << "Are you sure you want to edit " << accName << "? (Y/N): ";
								cin >> confirmOpt;
								while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
								{
									cout << "----------------------------------------------------------------" << endl;
									cout << "Invalid response. Please selection an option Y/N: ";
									cin >> confirmOpt;
								}

								if (confirmOpt == 'Y' || confirmOpt == 'y')
								{
									system("cls");
									cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									do
									{
										duplicateInfo = false;
										cout << "Enter a new name for this account: ";
										cin.ignore();
										getline(cin, accName);
										while (accName.length() >= accNameLimit) //Input validation
										{
											cout << "----------------------------------------------------------------" << endl;
											cout << "Error: Account name must be 30 characters or less. Please try again." << endl;
											cout << "Enter a new name for this account: ";
											getline(cin, accName);
										}

										for (int i = 0; i < checkingAccCount; i++) //Ensure there are no checking account name duplicates
										{
											if (customerPtr == checkingAccList[i].getCustomerInfo() && accName == checkingAccList[i].getAccName())
											{
												duplicateInfo = true;
												cout << "----------------------------------------------------------------" << endl;
												cout << "Error: An account with this name already exists. Please use a unique name." << endl;
												break;
											}
										}

										for (int i = 0; i < savingAccCount; i++) //Ensure there are no saving account name duplicates
										{
											if (customerPtr == savingAccList[i].getCustomerInfo() && accName == savingAccList[i].getAccName())
											{
												duplicateInfo = true;
												cout << "----------------------------------------------------------------" << endl;
												cout << "Error: An account with this name already exists. Please use a unique name." << endl;
												break;
											}
										}
									} while (duplicateInfo);

									system("cls");
									cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									savingAccList[savingAccIndex].setAccName(accName);
									cout << "Successfully renamed account to " << accName << "." << endl;
								}
							}
							else
							{
								cout << "Error: Account does not exist or was not found." << endl;
							}

							cout << endl << "Press 1 to edit a new account or 2 to return to main menu: ";
							cin >> menuReturnOpt;
							while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
							{
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
								}
								cout << "Error: Invalid option. Please select an option 1-2: ";
								cin >> menuReturnOpt;
							}
						} while (menuReturnOpt == 1);
					}
					else //SUB-OPTION 2: DELETE AN ACCOUNT
					{
						do
						{
							system("cls");
							cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
							cout << "----------------------------------------------------------------" << endl;
							cout << "1. Checking" << endl;
							cout << "2. Saving" << endl;
							cout << "----------------------------------------------------------------" << endl;
							cout << "Select which type of account to delete: " << endl; //Checking/Saving selection
							cin >> accTypeOpt;
							while (accTypeOpt < 1 || accTypeOpt > 2) //Input validation
							{
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
								}
								cout << "Error: Invalid option. Please select an option 1-2: ";
								cin >> accTypeOpt;
							}

							system("cls");
							cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
							if (accTypeOpt == 1) //DELETE A CHECKING ACCOUNT
							{
								if (hasCheckingAcc)
								{
									cout << "-------------------------------" << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname() << "'s Checking Accounts--------------------------------" << endl;
									cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; 
									cout << "----------------------------------------------------------------" << endl;
									for (int i = 0; i < checkingAccCount; i++) //Display checking accounts
									{
										if (customerPtr == checkingAccList[i].getCustomerInfo())
										{
											cout << left << setw(20) << checkingAccList[i].getID() << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
										}
									}
									cout << "----------------------------------------------------------------" << endl;
									cout << "Enter the name of the account you would like to delete: ";
									cin.ignore();
									getline(cin, accName);

									for (int i = 0; i < checkingAccCount; i++) //Find a name match for account
									{
										if (customerPtr == checkingAccList[i].getCustomerInfo())
										{
											accFound = true;
											checkingAccIndex = i;
											break;
										}
									}

									system("cls");
									cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									if (accFound)
									{
										cout << "Are you sure you want to delete " << accName << "\"? (Y/N): "; //Confirm account deletion
										cin >> confirmOpt;

										while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
										{
											cout << "----------------------------------------------------------------" << endl;
											cout << "Invalid response. Please selection an option Y/N: ";
											cin >> confirmOpt;
										}

										if (confirmOpt == 'Y' || confirmOpt == 'y') //Delete checking account
										{
											system("cls");
											cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
											cout << "----------------------------------------------------------------" << endl;
											cout << "Successfully deleted " << accName << "." << endl;

											if (checkingAccIndex < checkingAccCount - 1) //If the deleted account is not in the last index, move all the following accounts to fill the gap
											{
												for (int i = checkingAccIndex; i < checkingAccCount; i++)
												{
													checkingAccList[i].setAll(checkingAccList[i + 1].getID(), checkingAccList[i + 1].getWithdrawCount(), checkingAccList[i + 1].getDepositCount(),
														checkingAccList[i + 1].getTransferCount(), checkingAccList[i + 1].getBal(),
														checkingAccList[i + 1].getAccName(), checkingAccList[i + 1].getCustomerInfo(), checkingAccList[i + 1].getOverdraftLimit());
												}
											}
											else
											{
												checkingAccList[checkingAccIndex].setAll(0, 0, 0, 0, 0, "", nullptr, 0);
											}										
											checkingAccCount--;
										}
									}
									else
									{
										cout << "Error: Account does not exist or was not found." << endl;
									}
								}
								else
								{
									cout << "----------------------------------------------------------------" << endl;
									cout << "Error: This customer has no accounts." << endl;
								}
							}
							else //DELETE A SAVING ACCOUNT
							{
								if (hasSavingAcc)
								{
									cout << "-------------------------------" << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname() << "'s Saving Accounts--------------------------------" << endl;
									cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl;
									cout << "----------------------------------------------------------------" << endl;
									for (int i = 0; i < savingAccCount; i++) //Display saving accounts
									{
										if (customerPtr == savingAccList[i].getCustomerInfo())
										{
											cout << left << setw(20) << savingAccList[i].getID() << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
										}
									}
									cout << "----------------------------------------------------------------" << endl;
									cout << "Enter the name of the account you would like to delete: ";
									cin.ignore();
									getline(cin, accName);

									for (int i = 0; i < savingAccCount; i++) //Find a name match for account
									{
										if (customerPtr == savingAccList[i].getCustomerInfo())
										{
											accFound = true;
											savingAccIndex = i;
											break;
										}
									}

									system("cls");
									cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
									cout << "----------------------------------------------------------------" << endl;
									if (accFound)
									{
										cout << "Are you sure you want to delete " << accName << "\"? (Y/N): "; //Confirm account deletion
										cin >> confirmOpt;

										while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
										{
											cout << "----------------------------------------------------------------" << endl;
											cout << "Invalid response. Please selection an option Y/N: ";
											cin >> confirmOpt;
										}

										if (confirmOpt == 'Y' || confirmOpt == 'y') //Delete checking account
										{
											system("cls");
											cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
											cout << "----------------------------------------------------------------" << endl;
											cout << "Successfully deleted " << accName << "." << endl;

											if (savingAccIndex < savingAccCount - 1) //If the deleted account is not in the last index, move all the following accounts to fill the gap
											{
												for (int i = savingAccIndex; i < savingAccCount; i++)
												{
													savingAccList[i].setAll(savingAccList[i + 1].getID(), savingAccList[i + 1].getWithdrawCount(), savingAccList[i + 1].getDepositCount(),
														savingAccList[i + 1].getTransferCount(), savingAccList[i + 1].getBal(),
														savingAccList[i + 1].getAccName(), savingAccList[i + 1].getCustomerInfo(), savingAccList[i + 1].getInterestRate());
												}
											}
											else
											{
												savingAccList[savingAccIndex].setAll(0, 0, 0, 0, 0, "", nullptr, 0);
											}
											checkingAccCount--;
										}
									}
									else
									{
										cout << "Error: Account does not exist or was not found." << endl;
									}
								}
								else
								{
									cout << "----------------------------------------------------------------" << endl;
									cout << "Error: This customer has no accounts." << endl;
								}
							}
							cout << endl << "Press 1 to delete another account or 2 to return to main menu: ";
							cin >> menuReturnOpt;
							while (menuReturnOpt < 1 || menuReturnOpt > 2)
							{
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
								}
								cout << "----------------------------------------------------------------" << endl;
								cout << "Error: Invalid option. Please select an option 1-2: ";
								cin >> menuReturnOpt;
							}
						} while (menuReturnOpt == 1);
					}
				}
			}
			else
			{
				system("cls");
				cout << "===================MODIFY OR DELETE ACCOUNTS====================" << endl << endl;
				cout << "----------------------------------------------------------------" << endl;
				cout << "Error: There are no customers in the system." << endl << endl;
				cout << "Press any key to return to menu: ";
				cin.ignore();
				cin.get();				
			}

			break;
		case 4: //OPTION 4: VIEW PERSONAL ACCOUNT INFO
			if (totalCustomerCount > 0)
			{
				do
				{
					system("cls");
					cout << "==================VIEW PERSONAL CUSTOMER INFO===================" << endl << endl;
					cout << "Please enter the following customer credentials:" << endl; //Get credentials
					cout << "----------------------------------------------------------------" << endl;		
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
							customerPtr = &customerList[customerIndex];
							break;
						}
					}

					if (customerFound == false)  //If customer isn't found, prompt user to try again or exit
					{
						cout << "----------------------------------------------------------------" << endl;
						cout << "Error: Customer does not exist or credentials are wrong." << endl << endl;
						cout << "Press 1 to try again or 2 to return to main menu: ";
						cin >> menuReturnOpt;
						while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							cout << "----------------------------------------------------------------" << endl;
							cout << "Error: Invalid option. Please select an option 1-2: ";
							cin >> menuReturnOpt;
						}
						if (menuReturnOpt == 2)
						{
							break;
						}
					}
				} while (customerFound == false);

				if (customerFound == true) //If customer is found, show sub menu
				{
					system("cls");
					cout << "==================VIEW PERSONAL CUSTOMER INFO===================" << endl << endl;
					cout << "----------------------------------------------------------------" << endl;
					cout << "1. View general customer info" << endl;
					cout << "2. View transaction history" << endl;
					cout << "3. View account list" << endl;
					cout << "----------------------------------------------------------------" << endl;
					cout << "Select one of the above options: ";
					cin >> subMenuOpt;
					while (subMenuOpt < 1 || subMenuOpt > 3) //Input validation
					{
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(numeric_limits<streamsize>::max(), '\n');
						}
						cout << "----------------------------------------------------------------" << endl;
						cout << "Invalid option. Please select an option 1-3: " << endl;
						cin >> subMenuOpt;
					}

					for (int i = 0; i < checkingAccCount; i++) //Ensure the customer has checking accounts
					{
						if (customerPtr == checkingAccList[i].getCustomerInfo())
						{
							hasCheckingAcc = true;
							checkingAccIndex = i;
							break;
						}
					}

					for (int i = 0; i < savingAccCount; i++) //Ensure the customer has saving accounts
					{
						if (customerPtr == savingAccList[i].getCustomerInfo())
						{
							hasSavingAcc = true;
							savingAccIndex = i;
							break;
						}
					}

					if (subMenuOpt == 1) //SUB-OPTION 1: VIEW GENERAL CUSTOMER INFO
					{
						system("cls");
						cout << "======================GENERAL CUSTOMER INFO=====================" << endl << endl;
						cout << "----------------------------------------------------------------" << endl;

						if (hasCheckingAcc || hasSavingAcc) //If the customer has at least one account, view full info
						{
							savingAccList[savingAccIndex].printInfo();
						}
						else
						{
							customerList[customerIndex].printInfoFull();
							cout << "This customer has no accounts." << endl;
						}
					}
					else if (subMenuOpt == 2) //SUB-OPTION2: TRANSACTION HISTORY
					{
						system("cls");				
						cout << "=======================TRANSACTION HISTORY======================" << endl << endl;

						for (int i = 0; i < transactionCount; i++) //Ensure the customer has transactions
						{
							if (customerPtr == transactionList[i].getCustomerInfo())
							{
								hasTransactions = true;
								break;
							}
						}

						if (hasTransactions) //If the customer has transactions, display them
						{
							cout << "---------------------------------------------------------------" << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname() << "'s Transaction History" << "---------------------------------------------------------------" << endl << endl;
							cout << left << setw(20) << "Account ID" << left << setw(40) << "Account Name" << left << setw(20) << "Transaction Type" << left << setw(20) << "Amount" << left << setw(20) << "Snapshot Balance" << endl;
							cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
							for (int i = 0; i < transactionCount; i++)
							{
								if (customerPtr == transactionList[i].getCustomerInfo())
								{
									transactionList[i].printTransaction();
								}
							}
							cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
						}
						else
						{
							cout << "----------------------------------------------------------------" << endl;
							cout << "This customer has not made any transactions yet." << endl;
						}
					}
					else //SUB-OPTION 3: VIEW ACCOUNT LIST
					{
						system("cls");
						cout << "===========================ACCOUNT LIST=========================" << endl << endl;
					
						if (hasCheckingAcc)
						{
							//Display all checking accounts
							cout << "-------------------------------" << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname() << "'s Checking Accounts--------------------------------" << endl << endl;
							cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl;
							cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
							for (int i = 0; i < checkingAccCount; i++) //Only display the customer's accounts
							{
								if (customerPtr == checkingAccList[i].getCustomerInfo())
								{
									cout << left << setw(20) << checkingAccList[i].getID() << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
								}
							}
							cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
						}
						if (hasSavingAcc)
						{
							//Display all saving accounts
							cout << "-------------------------------" << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname() << "'s Saving Accounts--------------------------------" << endl;
							cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl;
							cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
							for (int i = 0; i < checkingAccCount; i++) //Only display the customer's accounts
							{
								if (customerPtr == checkingAccList[i].getCustomerInfo())
								{
									cout << left << setw(20) << checkingAccList[i].getID() << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
								}
							}
							cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
						}

						if (hasCheckingAcc == false && hasSavingAcc == false)
						{
							cout << "----------------------------------------------------------------" << endl;
							cout << "This customer has no accounts." << endl;
						}
					}
				}
			}
			else
			{
				system("cls");
				cout << "==================VIEW PERSONAL CUSTOMER INFO===================" << endl << endl;
				cout << "----------------------------------------------------------------" << endl;
				cout << "Error: There are no customers in the system." << endl;			
			}

			cout << endl << "Press any key to return to menu: ";
			cin.ignore();
			cin.get();

			break;
		case 5: //OPTION 5: VIEW ALL CUSTOMERS
			system("cls");
			cout << "=========================CUSTOMER LIST==========================" << endl << endl;	
			cout << "----------------------------------------------------------------" << endl;

			if (totalCustomerCount > 0) //If there are no customers in the system, exit this menu
			{
				cout << left << setw(20) << "First Name" << left << setw(20) << "Last Name" << left << setw(30) << "Address" << left << setw(20) << "Phone #" << left << setw(20) << "Email" << endl;
				cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
				for (int i = 0; i < totalCustomerCount; i++)
				{
					customerList[i].printInfoPartial();
				}
				cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
			}
			else
			{
				cout << "Error: There are no customers in the system." << endl;		
			}

			cout << "Press any key to return to menu: ";
			cin.ignore();
			cin.get();
			break;
		case 6: //OPTION 6: APPLY INTEREST	
			if (totalCustomerCount > 0) //If there are no customers in the system, exit this menu
			{
				do
				{
					system("cls");
					cout << "========================APPLY INTEREST==========================" << endl << endl;
					cout << "Please enter the following customer credentials:" << endl; //Get credentials
					cout << "----------------------------------------------------------------" << endl;	
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
							customerPtr = &customerList[customerIndex];
							break;
						}
					}

					if (customerFound == false)  //If customer isn't found, prompt user to try again or exit
					{
						cout << "----------------------------------------------------------------" << endl;
						cout << "Error: Customer does not exist or was not found." << endl;
						cout << "Press 1 to try again or 2 to return to main menu: ";
						cin >> menuReturnOpt;
						while (menuReturnOpt < 1 || menuReturnOpt > 2) //Input validation
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							cout << "----------------------------------------------------------------" << endl;
							cout << "Error: Invalid option. Please select an option 1-2: ";
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
					cout << "========================APPLY INTEREST==========================" << endl << endl;
					cout << "----------------------------------------------------------------" << endl;
					for (int i = 0; i < savingAccCount; i++) //Ensure the customer has saving accounts
					{
						if (customerPtr == savingAccList[i].getCustomerInfo())
						{
							hasSavingAcc = true;
							break;
						}
					}

					if (hasSavingAcc)
					{
						cout << "Are you sure you want to apply interest to " << customerList[customerIndex].getFname() << " " << customerList[customerIndex].getLname() << "'s savings? (Y/N): "; //Confirmation message
						cin >> confirmOpt;
						while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
						{
							cout << "----------------------------------------------------------------" << endl;
							cout << "Invalid response. Please selection an option Y/N: ";
							cin >> confirmOpt;
						}

						if (confirmOpt == 'Y' || confirmOpt == 'y') //Apply interest to saving accounts
						{
							for (int i = 0; i < savingAccCount; i++)
							{
								if (customerPtr == savingAccList[i].getCustomerInfo())
								{
									savingAccList[i].applyInterest();
								}
							}
						}
					}
					else
					{
						cout << "This customer has no savings to apply interest to." << endl;
					}
				}
			}
			else
			{
				system("cls");
				cout << "========================APPLY INTEREST==========================" << endl << endl;
				cout << "----------------------------------------------------------------" << endl;
				cout << "Error: There are no customers in the system." << endl;				
			}

			cout << endl << "Press any key to return to menu: ";
			cin.ignore();
			cin.get();
		}
	} while (mainMenuOpt != 7);

	cout << "Toodles." << endl;
	return 0;
}
