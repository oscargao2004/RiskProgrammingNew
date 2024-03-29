#include "Map.h"

void Map::initializeContinents()
{

}

void Map::initializeCountries()
{

}

Map::Map(string fileName)
{
	_mapFile = ifstream(fileName);

	initializeContinents();
	initializeCountries();
}
