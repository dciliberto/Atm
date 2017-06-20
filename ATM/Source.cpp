#include <iostream>
#include <string>
#include "Atm.h"
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "User.h"
#include <iomanip>

using namespace std;

string name; //variable declaration
int acctNum;
double balance;
int choiceZero;
int choiceTwo = 1;

userAccount user; //structure declaration


int main()
{
	Atm Atm; //class declaration
	
	bool validInput = false;
	user.name = Atm.getName(); //gets users name
	
	while (!validInput) //checks that next input is a 1 or a 2
	{
		validInput = true;
		cout << "Would you like to create an account Y(1)/N(2)?" << endl; 
		cin >> choiceZero;

		if (cin.fail() || choiceZero < 1 || choiceZero > 2)
		{
			cin.clear();
			cin.ignore();
			cout << "Invalid input" << endl;
			validInput = false;
		}

	}
	

	if (choiceZero == 1)
	{

		user.acctNum = Atm.acctCreation(); //creates account
		user.balance = 0; //new account balance is set to 0

	}
	
	else
	{

		user.acctNum = Atm.getAcctNum(); //gets account number from user
		user.balance = Atm.acctBalance(user.acctNum); //gets balance from account list based on given account number
		
	}

	Atm.display(user.name, user.acctNum, user.balance); //displays user account information in a table

	while (choiceTwo == 1)
	{

		user.balance = Atm.process(user.balance); //withdrawal and deposit functions are run
		choiceTwo = Atm.repeat(); //re runs Atm.process if user prompts it to

	}

	if (choiceZero == 1)
	{

		Atm.writeAccount(user.name, user.acctNum, user.balance); //writes new accounts to account list

	}
	else if (choiceZero == 2)
	{

		Atm.overwriteAccount(user.name, user.balance, user.acctNum); //updates balance of old accounts

	}

	
	

	return 0;

}

