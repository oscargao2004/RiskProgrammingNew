#include "Map.h"

void Map::initializeContinents()
{
	//temp
	for (int i = 0; i < 3; i++)
	{
		std::string contName = "cont" + std::to_string(i);
		Continent newCont(contName);

		_continents.push_back(newCont);
	}
}

void Map::initializeCountries()
{
	//temp
	for (int i = 0; i < _continents.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::string countryName = "country" + std::to_string(i) + std::to_string(j);
			Country newCountry(countryName);

			_countries.push_back(newCountry);
		}
	}
}

Map::Map(string fileName)
{
	_mapFile = ifstream(fileName);

	initializeContinents();
	initializeCountries();
}
