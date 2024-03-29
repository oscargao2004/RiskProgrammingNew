#pragma once
class Country
{
private:
	Player _owner;
	int _deployedArmies;

public:
	int numDeployed();
	Player owner();
};

