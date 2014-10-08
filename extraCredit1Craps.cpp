//April 16, 2014
//Author: Andres Garcia de Alba

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ctype.h>

using namespace std;
//function prototypes
void askRoll(char&, double&, int&, double&);  //asks the player if they want to roll
void getRollSum(int& sum, int&rolls, double& bet, double& balance);  //gives me what the player rolled
void getBet(double&, double);  //gets the player's bet
void winRoll(int&, int, double&, double&, char&, int&);  //if 7 or 11 is rolled on FIRST roll
void loseRoll(int&, int, double&, double&, char&, int&);  // if 2, 3, or 12 is rolled on FIRST roll
void playCraps(int, int, char&, double&, double, int&);  //if 4, 5, 6, 8, 9 or 10 on the FIRST roll

int main()
{
	double balance = 1000, bet;
	int sum, point = 0, rolls = 0;  //sum == what the player rolled
	char roll;  //Yes or No.  also used to exit the game.

	cout << "****************WELCOME TO CRAPS****************" << endl << endl;
	cout << "7 or 11 on first roll, WIN double your bet" << endl;
	cout << "2, 3, or 12 on first roll, LOSE your bet" << endl;
	cout << "7, before you make your point, LOSE your bet" << endl << endl;
	cout << "************************************************" << endl << endl;
	cout << "Current balance is: $" << balance << endl << endl;
	cout << endl << endl;
	
	askRoll(roll, balance, rolls, bet);  //only called during initial startup of program
	while (roll == 'Y' && balance > 0)  //following statements only run if the player chooses to play.
	{
		if (rolls==0)
			askRoll(roll, balance, rolls, bet);  //resets the game if the player wins/loses and chooses to continue playing
		if (roll == 'N' || roll =='n')  //exits the loop if the player chooses not to play.
			break;
		getBet(bet, balance);  //gets player's bet
		getRollSum(sum, rolls, bet, balance);  // gets what the player rolled
		if (rolls == 1)  
		{
			winRoll(rolls, sum, balance, bet, roll, point);  // win and loose functions only run if it is the player's first roll
			loseRoll(rolls, sum, balance, bet, roll, point);
		}
		if (rolls > 0)
			playCraps(sum, point, roll, balance, bet, rolls);  //only runs if the player did not win or lose on the first roll
	}
	return 0;
}

void askRoll(char& roll, double& balance, int& rolls, double& bet)
{
	cout << "Roll? (Y or N)  ";
	cin >> roll;

	while (roll != 'Y' && (roll != 'y') && roll != 'n' && roll != 'N')
	{
		cout << "You must enter Y or N!" << endl;
		cout << "Roll? (Y or N)  ";
		cin >> roll;
	}

	if (roll == 'y')
		roll = 'Y';  //converts lowercase y to uppercase
	else if (roll == 'n' || roll == 'N')
	{
		roll = 'N';  //converts lowercase n to uppercase; if not already
		cout << endl << "Thanks for trying!" << endl << endl;
		if (rolls > 0)
			balance = balance - bet;  // bet is lost if player started to play, but chooses to leave
		cout << "Your balance is: $" << balance << endl << endl;
	}
	rolls++;  //rolls is increased by 1
}

void getRollSum(int& sum, int& rolls, double& bet, double& balance)
{
	int dice1, dice2;

	cout << endl;
	srand(time(0));  //this function takes an unsigned int for the seed of the algorithm. time generates different seed values each timme according to the computers time
	dice1 = rand() % 6 + 1;
	dice2 = rand() % 6 + 1;
	sum = dice1 + dice2;
	cout << "You rolled a(n): " << sum << endl << endl;
}

void getBet(double& bet, double balance)
{
	cout << "Place your bet: $";
	cin >> bet;
	while (bet > balance)  //cannot bet more than a player's balance
	{
		cout << "Bet cannot be more than current balance" << endl;
		cout << "Place your bet: $";
		cin >> bet;
		cout << endl;
	}
	while (bet < 0)  //cannot bet a negative amount
	{
		cout << "You cannot bet negative money!" << endl;
		cout << "Place your bet: $";
		cin >> bet;
		cout << endl;
	}
	cout << "Your pending balance is: $" << balance-bet << endl << endl;  
}

void winRoll(int& rolls, int sum, double& balance, double& bet, char& roll, int& point)
{
	if (rolls == 1 && (sum == 7 || sum == 11))  //player wins if 7 or 11 on first roll
	{
		cout << "******You Win!******" << endl;
		balance += bet * 2;  //player gets back twice the bet
		cout << "Your new balance is: $" << balance << endl << endl;
		cout << "************************************************" << endl << endl;
		point = 0;  //reset to 0 to give the player a fresh start
		rolls = 0;  //reset to 0 to give the player a fresh start
	}
}

void loseRoll(int& rolls, int sum, double& balance, double& bet, char& roll, int& point)
{
	if (rolls == 1 && (sum == 2 || sum == 3 || sum == 12))  //player loses if 2, 3, 12 on first roll
	{
		cout << "******You Lose!******" << endl;
		balance -= bet;  //player loses the amount he/she bets
		cout << "Your new balance is: $" << balance << endl << endl;
		cout << "************************************************" << endl << endl;
		point = 0;  //reset to 0 to give the player a fresh start
		rolls = 0;  //reset to 0 to give the player a fresh start
	}
}

void playCraps(int sum, int point, char& roll, double& balance, double bet, int& rolls)
{

	if (rolls > 0)  //if player makes point or loses, roll == 0 and this if statement will not run.  Goes back to main function
	{
		while (roll == 'Y' && balance > 0 && rolls > 0)  // player has to agree to roll, must have enough money, and must be pass the initial roll
		{
			if (rolls > 1)  // runs when player agrees to roll for a second time, third time, etc...
			{
				getRollSum(sum, rolls, bet, balance);
			}

			if (rolls == 1)  //if player didn't win or lose, the player is assigned his/her point
			{
				switch (sum)
				{
				case 4: case 5: case 6: case 8: case 9: case 10: case 11:
					cout << "Your point is: " << sum << endl << endl;
					point = sum;
					cout << "Continue rolling until you make your point" << endl;
					cout << "If 7 is rolled before your point, you lose" << endl;
					cout << "If you don't roll, you forfeit your bet!!!" << endl << endl;
					break;
				}
			}

			if (point == sum  && rolls > 1)  //only runs after player's first roll
			{
				cout << "******You Win!******" << endl;
				cout << "You made your point" << endl << endl;
				balance += 2 * bet;
				cout << "Your new balance is: $" << balance << endl << endl;
				point = 0;  //reset to 0 to give the player a fresh start
				rolls = 0;  //reset to 0 to give the player a fresh start
				cout << "************************************************" << endl << endl;
			}

			if (sum == 7 && rolls > 1)  //only runs after my first roll
			{
				cout << "******You Lose!******" << endl;
				balance -= bet;
				cout << "Your new balance is: $" << balance << endl << endl;
				point = 0;  //reset to 0 to give the player a fresh start
				rolls = 0;  //reset to 0 to give the player a fresh start
				cout << "************************************************" << endl << endl;
			}

			if (rolls > 0)  //asks player to roll in order to make the point and win!... or lose
				askRoll(roll, balance, rolls, bet);  //if player chooses 'n', loop conditions are not met and control goes back to main
		}
	}
}