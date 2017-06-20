#pragma once
#include <string>

using namespace std;

class Atm //main class with functions
{

private:
	
	int i = 0;
	double withAmt;
	double deposAmt;
	int choiceOne;
	
public:
	
	int getAcctNum();
	double withdraw(double balance);
	double deposit(double balance);
	int acctCreation();
	double process(double bal);
	int repeat();
	double acctBalance(int acct);
	string getName();
	
	void display(string person, int acct, double bal);
	void writeAccount(string name, int acct, double bal);
	void overwriteAccount(string name, double bal, int acct);
};