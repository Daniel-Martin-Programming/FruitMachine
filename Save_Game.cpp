#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <iostream>

#include "Methods.h"
#include <windows.h>
#include <iterator>

void methods::saveGame(variables* myVars)
{
	std::ofstream saveFile;
	
	std::cout << "\nPlease give your save file a name:\n";
	std::cin >> myVars->saveName;
	myVars->saveName += ".txt";

	if (!saveFile.is_open())
	{
		// DELETE FILE IF ALREADY EXISTS OR CREATE NEW IF IT DOESN'T
		saveFile.open(myVars->saveName);
		saveFile << myVars->money << "\n";
		saveFile << myVars->timesPlayed << "\n";
		saveFile << myVars->timesWon << "\n";
		saveFile << myVars->timesLost << "\n";
		saveFile.close();
	}

	std::cout << "\nGame has been saved!";

	this->mainMenu();
}

void methods::loadGame(variables* myVars)
{
	// LOAD IN SAVE FILE AND REPLACE CURRENT VARIABLE VALUES WITH SAVED ONES

	std::ifstream fileLoaded;

	std::vector<std::string> listOfSaves;
	this->getFileNames(&listOfSaves);

	if (listOfSaves.size() == 0)
	{
		system("CLS");
		std::cout << "No save files located!\n";
		this->mainMenu();
	}
	else
	{
		std::cout << "\nPlease choose which save file you want to use";

		for (std::vector<std::string>::iterator it = listOfSaves.begin(); it != listOfSaves.end(); ++it)
		{
			std::cout << "\n" << *it;
		}

		std::cout << "\nSave File Name : \n";
		std::cin >> myVars->saveName;
		myVars->saveName += ".txt";

		if (std::find(std::begin(listOfSaves), std::end(listOfSaves), myVars->saveName) != std::end(listOfSaves))
		{
			system("CLS");
			std::cout << "\nLoading " << myVars->saveName;

			if (!fileLoaded.is_open())
			{
				fileLoaded.open(myVars->saveName);
				fileLoaded >> myVars->money >> myVars->timesPlayed >> myVars->timesWon >> myVars->timesLost;
				fileLoaded.close();

				std::cout << "\nLoaded " << myVars->saveName;
			}
		}
		else
		{
			while (std::find(std::begin(listOfSaves), std::end(listOfSaves), myVars->saveName) == std::end(listOfSaves))
			{
				system("CLS");
				std::cout << "Save file not found, please enter a new save name";

				for (std::vector<std::string>::iterator it = listOfSaves.begin(); it != listOfSaves.end(); ++it)
				{
					std::cout << "SAVES: ";
					std::cout << "\n" << *it;
				}

				std::cout << "\n Save File Name: \n";
				std::cin >> myVars->saveName;
				myVars->saveName += ".txt";
			}
		}

		this->mainMenu();
	}	
}

void methods::getFileNames(std::vector<std::string>* fileList)
{
	std::vector<std::string> fileNames;

	WIN32_FIND_DATA search_data;

	memset(&search_data, 0, sizeof(WIN32_FIND_DATA));

	HANDLE handle = FindFirstFile("F:/CMP104-C++/Unit_Assesment2_SlotMachine/Project/Slot_Machine/Slot_Machine/*.txt", &search_data);

	while (handle != INVALID_HANDLE_VALUE)
	{
		fileList->emplace_back(std::string(search_data.cFileName));

		if (FindNextFile(handle, &search_data) == FALSE)
		{
			break;
		}
	}
}