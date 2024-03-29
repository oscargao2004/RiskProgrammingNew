#pragma once
#include <vector>
#include <string>
#include "Country.h"
class Continent
{
private:
	int _controlValue;
	std::vector<Country> _countries;

public:
	std::string _name;
	int controlValue();
	std::vector<Country> countries();

	Continent(std::string name) : _name(name) {}
};

