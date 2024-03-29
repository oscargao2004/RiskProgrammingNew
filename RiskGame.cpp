#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "Map.h"
#include "RiskStateManager.h"
#include "Country.h"
#include "Player.h"

using namespace std;

string fileName = "Map.txt";
bool running;

vector<Country> countries;
vector<Player> players;

int randomInt(int max)
{
	srand(time(0));

	return (rand() % max);
}

int main()
{
	Map map(fileName); //creates a map and initializes continents and countries based on the text file
	running = true;
	int numPlayers;

	while (running)
	{
		//for loop loops through each player every three stages
		for (int i = 0; i < numPlayers; i++)
		{
			int currentPhase = RiskStateManager::currentPhase();
			Player currentPlayer = players[i];

			if (currentPhase == RiskStateManager::INITIAL) //inital phase logic here
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
			}

			else if (currentPhase == RiskStateManager::REINFORCEMENT) //fortification phase logic here
			{
				//give armies to player
				currentPlayer.addArmies(currentPlayer.ownedCountries().size() / 3);

				//checks if the player owns all countries in a continent
				for (Country country : currentPlayer.ownedCountries())
				{
					for (int i = 0; i < country.continent().countries().size(); i++)
					{
						if (country.continent().countries()[i].owner() == &currentPlayer)
						{
							currentPlayer.addArmies(country.continent().controlValue());
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
					cout << currentPlayer.ownedCountries()[i]._name << i << endl;
				}

				while (currentPlayer.armies() > 0)
				{
					int choice;

					cin >> choice;
					Country chosenCountry = currentPlayer.ownedCountries()[choice];

					cout << "Please input the number of armies you want to deploy. You have " <<
						currentPlayer.armies() << "armies." << endl;

					cin >> choice;
					currentPlayer.deploy(chosenCountry, choice);
				}

				cout << "You have no more armies to deploy.\n Beginning attack stage...\n";
				RiskStateManager::startNext();
			}

			else if (currentPhase == RiskStateManager::ATTACK) //attack phase logic here
			{


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