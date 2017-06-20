#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "Atm.h"
#include <fstream>

using namespace std;

int Atm::acctCreation() //creates account
{
	
	int* acctNum = NULL;
	acctNum = new int;
	srand((int)time(0));
	*acctNum = (rand() % 1000 + 1);
	cout << "Your new account number is: " << *acctNum << endl;

	return *acctNum;
	delete acctNum;

}

string Atm :: getName() //gets users name
{

	string name;
	cout << "Input Name: ";
	cin >> name;
	return name;

}

int Atm::getAcctNum() //gets users account number
{

	bool valid = false;
	int* acctNum = NULL;
	acctNum = new int;
	
	while (!valid)
	{

		valid = true;
		cout << "Input Account Number: ";
		cin >> *acctNum;

		if (cin.fail()) //checks if input is a string
		{

			cin.clear();
			cin.ignore();
			cout << "Invalid input" << endl;
			valid = false;

		}

	}

	return *acctNum;
	delete acctNum;

}

double Atm::process(double bal)
{

	bool* isValid = NULL;
	isValid = new bool;
	*isValid = false;
	int* choiceOne = NULL;
	choiceOne = new int;

	while (!(*isValid)) //while loop checks that user inputed a 1 or 2 when prompted
	{

		*isValid = true;
		cout << "Would you like to Withdraw(1) or Deposit(2)?" << endl;
		cin >> *choiceOne;

		if (cin.fail() || *choiceOne < 1 || *choiceOne > 2)
		{

			cin.clear();
			cin.ignore();
			cout << "Invalid input" << endl;
			*isValid = false;

		}

	}

	delete isValid;

	if (*choiceOne == 1)
	{

		bal = withdraw(bal); //calls withdraw function

	}
	else
	{

		bal = deposit(bal); //calls deposit function

	}

	delete choiceOne;
	cout << "Current balance is : $" << bal << endl;
	return bal;

}



double Atm::withdraw(double bal) //withdraw function, takes in balance
{

	bool valid = false;
	double* withAmt = NULL;
	withAmt = new double;

	while (!valid) //checks that entered amuont is a number
	{
		valid = true;
		cout << "Enter withdraw amount: $";
		cin >> *withAmt;
	
		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input" << endl;
			valid = false;
		}
	
	}

	if (*withAmt > bal) //checks that amount to be withdrawn doesnt exceed current balance
	{

		cout << "Withdrawal exceeds balance" << endl;

	}
	else
	{

		cout << "Withdrawing Funds" << endl;
		bal -= *withAmt;

	}

	delete withAmt;
	return bal;

}

double Atm::deposit(double bal) //deposit function
{

	bool valid = false;
	double* deposAmt = NULL;
	deposAmt = new double;

	while (!valid) //checks that a number is entered and not a string
	{

		valid = true;
		cout << "Enter deposit amount: $";
		cin >> *deposAmt;

		if (cin.fail())
		{

			cin.clear();
			cin.ignore();
			cout << "Invalid input" << endl;
			valid = false;

		}

	}

	bal += *deposAmt;
	delete deposAmt;
	return bal;

}

int Atm::repeat() //funtion that makes the main process for calling withdraw or deposit repeat
{

	int choiceTwo;
	bool* isValid = NULL;
	isValid = new bool;
	*isValid = false;

	while (!(*isValid)) //while loop checks that 1 or 2 is entered when prompted
	{

		*isValid = true;
		cout << "Would you like to do anythign else Y(1)/N(2)?" << endl;
		cin >> choiceTwo;

		if (cin.fail() || choiceTwo < 1 || choiceTwo >2)
		{

			cin.clear();
			cin.ignore();
			cout << "Invalid input" << endl;
			*isValid = false;

		}

	}

	delete isValid;
	return choiceTwo;

}

void Atm :: display(string person, int acct, double bal) //displays account information in table
{

	cout << setw(30) << right << "Name: " << person << endl;
	cout << setw(30) << right << "Account Number: " << acct << endl;
	cout << setw(31) << right << "Balance: $" << bal << endl;

}

double Atm :: acctBalance(int acct) //checks account balance for existing account
{

	fstream acctFile("accounts.txt"); //opens account list

	int choice;
	string value;
	double bal;
	
	while (acctFile.good()) //gets balance from account list using the account number
	{

		int temp = acct;
		string accountName = to_string(temp);
		getline(acctFile, value, ',');
		if ((strcmp(accountName.c_str(), value.c_str())) == 0)
		{

			string balanceStore;
			getline(acctFile, balanceStore, ',');
			bal = stod(balanceStore);

 			break;

		}

	}
	
	if (bal == NULL) //checks if account number has an existing account
	{

		cout << "invalid account number" << endl;
		cout << "try again? y(1)/n(2)" << endl;
		cin >> choice;
	
		if (choice == 1)
		{

			acctBalance(acct);

		}
		else
		{

			exit;

		}
		                                                  
	}
	
	return bal;

}

void Atm :: writeAccount(string name, int acct, double bal) //writes new account to account list
{

	fstream accounts;
	accounts.open("accounts.txt", std::ios_base::app);
	accounts << setw(10) << left << name << "," << setw(3) << left << acct << "," << setw(20) << left << bal << "," << endl;

}

void Atm::overwriteAccount(string name, double bal, int acct) //updates account balance for existing accounts
{

	size_t ptr;
	string str;
	string balanceNew = to_string(bal);
	string accountNumber = to_string(acct);
	string balanceOld;
	int count = 1;

	fstream acctList("accounts.txt", ios::in | ios::out | ios::binary);
	acctList.seekp(0);
	
	while (getline(acctList, str, ','))
	{

		if (str == accountNumber)
		{

			getline(acctList, balanceOld, ',');
			str = name + ',' + accountNumber + ',' + balanceOld + ',';
			ptr = str.find(balanceOld);
			str.replace(ptr, 20, balanceNew);

			if (count == 2)
			{

				acctList.seekp(15);
				acctList << balanceNew;

			}
			else
			{

				acctList.seekp(((count / 3) * 37) + (15 + 1 + (count / 3)));
				acctList << balanceNew;

			}

			break;
		}

		count++;

	}

}