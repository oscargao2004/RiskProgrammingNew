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
	static vector<Country> _countries;
	static vector<Continent> _continents;
	Map(string fileName);
};
