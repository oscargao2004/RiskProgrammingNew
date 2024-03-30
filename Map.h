#pragma once
#include <fstream>

using namespace std;
class Map
{
private:
	ifstream _mapFile;

	void initializeContinents();
	void initializeCountries();
public:
	Map(string fileName);
};
