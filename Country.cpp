#include "Country.h"

void Country::deployArmies(int num)
{
    _deployedArmies += num;
}

std::vector<Country> Country::adjCountries()
{
    return _adjCountries;
}

Player* Country::owner()
{
    return &_owner;
}

void Country::setOwner(Player& p)
{
    _owner = p;
}

Continent Country::continent()
{
    return _continent;
}
