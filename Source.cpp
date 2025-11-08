#include "Customer.h"
#include "Account.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
#include "MiscFunctions.h"
#include <iomanip>
#include <vector>

int main() {

	//Array limits
	const int customerLimit = 10, checkingAccLimit = 5, savingAccLimit = 5;

	//Bank limits
	const double interestRate = 1.02, overdraftLimit = 50; 

	//Arrays
	Customer customerList[customerLimit];
	CheckingAccount checkingAccList[checkingAccLimit];
	SavingAccount savingAccList[savingAccLimit];

	//Transaction history vector (not implemented yet)
	vector<Transaction> transactionList;
	
	//Indexes/Counters
	int totalCustomerCount = 0, customerIndex = 0, 
		checkingAccCount = 0, checkingAccIndex = 0, 
		savingAccCount = 0, savingAccIndex = 0, 
		transferPullIndex = 0, transferPushIndex = 0, 
		transactionCount = 0;

	//Flags
	bool customerFound = false, duplicateInfo = false;

	//Option inputs
	int menuOpt, subMenuOpt, accTypeOpt, menuReturnOpt, checkingAccOpt, savingAccOpt; 
	char existingOpt, confirmOpt;

	//Info inputs
	string fname, lname, address, email, phoneNumber, accName; 

	//Amount inputs
	double depositAmnt, withdrawAmnt, transferAmnt;

	do
	{
		system("cls");
		cout << "======================================" << endl; //Main menu 
		cout << "Select one of the following options: " << endl;
		cout << "1. Create an account" << endl;
		cout << "2. Make a transaction" << endl;
		cout << "3. Modify or delete accounts" << endl;
		cout << "4. View personal account information" << endl;
		cout << "5. View all customers" << endl;
		cout << "6. Exit program" << endl;
		cin >> menuOpt;
		while (menuOpt < 1 || menuOpt > 6) //Input validation
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
		case 1: //OPTION 1: Create an account (NEED TO SIMPLIFY THIS WITH SUB MENU)
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
				cin >> accTypeOpt;

				while (accTypeOpt < 1 || accTypeOpt > 2) //Input validation
				{
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "Invalid option. Please enter an option 1-2: ";
					cin >> accTypeOpt;
				}

				if (accTypeOpt == 1)
				{
					cout << "-----------------------------------------------" << endl;
					cout << "Enter a name for this account: ";
					cin.ignore();
					getline(cin, accName);
					checkingAccList[checkingAccCount].setAll((checkingAccCount + 1), 0, &customerList[customerIndex], accName, overdraftLimit); //Checking account creation
					cout << "You have successfully created a saving account named " << "\"" << accName << "\"." << endl;
					checkingAccCount++;
				}
				else
				{
					cout << "-------------------------------------------------" << endl;
					cout << "Enter a name for this account: ";
					cin.ignore();
					getline(cin, accName);
					savingAccList[savingAccCount].setAll((savingAccCount + 1), 0, 0, 0, &customerList[customerIndex], accName, interestRate); //Saving account creation
					cout << "You have successfully created a saving account named " << "\"" << accName << "\"." << endl;
					savingAccCount++;
				}

				cout << "Press any key to return to menu: ";
				cin.ignore();
				cin.get();
			}
			customerFound = false; //Reset flag

			break;
		case 2: //OPTION 2: Make a transaction (WIP)
			system("cls");
			cout << "---------------------------------------" << endl;

			if (totalCustomerCount == 0) //If there are no existing customers, exit
			{
				cout << "Error: There are no customers in the system." << endl;
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
					cout << "Customer found." << endl;
					do
					{
						system("cls");
						cout << "-------------------------------------------" << endl; //Transaction sub-menu
						cout << "Please select one of the following options:" << endl;
						cout << "1. Deposit" << endl;
						cout << "2. Withdraw" << endl;
						cout << "3. Transfer" << endl;
						cout << "4. Return to main menu" << endl;
						cin >> subMenuOpt;

						while (subMenuOpt < 1 || subMenuOpt > 4) //Input validation
						{
							if (cin.fail())
							{
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							cout << "Invalid option." << endl;
							cout << "Please select an option 1-4: ";
							cin >> subMenuOpt;
						}

						if (subMenuOpt == 1) //DEPOSIT 
						{
							system("cls");
							cout << "Select which type of account to deposit from: " << endl; //Checking/Saving selection
							cout << "1. Checking" << endl;
							cout << "2. Saving" << endl;
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

							if (accTypeOpt == 1)
							{
								system("cls");

								cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display checking accounts
								cout << "--------------------------------------------------------------" << endl;
								for (int i = 0; i < checkingAccCount; i++)
								{
									cout << i + 1 << ". " << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
								}
								cout << "--------------------------------------------------------------" << endl;

								cout << "Select an account to deposit to: ";  //Select a checking account
								cin >> checkingAccOpt;
								while (checkingAccOpt < 1 || checkingAccOpt >= checkingAccCount) //Input validation
								{
									if (cin.fail())
									{
										cin.clear();
										cin.ignore(numeric_limits<streamsize>::max(), '\n');
									}
									cout << "Invalid option. Please select an option 1-" << checkingAccCount - 1 << ": ";
									cin >> checkingAccOpt;
								}

								checkingAccIndex = checkingAccOpt - 1;
								system("cls");
								cout << "Enter amount to deposit: "; //Enter deposit amount
								cin >> depositAmnt;

								while (depositAmnt < 0)
								{
									cout << "Error: Cannot deposit a negative number." << endl; //Input validation
									cout << "Enter amount to deposit: ";
									cin >> depositAmnt;
								}

								cout << "Are you sure you want to deposit $" << withdrawAmnt << " to \"" << checkingAccList[checkingAccIndex].getAccName() << "\"? (Y/N): ";
								cin >> confirmOpt;

								while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
								{
									cout << "Invalid response. Please selection an option Y/N: ";
									cin >> confirmOpt;
								}

								if (confirmOpt == 'Y' || confirmOpt == 'y')
								{
									savingAccList[savingAccIndex].setBal(savingAccList[savingAccIndex].getBal() - withdrawAmnt); //Deposit money
									cout << "Successfully withdrew $" << withdrawAmnt << " from \"" << savingAccList[savingAccIndex].getAccName() << "\"." << endl << endl;
									savingAccList[0].setWithdrawCount(savingAccList[0].getWithdrawCount() + 1); //Increase deposit counter
								}

								cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
								cin >> menuReturnOpt;
							}
							else
							{
								system("cls");

								cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display saving accounts
								cout << "--------------------------------------------------------------" << endl;
								for (int i = 0; i < savingAccCount; i++)
								{
									cout << i + 1 << ". " << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
								}
								cout << "--------------------------------------------------------------" << endl;

								cout << "Select an account to deposit from: ";  //Select a saving account
								cin >> savingAccOpt;
								while (savingAccOpt < 1 || savingAccOpt >= savingAccCount) //Input validation
								{
									if (cin.fail())
									{
										cin.clear();
										cin.ignore(numeric_limits<streamsize>::max(), '\n');
									}
									cout << "Invalid option. Please select an option 1-" << savingAccCount - 1 << ": ";
									cin >> savingAccOpt;
								}

								savingAccIndex = savingAccOpt - 1;
								system("cls");
								cout << "Enter amount to deposit: "; //Enter deposit amount
								cin >> depositAmnt;

								while (depositAmnt < 0)
								{
									cout << "Error: Cannot deposit a negative number." << endl; //Input validation
									cout << "Enter amount to deposit: ";
									cin >> depositAmnt;
								}

								cout << "Are you sure you want to deposit $" << withdrawAmnt << " to \"" << checkingAccList[checkingAccIndex].getAccName() << "\"? (Y/N): ";
								cin >> confirmOpt;

								while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
								{
									cout << "Invalid response. Please selection an option Y/N: ";
									cin >> confirmOpt;
								}

								if (confirmOpt == 'Y' || confirmOpt == 'y')
								{
									savingAccList[savingAccIndex].setBal(savingAccList[savingAccIndex].getBal() - withdrawAmnt); //Deposit money
									cout << "Successfully withdrew $" << withdrawAmnt << " from \"" << savingAccList[savingAccIndex].getAccName() << "\"." << endl << endl;
									savingAccList[0].setDepositCount(savingAccList[0].getDepositCount() + 1); //Increase deposit counter
								}

								cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
								cin >> menuReturnOpt;
							}
						}
						else if (subMenuOpt == 2) //WITHDRAW
						{
							system("cls");

							if (savingAccList[0].getBal() == 0)
							{
								cout << "Error: You are broke. There is no money to withdraw." << endl;
							}
							else
							{
								cout << "Select which type of account to withdraw from: " << endl; //Checking/Saving selection
								cout << "1. Checking" << endl;
								cout << "2. Saving" << endl;
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

								if (accTypeOpt == 1)
								{
									system("cls");

									cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display checking accounts
									cout << "--------------------------------------------------------------" << endl;
									for (int i = 0; i < checkingAccCount; i++)
									{
										cout << i + 1 << ". " << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
									}
									cout << "--------------------------------------------------------------" << endl;

									cout << "Select an account to withdraw from: ";  //Select a checking account
									cin >> checkingAccOpt;
									while (checkingAccOpt < 1 || checkingAccOpt >= checkingAccCount) //Input validation
									{
										if (cin.fail())
										{
											cin.clear();
											cin.ignore(numeric_limits<streamsize>::max(), '\n');
										}
										cout << "Invalid option. Please select an option 1-" << checkingAccCount - 1 << ": ";
										cin >> checkingAccOpt;
									}

									checkingAccIndex = checkingAccOpt - 1;
									system("cls");
									cout << "Enter amount to withdraw: "; //Enter withdraw amount
									cin >> withdrawAmnt;

									while (withdrawAmnt < 0)
									{
										cout << "Error: Cannot withdraw a negative number." << endl; //Input validation
										cout << "Enter amount to withdraw: ";
										cin >> withdrawAmnt;
									}

									cout << "Are you sure you want to withdraw $" << withdrawAmnt << " from \"" << checkingAccList[checkingAccIndex].getAccName() << "\"? (Y/N): ";
									cin >> confirmOpt;

									while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
									{
										cout << "Invalid response. Please selection an option Y/N: ";
										cin >> confirmOpt;
									}

									if (confirmOpt == 'Y' || confirmOpt == 'y')
									{
										checkingAccList[checkingAccIndex].setBal(checkingAccList[checkingAccIndex].getBal() - withdrawAmnt); //Withdraw money
										cout << "Successfully withdrew $" << withdrawAmnt << " from \"" << checkingAccList[checkingAccIndex].getAccName() << "\"." << endl << endl;
										checkingAccList[0].setWithdrawCount(checkingAccList[0].getWithdrawCount() + 1); //Increase withdraw counter
									}

									cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
									cin >> menuReturnOpt;
								}
								else
								{
									system("cls");

									cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display saving accounts
									cout << "--------------------------------------------------------------" << endl;
									for (int i = 0; i < savingAccCount; i++)
									{
										cout << i + 1 << ". " << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
									}
									cout << "--------------------------------------------------------------" << endl;

									cout << "Select an account to withdraw from: ";  //Select a saving account
									cin >> savingAccOpt;
									while (savingAccOpt < 1 || savingAccOpt >= savingAccCount) //Input validation
									{
										if (cin.fail())
										{
											cin.clear();
											cin.ignore(numeric_limits<streamsize>::max(), '\n');
										}
										cout << "Invalid option. Please select an option 1-" << savingAccCount - 1 << ": ";
										cin >> savingAccOpt;
									}

									savingAccIndex = savingAccOpt - 1;
									system("cls");
									cout << "Enter amount to withdraw: "; //Enter withdraw amount
									cin >> withdrawAmnt;

									while (withdrawAmnt < 0)
									{
										cout << "Error: Cannot withdraw a negative number." << endl; //Input validation
										cout << "Enter amount to withdraw: ";
										cin >> withdrawAmnt;
									}

									cout << "Are you sure you want to withdraw $" << withdrawAmnt << " from \"" << savingAccList[savingAccIndex].getAccName() << "\"? (Y/N): ";
									cin >> confirmOpt;

									while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
									{
										cout << "Invalid response. Please selection an option Y/N: ";
										cin >> confirmOpt;
									}

									if (confirmOpt == 'Y' || confirmOpt == 'y')
									{
										savingAccList[savingAccIndex].setBal(savingAccList[savingAccIndex].getBal() - withdrawAmnt); //Withdraw money
										cout << "Successfully withdrew $" << withdrawAmnt << " from \"" << savingAccList[savingAccIndex].getAccName() << "\"." << endl << endl;
										savingAccList[0].setWithdrawCount(savingAccList[0].getWithdrawCount() + 1); //Increase withdraw counter
									}

									cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
									cin >> menuReturnOpt;
								}
							}
						}
						else if (subMenuOpt == 3) //TRANSFER
						{
							system("cls");
							if (savingAccList[0].getBal() == 0)
							{
								cout << "Error: You are broke. There is no money to transfer." << endl;
							}
							else
							{
								cout << "Select which type of account to transfer from: " << endl; //Checking/Saving selection
								cout << "1. Checking" << endl;
								cout << "2. Saving" << endl;
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

								if (accTypeOpt == 1) //TRANSFER FROM CHECKING
								{
									system("cls");

									cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display checking accounts
									cout << "--------------------------------------------------------------" << endl;
									for (int i = 0; i < checkingAccCount; i++)
									{
										cout << i + 1 << ". " << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
									}
									cout << "--------------------------------------------------------------" << endl;

									cout << "Select an account to transfer from: ";  //Select a checking account
									cin >> checkingAccOpt;
									while (checkingAccOpt < 1 || checkingAccOpt >= checkingAccCount) //Input validation
									{
										if (cin.fail())
										{
											cin.clear();
											cin.ignore(numeric_limits<streamsize>::max(), '\n');
										}
										cout << "Invalid option. Please select an option 1-" << checkingAccCount - 1 << ": ";
										cin >> checkingAccOpt;
									}

									transferPullIndex = checkingAccOpt - 1;
									system("cls");
									cout << "Enter amount to transfer: "; //Enter withdraw amount
									cin >> transferAmnt;

									while (transferAmnt < 0)
									{
										cout << "Error: Cannot transfer a negative number." << endl; //Input validation
										cout << "Enter amount to transfer: ";
										cin >> transferAmnt;
									}


									cout << "Select which type of account to transfer to: " << endl; //Checking/Saving selection
									cout << "1. Checking" << endl;
									cout << "2. Saving" << endl;
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

									if (accTypeOpt == 1) //TRANSFER FROM CHECKING TO CHECKING
									{
										system("cls");

										cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display checking accounts
										cout << "--------------------------------------------------------------" << endl;
										for (int i = 0; i < checkingAccCount; i++)
										{
											cout << i + 1 << ". " << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
										}
										cout << "--------------------------------------------------------------" << endl;

										cout << "Select an account to transfer to: ";  //Select a checking account
										cin >> checkingAccOpt;
										while (checkingAccOpt < 1 || checkingAccOpt >= checkingAccCount) //Input validation
										{
											if (cin.fail())
											{
												cin.clear();
												cin.ignore(numeric_limits<streamsize>::max(), '\n');
											}
											cout << "Invalid option. Please select an option 1-" << checkingAccCount - 1 << ": ";
											cin >> checkingAccOpt;
										}

										transferPushIndex = checkingAccOpt - 1;
										cout << "Are you sure you want to transfer $" << transferAmnt << " from \"" << checkingAccList[transferPullIndex].getAccName() << "\" to \"" << checkingAccList[transferPushIndex].getAccName() << "\"? (Y/N): ";
										cin >> confirmOpt;

										while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
										{
											cout << "Invalid response. Please selection an option Y/N: ";
											cin >> confirmOpt;
										}

										if (confirmOpt == 'Y' || confirmOpt == 'y')
										{
											checkingAccList[transferPullIndex].setBal(checkingAccList[transferPullIndex].getBal() - transferAmnt); //Pull money out of old account
											checkingAccList[transferPushIndex].setBal(checkingAccList[transferPushIndex].getBal() + transferAmnt); //Push money in new account
										}
										else
										{
											cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
											cin >> menuReturnOpt;
										}
									}
									else //TRANSFER FROM CHECKING TO SAVING
									{
										system("cls");

										cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display saving accounts
										cout << "--------------------------------------------------------------" << endl;
										for (int i = 0; i < savingAccCount; i++)
										{
											cout << i + 1 << ". " << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
										}
										cout << "--------------------------------------------------------------" << endl;

										cout << "Select an account to transfer to: ";  //Select a saving account
										cin >> savingAccOpt;
										while (savingAccOpt < 1 || savingAccOpt >= savingAccCount) //Input validation
										{
											if (cin.fail())
											{
												cin.clear();
												cin.ignore(numeric_limits<streamsize>::max(), '\n');
											}
											cout << "Invalid option. Please select an option 1-" << savingAccCount - 1 << ": ";
											cin >> savingAccOpt;
										}

										transferPushIndex = savingAccOpt - 1;
										cout << "Are you sure you want to transfer $" << transferAmnt << " from \"" << savingAccList[transferPullIndex].getAccName() << "\" to \"" << savingAccList[transferPushIndex].getAccName() << "\"? (Y/N): ";
										cin >> confirmOpt;

										while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
										{
											cout << "Invalid response. Please selection an option Y/N: ";
											cin >> confirmOpt;
										}

										if (confirmOpt == 'Y' || confirmOpt == 'y')
										{
											checkingAccList[transferPullIndex].setBal(checkingAccList[transferPullIndex].getBal() - transferAmnt); //Pull money out of old account
											savingAccList[transferPushIndex].setBal(savingAccList[transferPushIndex].getBal() + transferAmnt); //Push money in new account
										}
										else
										{
											cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
											cin >> menuReturnOpt;
										}
									}
								}
								else //TRANSFER FROM SAVING
								{
									system("cls");

									cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display saving accounts
									cout << "--------------------------------------------------------------" << endl;
									for (int i = 0; i < savingAccCount; i++)
									{
										cout << i + 1 << ". " << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
									}
									cout << "--------------------------------------------------------------" << endl;

									cout << "Select an account to transfer from: ";  //Select a saving account
									cin >> savingAccOpt;
									while (savingAccOpt < 1 || savingAccOpt >= savingAccCount) //Input validation
									{
										if (cin.fail())
										{
											cin.clear();
											cin.ignore(numeric_limits<streamsize>::max(), '\n');
										}
										cout << "Invalid option. Please select an option 1-" << savingAccCount - 1 << ": ";
										cin >> savingAccOpt;
									}

									transferPullIndex = savingAccOpt - 1;
									system("cls");
									cout << "Enter amount to transfer: "; //Enter transfer amount
									cin >> transferAmnt;

									while (transferAmnt < 0)
									{
										cout << "Error: Cannot transfer a negative number." << endl; //Input validation
										cout << "Enter amount to transfer: ";
										cin >> transferAmnt;
									}


									cout << "Select which type of account to transfer to: " << endl; //Checking/Saving selection
									cout << "1. Checking" << endl;
									cout << "2. Saving" << endl;
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

									if (accTypeOpt == 1) //TRANSFER FROM SAVING TO CHECKING
									{
										system("cls");

										cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display checking accounts
										cout << "--------------------------------------------------------------" << endl;
										for (int i = 0; i < checkingAccCount; i++)
										{
											cout << i + 1 << ". " << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
										}
										cout << "--------------------------------------------------------------" << endl;

										cout << "Select an account to transfer to: ";  //Select a checking account
										cin >> checkingAccOpt;
										while (checkingAccOpt < 1 || checkingAccOpt >= checkingAccCount) //Input validation
										{
											if (cin.fail())
											{
												cin.clear();
												cin.ignore(numeric_limits<streamsize>::max(), '\n');
											}
											cout << "Invalid option. Please select an option 1-" << checkingAccCount - 1 << ": ";
											cin >> checkingAccOpt;
										}

										transferPushIndex = checkingAccOpt - 1;
										cout << "Are you sure you want to transfer $" << transferAmnt << " from \"" << checkingAccList[transferPullIndex].getAccName() << "\" to \"" << checkingAccList[transferPushIndex].getAccName() << "\"? (Y/N): ";
										cin >> confirmOpt;

										while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
										{
											cout << "Invalid response. Please selection an option Y/N: ";
											cin >> confirmOpt;
										}

										if (confirmOpt == 'Y' || confirmOpt == 'y')
										{
											savingAccList[transferPullIndex].setBal(savingAccList[transferPullIndex].getBal() - transferAmnt); //Pull money out of old account
											checkingAccList[transferPushIndex].setBal(checkingAccList[transferPushIndex].getBal() + transferAmnt); //Push money in new account
										}
										else
										{
											cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
											cin >> menuReturnOpt;
										}
									}
									else //TRANSFER FROM SAVING TO SAVING
									{
										system("cls");

										cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display saving accounts
										cout << "--------------------------------------------------------------" << endl;
										for (int i = 0; i < savingAccCount; i++)
										{
											cout << i + 1 << ". " << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
										}
										cout << "--------------------------------------------------------------" << endl;

										cout << "Select an account to transfer to: ";  //Select a saving account
										cin >> savingAccOpt;
										while (savingAccOpt < 1 || savingAccOpt >= savingAccCount) //Input validation
										{
											if (cin.fail())
											{
												cin.clear();
												cin.ignore(numeric_limits<streamsize>::max(), '\n');
											}
											cout << "Invalid option. Please select an option 1-" << savingAccCount - 1 << ": ";
											cin >> savingAccOpt;
										}

										transferPushIndex = savingAccOpt - 1;
										cout << "Are you sure you want to transfer $" << transferAmnt << " from \"" << savingAccList[transferPullIndex].getAccName() << "\" to \"" << savingAccList[transferPushIndex].getAccName() << "\"? (Y/N): ";
										cin >> confirmOpt;

										while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
										{
											cout << "Invalid response. Please selection an option Y/N: ";
											cin >> confirmOpt;
										}

										if (confirmOpt == 'Y' || confirmOpt == 'y')
										{
											savingAccList[transferPullIndex].setBal(savingAccList[transferPullIndex].getBal() - transferAmnt); //Pull money out of old account
											savingAccList[transferPushIndex].setBal(savingAccList[transferPushIndex].getBal() + transferAmnt); //Push money in new account
										}
										else
										{
											cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
											cin >> menuReturnOpt;
										}
									}
								}
							}
						}
					} while (menuReturnOpt != 2);
				}
			}
			customerFound = false; //Reset flag
			
			break;
		case 3: //OPTION 3: Modify or delete accounts
			system("cls");
			cout << "---------------------------------------" << endl;

			if (totalCustomerCount == 0)
			{
				cout << "Error: There are no customers in the system." << endl;
			}
			else
			{
				cout << "Select one of the follwing options:" << endl;
				cout << "1. Modify an account" << endl;
				cout << "2. Delete an account" << endl;
				cin >> subMenuOpt;

				while (subMenuOpt < 1 || subMenuOpt > 2)
				{
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "Invalid option." << endl;
					cout << "Please select an option 1-2: ";
					cin >> subMenuOpt;
				}


			}

			cout << "Press any key to return to menu: ";
			cin.ignore();
			cin.get();
			break;
		case 4: //OPTION 4: View personal account info
			system("cls");
			cout << "---------------------------------------" << endl;

			if (totalCustomerCount == 0)
			{
				cout << "Error: There are no customers in the system." << endl;
			}
			else
			{
				cout << "Please enter the following credentials: " << endl;
				cout << "Enter customer last name: ";
				cin >> lname;
				cout << "Enter customer phone number (digits only): ";
				cin >> phoneNumber;

				for (int i = 0; i < totalCustomerCount; i++) //Check every customer to find a match
				{
					if (lname == customerList[i].getLname() && phoneNumber == customerList[i].getPhone())
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
					savingAccList[savingAccCount].printInfo();
				}
			}
			
			cout << "Press any key to return to menu: ";
			cin.ignore();
			cin.get();

			break;
		case 5: //OPTION 5: View all customers
			system("cls");
			cout << "-------------------------------------------------------------------------------------------------" << endl;

			if (totalCustomerCount == 0)
			{
				cout << "Error: There are no customers in the system." << endl << endl;
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

	} while (menuOpt != 6);

	cout << "Toodles." << endl;

	return 0;
}