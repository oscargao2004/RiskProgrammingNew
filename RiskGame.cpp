#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <cstdlib>
#include "RiskStateManager.h"
#include "Player.h"
#include "Continent.h"
#include "Country.h"
#include "Map.h"

string fileName = "Map.txt";
bool running;

vector<Player> players;

int randomInt(int max)
{
	return (rand() % max);
}

int main()
{
	srand(time(0));
	
	Map map(fileName); //creates a map and initializes continents and countries based on the text file
	running = true;
	int numPlayers;

	//INITIAL phase
	std::cout << "Please input the number of players playing: ";
	std::cin >> numPlayers;
	for (int i = 0; i < numPlayers; i++)
	{
		Player newPlayer;
		players.push_back(newPlayer);
	}

	std::cout << "Assigning countries randomly...\n";

	for (int i = 0; i < map._countries.size(); i++)
	{
		map._countries[i].setOwner(players[randomInt(numPlayers)]);
	}

	//for loop loops through each player every three stages
	for (int i = 0; i < numPlayers; i++)
	{
		int currentPhase = RiskStateManager::currentPhase();
		Player currentPlayer = players[i];

		/*if (currentPhase == RiskStateManager::INITIAL) //inital phase logic here
		{
			cout << "Please input the number of players playing: ";
			cin >> numPlayers;
			vector<Country> availableCountries = countries;

			//assign ownership of a random country to each player
			cout << "Assigning countries randomly...\n";
			for (int pIndex = 0; pIndex < numPlayers; pIndex++)
			{
				*availableCountries[randomInt(availableCountries.size())].owner() = players[pIndex];
			}

			cout << "Beginning reinforcement stage...\n";
			RiskStateManager::startNext();
		}*/

		if (currentPhase == RiskStateManager::REINFORCEMENT) //reinforcement phase logic here
		{
			std::cout << "Beginning reinforcement stage...\n";

			//give armies to player
			currentPlayer.addArmies(currentPlayer.ownedCountries().size() / 3);

			//checks if the player owns all countries in a continent
			for (Country* country : currentPlayer.ownedCountries())
			{
				for (int i = 0; i < country->continent().countries().size(); i++)
				{
					if (country->continent().countries()[i]->owner() == &currentPlayer)
					{
						currentPlayer.addArmies(country->continent().controlValue());
					}
				}
			}

			//if player does not have minmum 3 armies, give them 3
			if (currentPlayer.armies() < 3)
			{
				currentPlayer.setArmies(3);
			}

			//deployment of armies to countries
			//loop through army deployment until player has no more armies left to deploy
			while (currentPlayer.armies() > 0)
			{
				int choice;

				std::cout << "Input the number beside the country you want to deploy armies to: \n";
				for (int i = 0; i < currentPlayer.ownedCountries().size(); i++)
				{
					std::cout << i << ": " << currentPlayer.ownedCountries()[i]->_name << endl;
				}

				std::cin >> choice;
				Country* chosenCountry = currentPlayer.ownedCountries()[choice];

				std::cout << "Please input the number of armies you want to deploy. You have " <<
					currentPlayer.armies() << " armies." << endl;

				std::cin >> choice;
				currentPlayer.deploy(*chosenCountry, choice);
			}

			std::cout << "You have no more armies to deploy.\n";
			RiskStateManager::startNext();
		}

		else if (RiskStateManager::currentPhase() == RiskStateManager::ATTACK) //attack phase logic here
		{
			std::cout << "Beginning attack stage...\n";

			std::cout << "Do you wish to attack? Y/N\n";

			char choice;
			std::cin >> choice;
			if (choice == 'Y')
			{
				std::cout << "Input the number beside the country you wish to attack from: \n";
				for (int i = 0; i < currentPlayer.ownedCountries().size(); i++)
				{
					if (currentPlayer.ownedCountries()[i]->_deployedArmies > 1)
					{
						std::cout << i << ": " << currentPlayer.ownedCountries()[i]->_name << std::endl;
					}
				}

				int choice;
				std::cin >> choice;

				Country* attackingCountry = currentPlayer.ownedCountries()[choice];

				std::cout << "Input the number beside the country you wish to attack: \n";
				for (int i = 0; i < attackingCountry->adjCountries().size(); i++)
				{
					if (attackingCountry->adjCountries()[i]->owner() != &currentPlayer)
					{
						std::cout << i << ": " << attackingCountry->adjCountries()[i]->_name << std::endl;
					}
				}

				std::cin >> choice;
				Country* defendingCountry = attackingCountry->adjCountries()[choice];

				//roll dice
				int atkRoll = 0;
				int defRoll = 0;

				for (int i = 0; i < 3; i++) //roll atk dice 3x
				{
					int roll = randomInt(6);
					if (roll > atkRoll)
					{
						atkRoll = roll;
					}
					std::cout << "You rolled a max of: " << atkRoll << std::endl;
				}

				for (int i = 0; i < 2; i++) //roll def dice 2x
				{
					int roll = randomInt(6);
					if (roll > defRoll)
					{
						defRoll = roll;
					}
					std::cout << "The defense rolled a max of: " << defRoll << std::endl;
				}

				//compare atk/def rolls
				while (defendingCountry->_deployedArmies > 0 && attackingCountry->_deployedArmies > 0)
				{
					if (defRoll >= atkRoll)
					{
						attackingCountry->_deployedArmies--;
						defendingCountry->_deployedArmies++;
					}
					else
					{
						defendingCountry->_deployedArmies--;
						attackingCountry->_deployedArmies++;

					}
				}

				//reassign country ownership depending on winning player
				if (attackingCountry->_deployedArmies == 0)
				{
					attackingCountry->setOwner(*defendingCountry->owner());
				}
				else if (defendingCountry->_deployedArmies == 0)
				{
					defendingCountry->setOwner(*attackingCountry->owner());
				}
			}
			else
			{
				RiskStateManager::startNext();
			}
		}

		else if (RiskStateManager::currentPhase() == RiskStateManager::FORTIFICATION) //fortification phase logic here
		{
			std::cout << "Beginning fortification phase...\n";

			std::cout << "Input the number beside the country you wish to relocate armies FROM: \n";
			for (int i = 0; i < currentPlayer.ownedCountries().size(); i++)
			{
				std::cout << i << ": " << currentPlayer.ownedCountries()[i] << std::endl;
			}

			int choice;
			std::cin >> choice;

			Country c1 = *currentPlayer.ownedCountries()[choice];

			std::cout << "Input the number beside the country you wish to relocate armies TO: \n";
			for (int i = 0; i < currentPlayer.ownedCountries().size(); i++)
			{
				std::cout << i << ": " << currentPlayer.ownedCountries()[i] << std::endl;
			}

			std::cin >> choice;
			Country c2 = *currentPlayer.ownedCountries()[choice];

			std::cout << "How many armies would you like to relocate from " << c1._name <<
				" to " << c2._name << " ?\n";

			std::cin >> choice;
			//relocate armies
			c1._deployedArmies -= choice;
			c2._deployedArmies += choice;

			std::cout << c1._name << " now has " << c1._deployedArmies << " deployed.\n";
			std::cout << c2._name << " now has " << c2._deployedArmies << " deployed.\n";

		}

		for (int i = 0; i < players.size(); i++)
		{
			if (players[i].ownedCountries().size() == 0)
			{
				players.erase(players.begin() + i);
			}
		}
	}

	return 0;
}