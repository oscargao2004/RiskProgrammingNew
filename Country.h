#pragma once
#include <string>
#include "Player.h"
#include "Continent.h"

class Country
{
private:
	Player _owner;
	Continent _continent;
	std::vector<Country*> _adjCountries;

public:
	std::string _name;
	int _deployedArmies;
	Player* owner();
	void setOwner(Player& p);
	Continent continent();
	void deployArmies(int num);
	std::vector<Country*> adjCountries();

	Country(std::string name) : _name(name) {}

	friend class Continent;
	friend class Player;
};

