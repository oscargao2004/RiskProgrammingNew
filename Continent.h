#pragma once
#include <vector>
#include <string>
class Country;

class Continent
{
private:
	int _controlValue;
	std::vector<Country*> _countries;
	std::vector<std::vector<Country>> adjList;

public:
	std::string _name;
	int controlValue();
	std::vector<Country*> countries();


	Continent();
	Continent(std::string name) : _name(name) {}
};

