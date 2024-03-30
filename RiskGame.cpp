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

using namespace std;

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
	cout << "Please input the number of players playing: ";
	cin >> numPlayers;
	for (int i = 0; i < numPlayers; i++)
	{
		Player newPlayer;
		players.push_back(newPlayer);
	}
	vector<Country> availableCountries = Map::_countries;

	cout << "Assigning countries randomly...\n";
	for (int i = 0; i < numPlayers; i++)
	{
		*availableCountries[randomInt(availableCountries.size())].owner() = players[i];
	}

	cout << "Beginning reinforcement stage...\n";
	RiskStateManager::startNext();
	running = true;

	while (running)
	{
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

			if (currentPhase == RiskStateManager::REINFORCEMENT) //fortification phase logic here
			{
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
				cout << "Input the number beside the country you want to deploy armies to: \n";
				for (int i = 0; i < currentPlayer.ownedCountries().size(); i++)
				{
					cout << currentPlayer.ownedCountries()[i]->_name << i << endl;
				}

				while (currentPlayer.armies() > 0)
				{
					int choice;

					cin >> choice;
					Country* chosenCountry = currentPlayer.ownedCountries()[choice];

					cout << "Please input the number of armies you want to deploy. You have " <<
						currentPlayer.armies() << "armies." << endl;

					cin >> choice;
					currentPlayer.deploy(*chosenCountry, choice);
				}

				cout << "You have no more armies to deploy.\n Beginning attack stage...\n";
				RiskStateManager::startNext();
			}

			else if (currentPhase == RiskStateManager::ATTACK) //attack phase logic here
			{
				cout << "Input the number beside the country you wish to attack from: \n";
				for (int i = 0; i < currentPlayer.ownedCountries().size(); i++)
				{
					if (currentPlayer.ownedCountries()[i]->_deployedArmies > 1)
					{
						cout << i << ": " << currentPlayer.ownedCountries()[i] << endl;
					}
				}

				int choice;
				cin >> choice;

				Country* attackingCountry = currentPlayer.ownedCountries()[choice];

				cout << "Input the number beside the country you wish to attack: \n";
				for (int i = 0; i < attackingCountry->adjCountries().size(); i++)
				{
					if (attackingCountry->adjCountries()[i]->owner() != &currentPlayer)
					{
						cout << i << ": " << attackingCountry->adjCountries()[i]->_name << endl;
					}
				}

				cin >> choice;
				Country *defendingCountry = attackingCountry->adjCountries()[choice];

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
					cout << "You rolled a max of: " << atkRoll << endl;
				}

				for (int i = 0; i < 2; i++) //roll def dice 2x
				{
					int roll = randomInt(6);
					if (roll > defRoll)
					{
						defRoll = roll;
					}
					cout << "The defense rolled a max of: " << defRoll << endl;
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

			else if (currentPhase == RiskStateManager::FORTIFICATION) //reinforcement phase logic here
			{

			}
			else //if invalid phase
			{
				cout << "invalid phase\n";
				return 0;
			}
		}
	}

	return 0;
}