#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>

// imports for custom header files storing proto methods and variables
#include "Methods.h"
#include "Variables.h"

variables* var{ nullptr };

void methods::initialiseVars()
{
	// USED TO MAKE SURE ALL VARIABLES ARE RESET TO 0 WHEN A NEW GAME IS STARTED 

	if (!var) // IF NO VAR ALREADY EXISTS 
	{
		var = new variables(); // CREATE A NEW INSTANCE OF VAR
	}

	var->firstRowStopped = false;
	var->secondRowStopped = false;
	var->thirdRowStopped = false;

	var->currentRoll = 0;
	var->userKey = 0;

	var->firstColumn = '_';
	var->secondColumn = '_';
	var->thirdColumn = '_';
}

void methods::mainMenu()
{
	this->initialiseVars();
	// HANDLES ALL INPUT AND DISPLAY FOR THE MAIN MENU

	std::cout << "\n|1) Play          |";
	std::cout << "\n|2) Rules         |";
	std::cout << "\n|3) Topup Balance |";
	std::cout << "\n|4) Stats         |";
	std::cout << "\n|5) Save Game     |";
	std::cout << "\n|6) Load Game     |";
	std::cout << "\n|7) Quit          |";

	std::cout << "\nChoice: ";
	std::cin >> var->userKey;

	switch (var->userKey)
	{
		case 1:
		{
			this->placeBet(var->money);
		}
			break;
		case 2:
		{
			this->printRules();
		}
			break;
		case 3:
		{
			this->topupMoney();
		}
			break;
		case 4:
		{
			this->printStats();
		}
			break;
		case 5:
		{
			this->saveGame(var);
		}
			break;
		case 6:
		{
			this->loadGame(var);
		}
			break;
		case 7:
		{
			this->exitGame();
		}
			break;
		default:
		{
			system("CLS");  
			this->mainMenu();
		}
	}
}

void methods::printRules()
{
	system("CLS");

	std::cout << "\n  ###########";
	std::cout << "\n  ## Rules ##";
	std::cout << "\n  ###########\n";

	std::cout << "\n|     Press S to stop the current column from spinning";
	std::cout << "\n|    '| 3 | 3 | 3 |' Match any 3 numbers for the jackpot";
	std::cout << "\n|    '| 3 | 3 | # |' Match 2 numbers for a smaller jackpot";
	std::cout << "\n|    '| 3 | # | 3 |' Match 2 numbers for a smaller jackpot";
	std::cout << "\n-------------------------------------";

	this->mainMenu();
}

void methods::placeBet(int currentMoney)
{
	std::cout << "\nHow much would you like to bet on your next roll?";
	std::cout << "\nCurrent Balance: " << char(156) << currentMoney;

	if (currentMoney == 0 || currentMoney < 50)
	{
		this->topupMoney();
	}
	else if (currentMoney >= 50 && currentMoney < 100)
	{
		std::cout << "\n1) " << char(156) << "50\n";
	}
	else if (currentMoney >= 100 && currentMoney < 200)
	{
		std::cout << "\n1) " << char(156) << "50";
		std::cout << "\n2) " << char(156) << "100\n";
	}
	else if (currentMoney >= 200 && currentMoney < 300)
	{
		std::cout << "\n1) " << char(156) << "50";
		std::cout << "\n2) " << char(156) << "100";
		std::cout << "\n3) " << char(156) << "200\n";
	}
	else if (currentMoney >= 300 && currentMoney < 400)
	{
		std::cout << "\n1) " << char(156) << "50";
		std::cout << "\n2) " << char(156) << "100";
		std::cout << "\n3) " << char(156) << "200";
		std::cout << "\n4) " << char(156) << "300\n";
	}
	else if (currentMoney >= 400 && currentMoney < 500)
	{
		std::cout << "\n1) " << char(156) << "50";
		std::cout << "\n2) " << char(156) << "100";
		std::cout << "\n3) " << char(156) << "200";
		std::cout << "\n4) " << char(156) << "300";
		std::cout << "\n5) " << char(156) << "400\n";
	}
	else if (currentMoney >= 500)
	{
		std::cout << "\n1) " << char(156) << "50";
		std::cout << "\n2) " << char(156) << "100";
		std::cout << "\n3) " << char(156) << "200";
		std::cout << "\n4) " << char(156) << "300";
		std::cout << "\n5) " << char(156) << "400";
		std::cout << "\n6) " << char(156) << "500\n";
	}

	std::cin >> var->newBet;

	switch (var->newBet)
	{
		case 1:
		{
			std::cout << "\nYou bet " << char(156) << "50 the next roll\n";
			var->money -= 50;
		}
			break;
		case 2:
		{
			std::cout << "\nYou bet " << char(156) << "100 on the next roll\n";
			var->money -= 100;
		}
			break;
		case 3:
		{
			var->money -= 200;
			std::cout << "\nYou bet " << char(156) << "200 on the next roll\n";
		}
			break;
		case 4:
		{
			var->money -= 300;
			std::cout << "\nYou bet " << char(156) << "300 on the next roll\n";
		}
			break;
		case 5:
		{
			var->money -= 400;
			std::cout << "\nYou bet " << char(156) << "400 on the next roll\n";
		}
			break;
		case 6:
		{
			var->money -= 500;
			std::cout << "\nYou bet " << char(156) << "500 on the next roll\n";
		}
			break;
	}

	this->rollSlots(var->currentRoll, var->firstColumn, var->secondColumn, var->thirdColumn);
}

