#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Map.h"
#include "RiskStateManager.h"
#include "Country.h"
#include "Player.h"

using namespace std;

string fileName = "Map.txt";
bool running;

vector<Country> countries;
vector<Player> players;

int randomInt(int min, int max)
{
}

int main()
{
	Map map(fileName); //creates a map and initializes continents and countries based on the text file
	running = true;
	int numPlayers;

	while (running)
	{
		int currentPhase = RiskStateManager::currentPhase();

		if (currentPhase == RiskStateManager::INITIAL) //inital phase logic here
		{
			cout << "Please input the number of players playing: ";
			cin >> numPlayers;
			vector<Country> availableCountries = countries;

			//assign ownership of countries randomly to players
			for (int pIndex = 0; pIndex < numPlayers; pIndex++)
			{
				availableCountries[randomInt(0, availableCountries.size())].owner() = players[pIndex];
			}
		}

		else if (currentPhase == RiskStateManager::FORTIFICATION) //fortification phase logic here
		{
		}

		else if (currentPhase == RiskStateManager::ATTACK) //attack phase logic here
		{
		}

		else if (currentPhase == RiskStateManager::REINFORCEMENT) //reinforcement phase logic here
		{
		}
		else //if invalid phase
		{
			cout << "invalid phase\n";
		}
	}

	return 0;
}