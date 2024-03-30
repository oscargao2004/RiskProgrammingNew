#pragma once
#include <fstream>
#include "Country.h"
#include "Continent.h"

using namespace std;
class Map
{
private:
	ifstream _mapFile;

	void initializeContinents();
	void initializeCountries();
public:
	vector<Country> _countries;
	vector<Continent> _continents;
	Map(string fileName);
};
