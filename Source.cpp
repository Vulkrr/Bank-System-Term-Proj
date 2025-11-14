#include "Customer.h"
#include "Account.h"
#include "CheckingAccount.h"
#include "SavingAccount.h"
#include "Transaction.h"
#include "MiscFunctions.h"
#include <iomanip>
#include <vector>
using namespace std;

//Finish implementing transaction functions
//Start working on transaction history
//Put customer credentials into a miscfunction getCredentials()

int totalCustomerCount = 0, customerIndex = 0,
checkingAccCount = 0, checkingAccIndex = 0,
savingAccCount = 0, savingAccIndex = 0,
transferPullIndex = 0, transferPushIndex = 0,
transactionCount = 0, generalAccIndex = 0;

int main() 
{
	//Array limits
	const int customerLimit = 10, checkingAccLimit = 5, savingAccLimit = 5;

	//Bank limits
	const double interestRateValue = 1.02, overdraftLimit = 500, accNameLimit = 30; 

	//Arrays
	Customer customerList[customerLimit];
	CheckingAccount checkingAccList[checkingAccLimit];
	SavingAccount savingAccList[savingAccLimit];

	//Transaction history vector (not implemented yet)
	vector<Transaction> transactionList;

	//Flags
	bool customerFound = false, duplicateInfo;

	//Option inputs
	int mainMenuOpt, subMenuOpt, accTypeOpt, menuReturnOpt, checkingAccOpt, savingAccOpt, generalAccOpt; 
	char confirmOpt;

	//Info inputs
	string fname, lname, address, email, phoneNumber, accName; 

	//Amount inputs
	double depositAmnt, withdrawAmnt, transferAmnt;

	do
	{
		system("cls");
		cout << "=======================BANK MANAGER=======================" << endl; //Main menu 
		cout << "1. Create an account" << endl;
		cout << "2. Make a transaction" << endl;
		cout << "3. Modify or delete accounts" << endl;
		cout << "4. View personal account information" << endl;
		cout << "5. View all customers" << endl;
		cout << "6. Exit program" << endl;
		cout << "==========================================================" << endl;
		cout << "Welcome. Please select one of the above options: ";
		cin >> mainMenuOpt;
		while (mainMenuOpt < 1 || mainMenuOpt > 6) //Input validation
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
		case 1: //OPTION 1: Create an account
			system("cls");	
			cout << "---------------------------------------------------------" << endl;
			cout << "1. Create a new customer profile" << endl;
			cout << "2. Create an account for an existing customer" << endl;
			cout << "---------------------------------------------------------" << endl;
			cout << "Select one of the above options:" << endl;
			cin >> subMenuOpt;

			while (subMenuOpt < 1 || subMenuOpt > 2) //Input validation
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				cout << "Error: Invalid option. Please enter an option 1-2: ";
				cin >> subMenuOpt;
			}

			if (subMenuOpt == 1)
			{
				cout << "-------------------------------------------------------------" << endl;
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
				do
				{
					cout << "--------------------------------------------" << endl;
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

			if (customerFound)
			{
				cout << "-------------------------------------------------------" << endl; //Account creation selection
				cout << "1. Checking account" << endl;
				cout << "2. Saving account" << endl;
				cout << "-------------------------------------------------------" << endl; //Account creation selection
				cout << "Select which type of account you would like to create: " << endl;
				cin >> accTypeOpt;

				while (accTypeOpt < 1 || accTypeOpt > 2) //Input validation
				{
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
					}
					cout << "Error: Invalid option. Please enter an option 1-2: ";
					cin >> accTypeOpt;
				}

				if (accTypeOpt == 1)
				{
					cout << "------------------------------" << endl;
					cout << "Enter a name for this account: ";
					cin.ignore();
					getline(cin, accName);
					while (accName.length() >= accNameLimit) //Input validation
					{
						cout << "Error: Account name must be 30 characters or less. Please try again." << endl;
						cout << "Enter a name for this account: ";
						getline(cin, accName);
					}

					checkingAccList[checkingAccCount].setAll((checkingAccCount + 1), 0, 0, 0, 0, 0, accName, &customerList[customerIndex],overdraftLimit); //Checking account creation
					cout << "-------------------------------------------------------------------------------------" << endl;
					cout << "You have successfully created a checking account named " << "\"" << accName << "\"." << endl;
					checkingAccCount++;
				}
				else
				{
					cout << "------------------------------------------------------------" << endl;
					cout << "Enter a name for this account: ";
					cin.ignore();
					getline(cin, accName);
					while (accName.length() >= accNameLimit) //Input validation
					{
						cout << "Error: Account name must be 30 characters or less. Please try again." << endl;
						cout << "Enter a name for this account: ";
						getline(cin, accName);
					}

					savingAccList[savingAccCount].setAll((savingAccCount + 1), 0, 0, 0, 0, 0, accName, &customerList[customerIndex], interestRateValue); //Saving account creation
					cout << "You have successfully created a saving account named " << "\"" << accName << "\"." << endl;
					savingAccCount++;
				}

				cout << "Press any key to return to menu: ";
				cin.ignore();
				cin.get();
			}
			else
			{
				cout << "Error: Customer does not exist or was not found." << endl;
			}
			customerFound = false; //Reset flag

			break;
		case 2: //OPTION 2: Make a transaction 
			system("cls");
			cout << "--------------------------------------------" << endl;
			
			if (totalCustomerCount == 0) //If there are no existing customers, exit
			{
				cout << "Error: There are no customers in the system." << endl;
			}
			else
			{
				do
				{
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
					do
					{
						system("cls");
						cout << "-------------------------------------------" << endl; //Transaction sub-menu
						cout << "Please select one of the following options:" << endl;
						cout << "1. Deposit" << endl;
						cout << "2. Withdraw" << endl;
						cout << "3. Transfer" << endl;
						cout << "4. Take Loan" << endl;
						cout << "5. Return to main menu" << endl;
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
								cout << "Error: Invalid option. Please select an option 1-2: ";
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
									cout << "Error: Invalid option. Please select an option 1-2" << checkingAccCount - 1 << ": ";
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

								while (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Input validation
									cout << "Error: Invalid amount. Please enter a valid number: " << endl;
									cin >> depositAmnt;
								}

								cout << "Are you sure you want to deposit $" << depositAmnt << " to \"" << checkingAccList[checkingAccIndex].getAccName() << "\"? (Y/N): ";
								cin >> confirmOpt;

								while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
								{
									cout << "Invalid response. Please selection an option Y/N: ";
									cin >> confirmOpt;
								}

								if (confirmOpt == 'Y' || confirmOpt == 'y')
								{
									checkingAccList[checkingAccIndex].deposit(depositAmnt); //Deposit money
									cout << "Successfully deposited $" << depositAmnt << " to \"" << checkingAccList[checkingAccIndex].getAccName() << "\"." << endl << endl;
									checkingAccList[0].setDepositCount(checkingAccList[0].getDepositCount() + 1); //Increase deposit counter

									Transaction t("Deposit", depositAmnt, checkingAccList[checkingAccIndex].getBal()); //Create a new transaction object
									transactionList.push_back(t); //Add the object to transaction list
									transactionCount++; //Increase transaction counter
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

								cout << "Select an account to deposit to: ";  //Select a saving account
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

								cout << "Are you sure you want to deposit $" << depositAmnt << " to \"" << checkingAccList[checkingAccIndex].getAccName() << "\"? (Y/N): ";
								cin >> confirmOpt;

								while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
								{
									cout << "Invalid response. Please selection an option Y/N: ";
									cin >> confirmOpt;
								}

								if (confirmOpt == 'Y' || confirmOpt == 'y')
								{
									savingAccList[savingAccIndex].deposit(depositAmnt); //Deposit money
									cout << "Successfully deposited $" << depositAmnt << " to \"" << savingAccList[savingAccIndex].getAccName() << "\"." << endl << endl;
									savingAccList[0].setDepositCount(savingAccList[0].getDepositCount() + 1); //Increase deposit counter

									Transaction t("Deposit", depositAmnt, savingAccList[savingAccIndex].getBal()); //Create a new transaction object
									transactionList.push_back(t); //Add the object to transaction list
									transactionCount++; //Increase transaction counter
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
										checkingAccList[checkingAccIndex].withdraw(withdrawAmnt); //Withdraw money
										cout << "Successfully withdrew $" << withdrawAmnt << " from \"" << checkingAccList[checkingAccIndex].getAccName() << "\"." << endl << endl;
										checkingAccList[0].setWithdrawCount(checkingAccList[0].getWithdrawCount() + 1); //Increase withdraw counter

										Transaction t("Withdrawal", withdrawAmnt, checkingAccList[checkingAccIndex].getBal()); //Create a new transaction object
										transactionList.push_back(t); //Add the object to transaction list
										transactionCount++; //Increase transaction counter
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
										savingAccList[savingAccIndex].withdraw(withdrawAmnt); //Withdraw money
										cout << "Successfully withdrew $" << withdrawAmnt << " from \"" << savingAccList[savingAccIndex].getAccName() << "\"." << endl << endl;
										savingAccList[0].setWithdrawCount(savingAccList[0].getWithdrawCount() + 1); //Increase withdraw counter

										Transaction t("Withdrawal", withdrawAmnt, savingAccList[savingAccIndex].getBal()); //Create a new transaction object
										transactionList.push_back(t); //Add the object to transaction list
										transactionCount++; //Increase transaction counter
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
									cout << "Enter amount to transfer: "; //Enter transfer amount
									cin >> transferAmnt;

									while (transferAmnt < 0) //Input validation
									{
										if (cin.fail())
										{
											cin.clear();
											cin.ignore(numeric_limits<streamsize>::max(), '\n');
										}
										cout << "Error: Invalid amount. Please enter a valid number: ";
										cin >> transferAmnt;
									}

									while (transferAmnt > checkingAccList[transferPullIndex].getBal()) //Funds validation
									{
										cout << "Error: Not enough funds in account. You have $" << checkingAccList[transferPullIndex].getBal() << " in this account." << endl; 
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
											checkingAccList[transferPullIndex].transfer(transferAmnt, checkingAccList[transferPushIndex]); //Transfer

											Transaction t("Transfer", transferAmnt, checkingAccList[transferPullIndex].getBal()); //Create a new transaction object
											transactionList.push_back(t); //Add the object to transaction list
											transactionCount++; //Increase transaction counter
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
											checkingAccList[transferPullIndex].transfer(transferAmnt, checkingAccList[transferPushIndex]); //Transfer

											Transaction t("Transfer", transferAmnt, checkingAccList[transferPullIndex].getBal()); //Create a new transaction object
											transactionList.push_back(t); //Add the object to transaction list
											transactionCount++; //Increase transaction counter
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

										cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display saving accounts
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
											savingAccList[transferPullIndex].transfer(transferAmnt, checkingAccList[transferPushIndex]); //Transfer

											Transaction t("Transfer", transferAmnt, savingAccList[transferPullIndex].getBal()); //Create a new transaction object
											transactionList.push_back(t); //Add the object to transaction list
											transactionCount++; //Increase transaction counter
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
											savingAccList[transferPullIndex].transfer(transferAmnt, savingAccList[transferPushIndex]); //Transfer

											Transaction t("Transfer", transferAmnt, savingAccList[transferPullIndex].getBal()); //Create a new transaction object
											transactionList.push_back(t); //Add the object to transaction list
											transactionCount++; //Increase transaction counter
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
						else if (subMenuOpt == 4) {
						{
							system("cls");

							cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display checking accounts
							cout << "--------------------------------------------------------------" << endl;
							for (int i = 0; i < checkingAccCount; i++)
							{
								cout << i + 1 << ". " << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
							}
							cout << "--------------------------------------------------------------" << endl;

							cout << "Select an account to add a loan to: ";  //Select a checking account
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
							cout << "Please select which loan you would like to add by entering the amount of the loan: " << endl; //Enter loan amount
							cout << "$1000 --- 2.5% APR ---- 5 months" << endl;
							cout << "$2000 --- 5.8% APR ---- 8 months" << endl;
							cout << "$200,000 --- 16% APR --- 30 years" << endl;
							double loanAmnt = 0;
							cin >> loanAmnt;

							while (loanAmnt != 1000 && loanAmnt != 2000 && loanAmnt != 200000)
							{
								cout << "Error: Incorrect Loan Selected." << endl; //Input validation
								cout << "Please select which loan you would like to add by entering the amount of the loan: ";
								cin >> depositAmnt;
							}

							cout << "Are you sure you want to take loan $" << loanAmnt << " and add to \"" << checkingAccList[checkingAccIndex].getAccName() << "\"? (Y/N): ";
							cin >> confirmOpt;

							while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
							{
								cout << "Invalid response. Please selection an option Y/N: ";
								cin >> confirmOpt;
							}

							if (confirmOpt == 'Y' || confirmOpt == 'y')
							{
								checkingAccList[checkingAccIndex].setLoan(loanAmnt);
								cout << " Congrats your debt has grown! " << endl;
								cout << "-------------------------------" << endl;

								Transaction t("Loan", loanAmnt, checkingAccList[checkingAccIndex].getBal()); //Create a new transaction object
								transactionList.push_back(t); //Add the object to transaction list
								transactionCount++; //Increase transaction counter
							}

							cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
							cin >> menuReturnOpt;
						}
					}
				} while (subMenuOpt != 5 || menuReturnOpt != 2);
			} 
			customerFound = false; //Reset flag
			
			break;
		case 3: //OPTION 3: Modify or delete accounts
			system("cls");
			cout << "---------------------------------------" << endl;

			if (totalCustomerCount == 0)
			{
				cout << "Error: There are no customers in the system." << endl;
				cout << "Press any key to return to menu: ";
				cin.ignore();
				cin.get();
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
					cout << "---------------------------------------" << endl;
					cout << "1. Change an account name" << endl; //Display sub menu
					cout << "2. Delete an account" << endl;
					cout << "---------------------------------------" << endl;
					cout << "Select one of the above options: ";
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

					if (subMenuOpt == 1) //CHANGING ACCOUNT NAME
					{
						system("cls");

						do
						{
							system("cls");

							cout << "-------------------------------CHEKCING ACCOUNTS--------------------------------" << endl; //Display all checking accounts
							cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl;
							cout << "--------------------------------------------------------------" << endl;
							for (generalAccIndex = 0; generalAccIndex < checkingAccCount; generalAccIndex++)
							{
								cout << generalAccIndex + 1 << ". " << left << setw(40) << checkingAccList[generalAccIndex].getAccName() << left << setw(20) << checkingAccList[generalAccIndex].getBal() << endl;
							}

							cout << "-------------------------------SAVING ACCOUNTS--------------------------------" << endl; //Display all saving accounts
							cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl;
							cout << "--------------------------------------------------------------" << endl;
							for (generalAccIndex; generalAccIndex < savingAccCount; generalAccIndex++)
							{
								cout << generalAccIndex + 1 << ". " << left << setw(40) << savingAccList[generalAccIndex].getAccName() << left << setw(20) << savingAccList[generalAccIndex].getBal() << endl;
							}

							cout << "--------------------------------------------------------------" << endl;
							cout << "Select an account to edit: ";  //Select an account
							cin >> generalAccOpt;
							while (generalAccOpt < 1 || generalAccOpt >= generalAccIndex) //Input validation
							{
								if (cin.fail())
								{
									cin.clear();
									cin.ignore(numeric_limits<streamsize>::max(), '\n');
								}
								cout << "Invalid option. Please select an option 1-" << generalAccIndex - 1 << ": ";
								cin >> checkingAccOpt;
							}

							generalAccIndex = generalAccOpt - 1;

							cout << "Are you sure you want to edit \"" << checkingAccList[generalAccIndex].getAccName() << "\"? (Y/N): ";
							cin >> confirmOpt;

							while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N')
							{
								cout << "Invalid response. Please selection an option Y/N: ";
								cin >> confirmOpt;
							}

							if (confirmOpt == 'Y' || confirmOpt == 'y')
							{
								system("cls");
								cout << "--------------------------------------------------------------" << endl;
								cout << "Enter a new name for \"" << checkingAccList[checkingAccIndex].getAccName() << "\": ";
								cin >> accName;
								while (accName == checkingAccList[checkingAccIndex].getAccName()) //Input validation
								{
									cout << "Error: New name must be unique. Please enter a new name: ";
									cin >> accName;
								}

								cout << "Successfully renamed account." << endl;
							}

							cout << "Press 1 to edit a new account or 2 to return to main menu: ";
							cin >> menuReturnOpt;

							while (menuReturnOpt < 1 || menuReturnOpt > 2)
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
					else //DELETING AN ACCOUNT
					{
						do
						{
							system("cls");
							cout << "Select which type of account to delete: " << endl; //Checking/Saving selection
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
								cout << "Error: Invalid option. Please select an option 1-2: ";
								cin >> accTypeOpt;
							}

							if (accTypeOpt == 1) //DELETE A CHECKING ACCOUNT
							{
								system("cls");

								cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display checking accounts
								cout << "--------------------------------------------------------------" << endl;
								for (int i = 0; i < checkingAccCount; i++)
								{
									cout << i + 1 << ". " << left << setw(40) << checkingAccList[i].getAccName() << left << setw(20) << checkingAccList[i].getBal() << endl;
								}
								cout << "--------------------------------------------------------------" << endl;

								cout << "Select an account to delete: ";  //Select a checking account
								cin >> checkingAccOpt;
								while (checkingAccOpt < 1 || checkingAccOpt >= checkingAccCount) //Input validation
								{
									if (cin.fail())
									{
										cin.clear();
										cin.ignore(numeric_limits<streamsize>::max(), '\n');
									}
									cout << "Error: Invalid option. Please select an option 1-2" << checkingAccCount - 1 << ": ";
									cin >> checkingAccOpt;
								}

								checkingAccIndex = checkingAccOpt - 1;

								cout << "Are you sure you want to delete " << checkingAccList[checkingAccIndex].getAccName() << "\"? (Y/N): "; //Confirm account deletion
								cin >> confirmOpt;

								while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
								{
									cout << "Invalid response. Please selection an option Y/N: ";
									cin >> confirmOpt;
								}

								if (confirmOpt == 'Y' || confirmOpt == 'y') //Delete checking account
								{
									if (checkingAccIndex < checkingAccCount - 1) //If the deleted account is not in the last index, move all the following accounts to fill the gap
									{
										for (int i = checkingAccIndex; i < checkingAccCount; i++)
										{
											checkingAccList[i].setAll(checkingAccList[i + 1].getID(), checkingAccList[i + 1].getWithdrawCount(), checkingAccList[i + 1].getDepositCount(),
												checkingAccList[i + 1].getTransferCount(), checkingAccList[i + 1].getBal(), checkingAccList[i + 1].getLoan(),
												checkingAccList[i + 1].getAccName(), checkingAccList[i + 1].getCustomerInfo(), checkingAccList[i + 1].getOverdraftLimit());
										}
									}
									else
									{
										checkingAccList[checkingAccCount].setAll(0, 0, 0, 0, 0, 0, "", nullptr, 0);
									}
									checkingAccCount--;
								}

								cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
								cin >> menuReturnOpt;
							}
							else //DELETE A SAVING ACCOUNT
							{
								system("cls");

								cout << left << setw(40) << "Account Name" << left << setw(20) << "Balance" << endl; //Display saving accounts
								cout << "--------------------------------------------------------------" << endl;
								for (int i = 0; i < savingAccCount; i++)
								{
									cout << i + 1 << ". " << left << setw(40) << savingAccList[i].getAccName() << left << setw(20) << savingAccList[i].getBal() << endl;
								}
								cout << "--------------------------------------------------------------" << endl;

								cout << "Select an account to delete: ";  //Select a saving account
								cin >> savingAccOpt;
								while (savingAccOpt < 1 || savingAccOpt >= savingAccCount) //Input validation
								{
									if (cin.fail())
									{
										cin.clear();
										cin.ignore(numeric_limits<streamsize>::max(), '\n');
									}
									cout << "Error: Invalid option. Please select an option 1-2" << savingAccCount - 1 << ": ";
									cin >> savingAccOpt;
								}

								checkingAccIndex = savingAccOpt - 1;

								cout << "Are you sure you want to delete " << savingAccList[savingAccIndex].getAccName() << "\"? (Y/N): "; //Confirm account deletio
								cin >> confirmOpt;

								while (confirmOpt != 'y' && confirmOpt != 'Y' && confirmOpt != 'n' && confirmOpt != 'N') //Input validation
								{
									cout << "Invalid response. Please selection an option Y/N: ";
									cin >> confirmOpt;
								}

								if (confirmOpt == 'Y' || confirmOpt == 'y') //Delete saving account
								{
									if (savingAccIndex < checkingAccCount - 1)
									{
										for (int i = savingAccIndex; i < savingAccCount; i++) //If the deleted account is not in the last index, move all the following accounts to fill the gap
										{
											savingAccList[i].setAll(savingAccList[i + 1].getID(), savingAccList[i + 1].getWithdrawCount(), savingAccList[i + 1].getDepositCount(),
												savingAccList[i + 1].getTransferCount(), savingAccList[i + 1].getBal(), savingAccList[i + 1].getLoan(),
												savingAccList[i + 1].getAccName(), savingAccList[i + 1].getCustomerInfo(), savingAccList[i + 1].getInterestRate());
										}
									}
									else
									{
										savingAccList[savingAccCount].setAll(0, 0, 0, 0, 0, 0, "", nullptr, 0);
									}
									savingAccCount--;
								}

								cout << "Press 1 to make a new transaction or 2 to return to main menu: ";
								cin >> menuReturnOpt;
							}
						} while (menuReturnOpt == 1);
					}
				}				
			}
			
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
					cout << "---------------------------------------" << endl;
					cout << "1. View general info" << endl;
					cout << "2. View transaction history" << endl;
					cout << "3. View account list" << endl;
					cout << "---------------------------------------" << endl;
					cout << "Select one of the above options: ";
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

					if (subMenuOpt == 1)
					{

					}
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
		} 
	} while (mainMenuOpt != 6 || menuReturnOpt != 2);

	cout << "Toodles." << endl;
	return 0;
}
