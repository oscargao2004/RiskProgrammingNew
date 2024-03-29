#pragma once
#include "Continent.h"
#include "Player.h"
#include <string>
class Country
{
private:
	Player _owner;
	Continent _continent;

public:
	std::string _name;
	int _deployedArmies;
	Player* owner();
	Continent continent();
	void deployArmies(int num);

	Country(std::string name) : _name(name) {}
};

