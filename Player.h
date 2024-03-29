#pragma once
#include <vector>
#include <iostream>
#include "Country.h"
class Player
{
private:
	int _numArmies;
	std::vector<Country> _ownedCountries;

public:
	int armies();
	void addArmies(int num);
	void subtractArmies(int num);
	void setArmies(int num);
	std::vector<Country> ownedCountries();
	void deploy(Country country, int num);
};