void methods::rollSlots(int slot, char column1, char column2, char column3)
{
	// HANDLES ALL DISPLAY AND LOGIC FOR ROLLING COLUMNS FOR SLOTS
	
	switch (slot)
	{
		case 0: // if game is on roll 1
		{
			while (!var->firstRowStopped)
			{
				var->randomChar = rand() % 10 + 1;
				column1 = var->slotCharacters[var->randomChar];
				
				Sleep(25);
				std::cout << "\r | " << column1 << " | " << column2 << " | " << column3 << " |";

				this->rollStopped();
			}
		}
			break;
		case 1: // if game is on roll 2
		{
			while (!var->secondRowStopped)
			{
				var->randomChar = rand() % 10 + 1;
				column2 = var->slotCharacters[var->randomChar];

				Sleep(25);
				std::cout << "\r | " << column1 << " | " << column2 << " | " << column3 << " |";

				this->rollStopped();
			}
		}
			break;
		case 2: // if game is on roll 3
		{
			while (!var->thirdRowStopped)
			{
				var->randomChar = rand() % 10 + 1;
				column3 = var->slotCharacters[var->randomChar];

				Sleep(25);
				std::cout << "\r | " << column1 << " | " << column2 << " | " << column3 << " |";

				this->rollStopped();
			}
		}
		break;
	}
}

void methods::rollStopped()
{
	// METHOD USED TO TELL THE GAME WHEN A ROLL HAS BEEN STOPPED

	if (_kbhit())
	{
		var->key = toupper(_getch());

		if (var->key)
		{
			switch (var->currentRoll)
			{
				case 0: // if game is on roll 1
				{
					var->firstRowStopped = true;
					var->firstColumn = var->slotCharacters[var->randomChar];
					++var->currentRoll;
					this->rollSlots(var->currentRoll, var->firstColumn, var->secondColumn, var->thirdColumn);
				}
					break;
				case 1: // if game is on roll 2
				{
					var->secondRowStopped = true;
					var->secondColumn = var->slotCharacters[var->randomChar];
					++var->currentRoll;
					this->rollSlots(var->currentRoll, var->firstColumn, var->secondColumn, var->thirdColumn);
				}
					break;
				case 2: // if game is on roll 3
				{
					var->thirdRowStopped = true;
					var->thirdColumn = var->slotCharacters[var->randomChar];
					this->checkWin(var->firstColumn, var->secondColumn, var->thirdColumn);
				}
					break;
			}
		}
	}
}

void methods::checkWin(char column1, char column2, char column3)
{
	++var->timesPlayed;

	if (column1 == column2 && column1 == column3)
	{
		++var->timesWon;
		this->jackpotWon(1000);
	}
	else if (column1 == column2 || column2 == column3)
	{
		++var->timesWon;
		this->jackpotWon(750);
	}
	else if (column1 == column3)
	{
		++var->timesWon;
		this->jackpotWon(500);
	}
	
	if (var->money <= 0)
	{
		++var->timesLost;
		this->topupMoney();
	}
	else
	{
		++var->timesLost;
		this->mainMenu();
	}
}

void methods::topupMoney()
{
	system("CLS");

	std::cout << "\n  #################";
	std::cout << "\n  ## Money Topup ##";
	std::cout << "\n  #################";

	std::cout << "\n|1) "<<  char(156) << "100";
	std::cout << "\n|2) " << char(156) << "200";
	std::cout << "\n|3) " << char(156) << "300";
	std::cout << "\n|4) " << char(156) << "400";
	std::cout << "\n|5) " << char(156) << "500";
	std::cout << "\n|6) " << "Back to main menu";

	std::cout << "\n Choose how much you want to add to your current balance of: " << char(156) << var->money << "\n";
	std::cin >> var->moneyToAdd;

	switch (var->moneyToAdd)
	{
		case 1:
		{
			var->money += 100;
		}
			break;
		case 2:
		{
			var->money += 200;
		}
			break;
		case 3:
		{
			var->money += 300;
		}
			break;
		case 4:
		{
			var->money += 400;
		}
			break;
		case 5:
		{
			var->money += 500;
		}
			break;
		case 6:
		{
			this->mainMenu();
		}
			break;
		default:
		{
			system("CLS");
			this->topupMoney();
		}
	}

	this->printStats();
}

void methods::jackpotWon(int amountWon)
{
	var->money += amountWon;
	std::cout << "\nYou won the jackpot! \n You won: " << char(156) << amountWon;
	std::cout << "\nCurrent Credit: " << char(156) << var->money;

	this->mainMenu();
}

void methods::printStats()
{
	system("CLS");

	std::cout << "\n  ###########";
	std::cout << "\n  ## STATS ##";
	std::cout << "\n  ###########";

	std::cout << "\n|Balance:       " << char(156) << var->money;
	std::cout << "\n|Times played:  " << var->timesPlayed;
	std::cout << "\n|Times Won:     " << var->timesWon;
	std::cout << "\n|Times Lost:    " << var->timesLost;
	std::cout << "\n-------------------------------------";

	this->mainMenu();
}

int methods::exitGame()
{
	delete var;

	exit(0);
}